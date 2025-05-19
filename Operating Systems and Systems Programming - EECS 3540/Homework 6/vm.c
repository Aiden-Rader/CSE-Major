#include "vm.h"

// Global Variables from the header file
FILE *address_file;
FILE *backing_store;
char buffer[BUFFER_SIZE];
signed char *physical_memory;
int page_table[PAGE_TABLE_SIZE];
int free_frame_list[NUMBER_OF_FRAMES];
struct tlb_entry tlb[TLB_SIZE];

int next_free_frame = 0;
int page_fault_count = 0;
int tlb_hit_count = 0;
int total_addresses = 0;
int tlb_fifo_index = 0;
int frame_fifo_index = 0;

// Helper Functions //

// Returns frame number from TLB, or -1 on miss
int tlb_lookup(int page_number) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].valid && tlb[i].page_number == page_number) {
            tlb_hit_count++;
            return tlb[i].frame_number;
        }
    }
    return -1;
}

// Inserts into TLB using FIFO
void tlb_insert(int page_number, int frame_number) {
    tlb[tlb_fifo_index].page_number = page_number;
    tlb[tlb_fifo_index].frame_number = frame_number;
    tlb[tlb_fifo_index].valid = 1;
    tlb_fifo_index = (tlb_fifo_index + 1) % TLB_SIZE;
}

// Returns next available frame index, or evicts using FIFO if full
int get_free_frame() {
    if (next_free_frame < NUMBER_OF_FRAMES) {
        return next_free_frame++;
    } else {
        int evicted_frame = frame_fifo_index;
        for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
            if (page_table[i] == evicted_frame) {
                page_table[i] = -1;
                break;
            }
        }
        frame_fifo_index = (frame_fifo_index + 1) % NUMBER_OF_FRAMES;
        return evicted_frame;
    }
}

// Main Function //
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s BACKING_STORE.bin addresses.txt\n", argv[0]);
        return 1;
    }

    // Open backing store bin file
    backing_store = fopen(argv[1], "rb");
    if (backing_store == NULL) {
        perror("Error opening BACKING_STORE.bin");
        return 1;
    }

    physical_memory = (signed char *)malloc(MEMORY_SIZE);

    // If there is no physical memory check
    if (physical_memory == NULL) {
        perror("Failed to allocate physical memory");
        return 1;
    }

    // Initialize page table to -1 which means empty
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i] = -1;
    }

    // Initialize TLB to invalid
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb[i].valid = 0;
    }

    // Open address text file
    address_file = fopen(argv[2], "r");
    if (address_file == NULL) {
        perror("Error opening addresses.txt");
        return 1;
    }

    int logical_address;
    while (fscanf(address_file, "%d", &logical_address) == 1) {
        total_addresses++;

        // Calculate page number, offset and logical address (in 16-bit format)
        int logical_16 = logical_address & 65535;
        int page_number = (logical_16 >> 8) & 255;
        int offset = logical_16 & 255;

        // Use this helper function
        int frame_number = tlb_lookup(page_number);

        if (frame_number == -1) {
            // TLB miss — check page table
            if (page_table[page_number] == -1) {
                // Page fault counter
                page_fault_count++;

                frame_number = get_free_frame();
                fseek(backing_store, page_number * PAGE_SIZE, SEEK_SET);
                fread(physical_memory + (frame_number * PAGE_SIZE), sizeof(char), PAGE_SIZE, backing_store);

                page_table[page_number] = frame_number;
            } else {
                frame_number = page_table[page_number];
            }

            // Update TLB after finding the frame
            tlb_insert(page_number, frame_number);
        }

        int physical_address = (frame_number * PAGE_SIZE) + offset;
        signed char value = physical_memory[physical_address];

        // Main Address and Value Information
        printf("Logical Address: %d\n", logical_address);
        printf("Physical Address: %d\n", physical_address);
        printf("Value: %d\n", value);
    }

    // Print other information (i.e. Page Fault Count and TLB Hit Count)
    printf("\nPage Faults = %d\n", page_fault_count);
    printf("TLB Hits = %d\n", tlb_hit_count);

    // Cleaning and closing functions
    fclose(backing_store);
    fclose(address_file);
    free(physical_memory);  // Clean up function for memory leaks
    return 0;
}