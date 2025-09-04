// hst-l.c
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    size_t file_size = 96ULL * 1024 * 1024 * 1024; // 
    const size_t DPU_COUNT = 16;
    size_t one_thread = 50 * 1024 * 1024 * DPU_COUNT; // 

    off_t one_thread_numbers = one_thread / sizeof(uint32_t); //
    off_t rep_times = file_size / one_thread_numbers; // 

    printf("Allocating %zu bytes (%.1f GB)\n",
           file_size, file_size / (1024.0 * 1024.0 * 1024.0));

    volatile uint32_t *p = (volatile uint32_t *)malloc(file_size);
    if (!p) {
        fprintf(stderr, "malloc() failed\n");
        return EXIT_FAILURE;
    }

    for(size_t j = 0; j < rep_times ;j++){
        for (size_t i = 0; i < one_thread_numbers; i++) {
            p[one_thread_numbers * j + i] = i;
        }
      
        for(size_t i = 0; i < 256 * DPU_COUNT; ++i) {
                (void)p[i]; // Simulate reading data
            }
        
        
        
    }

    

    

    free(p);
    return EXIT_SUCCESS;
}