// Set up the necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define GRID_SIZE 9 // Used for the 9x9 grid shape
#define MAX_PUZZLES 5 // We only use 5 puzzles in the txt file so we can make sure we are only storing exactly 5

// On/off pre-processsor flags for logging and execution timing
#define LOGGING_ENABLED 0  /* <-- NOTE: LOGGING_ENABLED = 1 makes individual thread logging appear in the output */
#define MEASURE_TIME 1  /* <-- NOTE: MEASURE_TIME = 1 makes clock functions start and stop returning time for process to run */

// Declaration of function prototypes (suppresses warnings)
void *check_row(void *param);
void *check_column(void *param);
void *check_subgrid(void *param);

// structure for passing data to threads
typedef struct {
    int puzzle_id;
    int thread_number;
    int puzzle_row;
    int puzzle_column;
} thread_parameter_t;

// Defines the global sudoku puzzle(s) that will be used to store our 
int sudoku_puzzles[MAX_PUZZLES][GRID_SIZE][GRID_SIZE];

// Top level function that reads the text file and outputs results, populates globals, tokenizes and splits puzzles into their own groups
int load_sudoku_file(const char *filename) {
    FILE *file = fopen(filename, "r");

    // Add some error handling for when the file cannot be opened
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Count and iterator variables
    int puzzle_count = 0;
    int row = 0;
    int col = 0;

    // Acts as a buffer to read lines from grid(s)
    char line[100];

    while (fgets(line, sizeof(line), file)) {
        // If we hit a blank line, move to the next puzzle after counting the rows, columns, and the overall puzzle(s)
        if (line[0] == '\n' || line[0] == '\r') {  
            puzzle_count++;
            row = 0;
            col = 0;
            continue;
        }
        
        // Avoid reading more than 5 puzzles
        if (puzzle_count >= MAX_PUZZLES) {
            break;
        }

        // Tokenization portion
        col = 0;
        char *token;
        token = strtok(line, " ");

        while (token != NULL && col < GRID_SIZE) {
            sudoku_puzzles[puzzle_count][row][col] = atoi(token);
            token = strtok(NULL, " ");
            col++;
        }
        row++;
    }

    // Make sure the last puzzle is counted even without return/whitespace under it!
    if (row > 0) {
        puzzle_count++;
    }

    // Close the file, return the number of puzzles loaded
    fclose(file);
    return puzzle_count;
}

// Function to validate the puzzle(s) given the user input
void validate_puzzle(int p_id, int num_threads) {
    clock_t start;
    clock_t end;

    // If there measured time is true then start the clock
    if (MEASURE_TIME) {
        start = clock();
    }

    int is_valid = 1;

    // Set a total count of 27 threads
    pthread_t threads[27];
    thread_parameter_t params[27];

    int thread_count = 0;

    // For Rows
    for (int i = 0; i < GRID_SIZE && thread_count < num_threads; i++) {
        params[thread_count].puzzle_id = p_id;
        params[thread_count].thread_number = thread_count;
        params[thread_count].puzzle_row = i;
        pthread_create(&threads[thread_count], NULL, check_row, &params[thread_count]);
        thread_count++;
    }

    // For Columns
    for (int i = 0; i < GRID_SIZE && thread_count < num_threads; i++) {
        params[thread_count].puzzle_id = p_id;
        params[thread_count].thread_number = thread_count;
        params[thread_count].puzzle_column = i;
        pthread_create(&threads[thread_count], NULL, check_column, &params[thread_count]);
        thread_count++;
    }

    // For Subgrids
    for (int i = 0; i < GRID_SIZE && thread_count < num_threads; i += 3) {
        for (int j = 0; j < GRID_SIZE && thread_count < num_threads; j += 3) {
            params[thread_count].puzzle_id = p_id;
            params[thread_count].thread_number = thread_count;
            params[thread_count].puzzle_row = i;
            params[thread_count].puzzle_column = j;
            pthread_create(&threads[thread_count], NULL, check_subgrid, &params[thread_count]);
            thread_count++;
        }
    }

    // Status is being used to store the return value of pthread_join which can be something or NULL/0
    void *status;
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], &status);
        if ((intptr_t) status == 0) {
            is_valid = 0;
        }
    }

    if (MEASURE_TIME) {
        end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Execution time for Puzzle %d with %d threads: %f seconds\n", p_id + 1, num_threads, time_taken);
    } else {
        // Checks puzzles validitiy 
        if (is_valid) {
            printf("Puzzle %d: Valid\n", p_id + 1);
        } else {
            printf("Puzzle %d: Invalid\n", p_id + 1);
        }
    }
}

