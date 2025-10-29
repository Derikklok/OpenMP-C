#include <stdio.h>
#include <omp.h>

int main()
{
    omp_set_num_threads(20);
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int n = omp_get_num_threads();
        printf("Thread %d runs in %d Total Pool\n",id,n);
    }
    return 0;
}