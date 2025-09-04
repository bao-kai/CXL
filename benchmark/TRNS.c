//trns
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
    size_t file_size = 96ULL * 1024 * 1024 * 1024; 
    size_t dpu = 16;
    off_t one_thread = 50 * 1024 * 1024 * dpu; 

    off_t one_thread_numbers = one_thread / sizeof(int64_t); 
    off_t rep_times = file_size / one_thread_numbers; // 

    printf("Allocating %zu bytes (%.1f GB)\n",
           file_size, file_size / (1024.0 * 1024.0 * 1024.0));

    volatile int64_t *p = (volatile int64_t *)malloc(file_size);
    if (!p) {
        fprintf(stderr, "malloc() failed\n");
        return EXIT_FAILURE;
    }

    for(size_t j = 0; j < rep_times ;j++){
        for (size_t i = 0; i < one_thread_numbers; i++) {
            p[one_thread_numbers * j + i] = i;
        }
        for (size_t i = 0; i < one_thread_numbers; i++) {
            (void)p[one_thread_numbers *j + i]; 
        }
        
        
        
        
    }

    

    

    free(p);
    return EXIT_SUCCESS;
}