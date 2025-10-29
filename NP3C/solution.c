#include <stdio.h>
#include <omp.h>

int main() {
    int x = 0;
    
    #pragma omp parallel for shared(x)
    for (int i = 0; i < 4; i++) {
        // i is PRIVATE - each thread has its own i
        // x is SHARED - all threads see same x
        x++;
    }
    
    printf("x = %d\n", x);
    return 0;
}