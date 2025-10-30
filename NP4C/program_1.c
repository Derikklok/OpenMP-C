// Include standard I/O library for printf function
#include <stdio.h>

// Include OpenMP header file for parallel programming functions
#include <omp.h>

// Include Windows header for Sleep function (Windows-specific)
#include <windows.h>

int main() {
    // Create a parallel region with exactly 4 threads
    // #pragma omp parallel: Creates multiple threads
    // num_threads(4): Specifies exactly 4 threads should be created
    #pragma omp parallel num_threads(4)
    {
        // Get the ID of the current thread (0 to 3)
        int id = omp_get_thread_num();
        
        // First print - Thread announces it's starting work
        printf("Thread %d: Starting work\n", id);
        
        // Sleep for (1 + id) seconds
        // Sleep takes milliseconds, so multiply by 1000 to convert seconds to milliseconds
        // Thread 0 sleeps for 1 sec, Thread 1 for 2 sec, Thread 2 for 3 sec, Thread 3 for 4 sec
        Sleep((1 + id) * 1000);  // Windows Sleep uses milliseconds
        
        // Second print - Thread announces it has finished its work
        printf("Thread %d: Finished work\n", id);
        
        // #pragma omp barrier: Synchronization point
        // All threads MUST wait here until EVERY thread reaches this point
        // This ensures all threads have finished their work before proceeding
        #pragma omp barrier
        
        // Third print - Only executes after ALL threads have reached the barrier
        // Shows the power of barrier synchronization
        printf("Thread %d: All threads have finished!\n", id);
    }
    
    // return 0: Program completed successfully
    return 0;
}