#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        
        #pragma omp for
        for (int i = 0; i < 10; i++) {
            printf("Thread %d: Iteration %d\n", id, i);
        }
        
        #pragma omp barrier  // Waits for ALL loop iterations from ALL threads
        
        printf("Thread %d: All threads finished the loop!\n", id);
    }
    
    return 0;
}