#ifndef VM_H
#define VM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10
#define PAGE_SIZE 256
#define PAGE_TABLE_SIZE 256
#define NUMBER_OF_FRAMES 256
#define TLB_SIZE 16
#define MEMORY_SIZE (NUMBER_OF_FRAMES * PAGE_SIZE)

struct tlb_entry {
    int page_number;
    int frame_number;
    int valid;
};

// Declare all global variables — DO NOT assign them in the header
extern FILE *address_file;
extern FILE *backing_store;
extern char buffer[BUFFER_SIZE];
extern signed char *physical_memory;
extern int page_table[PAGE_TABLE_SIZE];
extern int free_frame_list[NUMBER_OF_FRAMES];
extern struct tlb_entry tlb[TLB_SIZE];

extern int next_free_frame;
extern int page_fault_count;
extern int tlb_hit_count;
extern int total_addresses;
extern int tlb_fifo_index;
extern int frame_fifo_index;

int tlb_lookup(int page_number);
void tlb_insert(int page_number, int frame_number);
int get_free_frame();

#endif
