#include <stdio.h>
#include <omp.h>

int main()
{
    omp_set_num_threads(4);
#pragma omp parallel
    {
        printf("Runs in 4 threads\n");
    }
    return 0;
}