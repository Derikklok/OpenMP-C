#include <stdio.h>
#include <omp.h>

int main()
{
printf("Before Core level execution..\n");
#pragma omp parallel
{
    int thread_id = omp_get_thread_num();
    int total_number_of_threads = omp_get_num_threads();
    printf("Hello from thread: %d of total :- %d number of threads...\n", thread_id, total_number_of_threads);
}
printf("After Core level execution..\n");
return 0;
}