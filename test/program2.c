#include <stdio.h>
#include <omp.h>

int main()
{
    omp_set_num_threads(4);
#pragma omp parallel
    {

#pragma omp for
        for (int i = 0; i < 5; i++)
        {
            printf("Hello i\t=\t %d  from thread\t:\t %d \n", i, omp_get_thread_num());
        }
    }
    return 0;
}