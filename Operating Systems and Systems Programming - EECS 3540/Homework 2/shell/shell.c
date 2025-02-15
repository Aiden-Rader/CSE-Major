#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 80 /* The maximum length command */

char last_command[MAX_LINE] = "";

int main(void)
{
    char *args1[MAX_LINE / 2 + 1]; /* command line arguments */
    char *args2[MAX_LINE / 2 + 1]; /* command after pipe */
    char user_in[MAX_LINE];  /* Stores the users input */

    int should_run = 1; /* flag to determine when to exit program */

    while (should_run) {
        printf("osh> ");
        fflush(stdout);

        /* Error handling for reading in the users input */
        if (!fgets(user_in, MAX_LINE, stdin)) {
            perror("Failed to read user input");
            continue;
        }

        /* Remove the newline character from input... if applicable */
        user_in[strcspn(user_in, "\n")] = 0;

        /* Handle empty input, this was just something I realized should be an edge case so I added it! */
        if (strlen(user_in) == 0) {
            printf("No command entered. Please type a command.\n");
            continue;
        }

        /* Exit if the user types the string "exit" */
        if (strcmp(user_in, "exit") == 0) {
            should_run = 0;
            continue;
        }

        /* Handle !! command which gives the last cmd entered */
        int is_last_cmd = 0;
        if (strcmp(user_in, "!!") == 0) {
            if (strlen(last_command) == 0) {
                printf("No previous command found.\n");
                continue;
            } else {
                strcpy(user_in, last_command); // Replace user_in with last command
																	 
                is_last_cmd = 1;
            }
        } else {
            strcpy(last_command, user_in);
        }

        /* Check for pipe and set the has pipe_flag accordingly */
        int has_pipe = 0;
        char *cmd1 = strtok(user_in, "|");
        char *cmd2 = strtok(NULL, "|");

        if (cmd2 != NULL) {
            has_pipe = 1;
        }

        /* PARSING INPUT PORTION OF THE CODE */

        int i = 0;
        int j = 0;
        int redirect_out = 0; 
        int redirect_in = 0;
        int run_in_background = 0;

        char *token = strtok(cmd1, " ");
        char *output_file = NULL;
        char *input_file = NULL;

        /* When the token is not nulled, check if user wants cmd to run in background by looking for & */
        while (token != NULL) {
            if (strcmp(token, ">") == 0) {
                token = strtok(NULL, " ");
                if (token == NULL) {
                    printf("Error: No output file specified.\n");
                    break;
                }
                output_file = token;
                redirect_out = 1;
            } else if (strcmp(token, "<") == 0) {
                token = strtok(NULL, " ");
                if (token == NULL) {
                    printf("Error: No input file specified.\n");
                    break;
                }
                input_file = token;
                redirect_in = 1;
            } else if (strcmp(token, "&") == 0) {
                run_in_background = 1;
                break;
            } else {
                args1[i++] = token;
            }
            token = strtok(NULL, " ");
        }
        args1[i] = NULL;

        /* Tokenize second command (if pipe exists) */
        if (has_pipe) {
            token = strtok(cmd2, " ");
            while (token != NULL) {
                args2[j++] = token;
                token = strtok(NULL, " ");
            }
            args2[j] = NULL;
        }

        /* EXECUTE INPUT PORTION OF THE CODE */

        /* Create pipe if necessary, add error handler */
        int pipefd[2];
        if (has_pipe) {
            if (pipe(pipefd) == -1) {
                perror("Pipe failed");
                continue;
            }
        }

        /* This is where we fork the FIRST child process */
        pid_t pid1 = fork();

        /* Check if successfully forked */
        if (pid1 < 0) {
            perror("Fork failed");
			continue;
        }
		
		if (pid1 == 0) {
		
            /* Child Process 1 */

            /* Handle Output Redirection */
            if (redirect_out) {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("Failed to open output file");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            /* Handle Input Redirection */
            if (redirect_in) {
                int fd = open(input_file, O_RDONLY);
                if (fd == -1) {
                    perror("Failed to open input file");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }

             /* If cmd has pipe in it, redirect stdout to pipe */
            if (has_pipe) {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }

			/* Handle last command arguement */
            if (is_last_cmd) {
                printf("This is the last arguement: %s\n", last_command);
            } else {
                printf("This is the argument: %s\n", args1[0]);  /* Had to replace the printk because it was causing issues */
            }													  

            /* Execute the args1 and see if it fails */ 
            execvp(args1[0], args1);
            perror("the cmd 'execvp' failed");
            exit(EXIT_FAILURE);
        }

        /* Fork SECOND process if there's a pipe, add error handler */
        if (has_pipe) {
            pid_t pid2 = fork();
            if (pid2 < 0) {
                perror("Fork failed");
                continue;
            }

            if (pid2 == 0) {

                /* Child Process 2 */

                close(pipefd[1]);
                dup2(pipefd[0], STDIN_FILENO);
                close(pipefd[0]);

                execvp(args2[0], args2);
                perror("execvp failed");
                exit(EXIT_FAILURE);
            }

            /* Parent: Close pipe */
            close(pipefd[0]);
            close(pipefd[1]);
        }

        /* Parent Process waits for child unless background execution is requested */
        if (!run_in_background) {
            wait(NULL);
            if (has_pipe) {
                wait(NULL);
            }
        }
    }

    return 0;
}