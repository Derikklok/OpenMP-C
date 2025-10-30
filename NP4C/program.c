// Include standard I/O library for printf function to display output
#include <stdio.h>

// Include OpenMP header file for parallel programming functions and synchronization
#include <omp.h>

// Main function - entry point of the program
int main()
{
    // int max: Declare a variable to store the maximum value found in the array
    // This variable will be shared among all threads (critical section)
    int max;
    
    // int num_array[10]: Declare an array of 10 integers
    // Initialize with values: {4, 2, 3, 1, 5, 6, 7, 8, 9, 10}
    // The largest value is 10 at index 9
    int num_array[10] = {4, 2, 3, 1, 5, 6, 7, 8, 9, 10};
    
    // max = num_array[0]: Initialize max with the first element (4)
    // This sets the initial value to compare against
    // Starting value is 4, which will be updated as larger values are found
    max = num_array[0];
    
    // #pragma omp parallel for num_threads(4): OpenMP directive with two parts:
    //   - "parallel for" creates parallel threads and distributes loop iterations among them
    //   - "num_threads(4)" explicitly creates exactly 4 threads for this loop
    // Without num_threads(), it would create threads based on system CPU count
    // Loop iterations (0-9) will be divided among these 4 threads
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 10; i++)
    {
        // #pragma omp critical: Synchronization directive that ensures ONLY ONE THREAD at a time
        // can execute the code block inside
        // Critical section prevents RACE CONDITIONS (multiple threads modifying same variable)
        // Without this, multiple threads could read the same 'max' value and cause data corruption
        #pragma omp critical
        {
            // if (num_array[i] > max): Comparison check
            // Compares current array element with current maximum value
            // Only enters the block if array element is greater than max
            if (num_array[i] > max)
            {
                // max = num_array[i]: Update max with the new larger value
                // Only one thread can execute this at a time (due to #pragma omp critical)
                // This prevents race conditions where multiple threads write simultaneously
                max = num_array[i];
            }
        }; // End of critical section - other threads can now enter
        
    }; // End of parallel for loop - implicit barrier synchronization here
    
    // printf(): Print the final maximum value after all threads complete
    // All 4 threads must finish before this line executes
    printf("max = %d\n", max);

    // return 0: Return 0 to indicate successful program execution
    return 0;
}
