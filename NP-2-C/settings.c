// Include standard I/O library for printf function
#include <stdio.h>

// Include OpenMP header file for parallel programming functions and thread management
#include <omp.h>

// Main function - entry point of the program
int main()
{
    // omp_set_num_threads(20): OpenMP function to set the number of threads for parallel regions
    // 20: The exact number of threads that will be created in the thread pool
    // Note: This must be called BEFORE any parallel region is created
    omp_set_num_threads(20);
    
    // #pragma omp parallel: OpenMP directive to create a parallel region
    // All code inside the braces will be executed by all 20 threads simultaneously
    #pragma omp parallel
    {
        // omp_get_thread_num(): Returns the unique ID of the current thread (0-indexed)
        // Stores the thread ID in variable 'id'
        int id = omp_get_thread_num();
        
        // omp_get_num_threads(): Returns the total number of threads in the parallel team
        // Stores this count in variable 'n' (should be 20 based on our setting)
        int n = omp_get_num_threads();
        
        // printf(): Standard C function to print formatted output to console
        // %d is placeholder for integer values
        // Each thread prints its own ID and the total thread count
        printf("Thread %d runs in %d Total Pool\n", id, n);
    }
    
    // return 0: Returns 0 to indicate successful program execution
    return 0;
}