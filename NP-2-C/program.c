#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int n  = omp_get_num_threads();
        printf("Thread %d of %d says hello\n", id, n);
    }
    return 0;
}