// A thread to check that each column contains the digits 1 through 9
void *check_row(void *param) {
    thread_parameter_t *data = (thread_parameter_t*) param;
    int row = data->puzzle_row;
    int puzzle = data->puzzle_id;

    int num_seen[GRID_SIZE + 1] = {0};

    for (int col = 0; col < GRID_SIZE; col++) {
        int num = sudoku_puzzles[puzzle][row][col];
        if (num < 1 || num > 9 || num_seen[num]) {
            if (LOGGING_ENABLED) {
                printf("Thread %d: Row validation Invalid\n", data->thread_number);
            }
            pthread_exit((void *) 0);
        }
        num_seen[num] = 1;
    }
    if (LOGGING_ENABLED) {
        printf("Thread %d: Row validation Valid\n", data->thread_number);
    }
    pthread_exit((void *) 1);
}

// A thread to check that each row contains the digits 1 through 9
void *check_column(void *param) {
    thread_parameter_t *data = (thread_parameter_t*) param;
    int col = data->puzzle_column;
    int puzzle = data->puzzle_id;

    int num_seen[GRID_SIZE + 1] = {0};
    
    for (int row = 0; row < GRID_SIZE; row++) {  
        int num = sudoku_puzzles[puzzle][row][col];
        if (num < 1 || num > 9 || num_seen[num]) {  
            if (LOGGING_ENABLED) {
                printf("Thread %d: Column validation Invalid\n", data->thread_number);
            }
            pthread_exit((void *) 0);
        }
        num_seen[num] = 1;
    }
    if (LOGGING_ENABLED) {
        printf("Thread %d: Column validation Valid\n", data->thread_number);
    }
    pthread_exit((void *) 1);
}

// Nine threads to check that each of the 3 × 3 subgrids contains the digits 1 through 9
void *check_subgrid(void *param) {
    thread_parameter_t *data = (thread_parameter_t*) param;
    int row_start = data->puzzle_row;
    int col_start = data->puzzle_column;
    int puzzle = data->puzzle_id;

    int num_seen[GRID_SIZE + 1] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = sudoku_puzzles[puzzle][row_start + i][col_start + j];
            if (num < 1 || num > 9 || num_seen[num]) {
                if (LOGGING_ENABLED) {
                    printf("Thread %d: Subgrid validation Invalid\n", data->thread_number);
                }
                pthread_exit((void *) 0);
            }
            num_seen[num] = 1;
        }
    }
    if (LOGGING_ENABLED) {
        printf("Thread %d: Subgrid validation Valid\n", data->thread_number);
    }
    pthread_exit((void *) 1);
}

// Here will be how we run the program!
int main(int argc, char *argv[]) {
    char *filename = "puzzles.txt";
    int num_puzzles = load_sudoku_file(filename);

    if (num_puzzles == 0) {
        printf("No puzzles found in file.\n");
        return 1;
    }

    // If the user arguements are not what they should be, notify and print to terminal
    if (argc < 2) {
        printf("Invalid Arugments, Try Again\n");
        return 1;
    }

    // If we are running performance metrics then activate them
    if (strcmp(argv[1], "perf") == 0) {
        int p_id = 0;
        int thread_counts[] = {9, 18, 27, 36};
        int num_tests = sizeof(thread_counts) / sizeof(thread_counts[0]);

        // Since we want to ONLY measure performance in performance mode, let user know MEASURE_TIME is not enabled if that is the case
        if (!MEASURE_TIME) {
            printf("MEASURE_TIME Flag is not enabled!\n");
            return 1;
        } else {
            for (int i = 0; i < num_tests; i++) {
                validate_puzzle(p_id, thread_counts[i]);
            }
        }

        // Put it back to what it was before after execution
        return 0;
    }

    int filtered_puzzles[MAX_PUZZLES];
    int total_filtered_puzzles = 0;

    // If you want to validate all puzzles, the argument is all, else use the specific id number for each puzzle you want to validate
    if (strcmp(argv[1], "all") == 0) {
        for (int i = 0; i < num_puzzles; i++) {
            filtered_puzzles[total_filtered_puzzles++] = i;
        }
    } else {
        for (int i = 1; i < argc; i++) {
            int puzzle_num = atoi(argv[i]);
            if (puzzle_num < 1 || puzzle_num > num_puzzles) {
                printf("Invalid puzzle number: %d\n", puzzle_num);
                return 1;
            }
            filtered_puzzles[total_filtered_puzzles++] = puzzle_num - 1;
        }
    }

    // For each of the puzzles now validate them
    for (int i = 0; i < total_filtered_puzzles; i++) {
        validate_puzzle(filtered_puzzles[i], 27);
    }
    return 0;
}