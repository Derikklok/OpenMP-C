// Include standard I/O library for printf function
#include <stdio.h>

// Include OpenMP header file for parallel programming functions
#include <omp.h>

// Main function - entry point of the program
int main(){
    // int sum = 0: Initialize a variable to store the sum of all iterations
    // This will accumulate values from the parallel for loop
    int sum = 0;
    
    // int steps = 10: Define the number of iterations the loop will run (1 to 10)
    int steps = 10;

    // #pragma omp parallel for: OpenMP directive that parallelizes the for loop
    // "parallel" creates multiple threads
    // "for" distributes loop iterations among these threads
    // Each iteration can be executed by different threads simultaneously
    #pragma omp parallel for
    for(int i=1; i<=steps; i++){
        // sum+=i: Add the current iteration value to the sum
        // Note: In a real scenario, this should use #pragma omp critical or #pragma omp atomic
        // to avoid race conditions when multiple threads access 'sum' simultaneously
        sum+=i;
        
        // printf(): Print which iteration is executing and which thread is executing it
        // %d: placeholder for integer values
        // omp_get_thread_num(): Returns the ID of the current thread executing this iteration
        printf("Iteration %d, executed by thread %d \n", i, omp_get_thread_num());
    }
    
    // printf(): Print the final sum after all iterations are complete
    // \t: tab character for formatting
    // -: separator for clarity
    printf("Total is\t:-\t %d", sum);
    
    // return 0: Return 0 to indicate successful program execution
    return 0;
}