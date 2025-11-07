// mmap_read_64g.c
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
    size_t file_size = 638ULL * 1024 * 1024; // 128GB
    off_t one_thread = 512ULL * 1024 * 1024; // 64MB

    off_t one_thread_numbers = one_thread / sizeof(uint32_t); // 每個線程寫入的 uint64_t 數量
    off_t rep_times = file_size / one_thread_numbers; // 

    printf("Allocating %zu bytes (%.1f GB)\n",
           file_size, file_size / (1024.0 * 1024.0 * 1024.0));

    volatile uint32_t *p = (uint32_t *)malloc(file_size);
    if (!p) {
        fprintf(stderr, "malloc() failed\n");
        return EXIT_FAILURE;
    }
    printf("rep_times: %d, one_thread_numbers: %d\n", (int)rep_times, (int)one_thread_numbers);
    // 初始化記憶體 (確保實際分配到實體頁面)
    for(size_t j = 0; j < 1 ;j++){
        for (size_t i = 0; i < file_size; i++) {
            p[file_size * j + i] = (uint8_t)(i % 256);
        }
        usleep(1);
        
        
    }
    for (size_t i = 0; i < 4425; i++) {
            (void)p[i]; 
    }
    

    

    free(p);
    return EXIT_SUCCESS;
}
