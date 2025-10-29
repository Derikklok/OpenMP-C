// Include standard I/O library for printf function
#include <stdio.h>

// Include OpenMP header file for parallel programming functions
#include <omp.h>

// Main function - entry point of the program
int main() {
    // #pragma omp parallel: OpenMP directive to create a parallel region
    // All code inside the braces will be executed by multiple threads simultaneously
    #pragma omp parallel
    {
        // omp_get_thread_num(): Returns the unique ID of the current thread (0-indexed)
        // Stores the thread ID in variable 'id'
        int id = omp_get_thread_num();
        
        // omp_get_num_threads(): Returns the total number of threads in the parallel team
        // Stores this count in variable 'n'
        int n  = omp_get_num_threads();
        
        // printf(): Standard C function to print formatted output to console
        // %d is placeholder for integer values
        // Each thread prints its own ID and the total thread count
        printf("Thread %d of %d says hello\n", id, n);
    }
    
    // return 0: Returns 0 to indicate successful program execution
    return 0;
}
