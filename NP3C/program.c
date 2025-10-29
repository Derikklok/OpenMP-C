#include <stdio.h>
#include <omp.h>

int main() {
    int x = 0;
    
    #pragma omp parallel for
    for (int i = 0; i < 4; i++) {
        x++;  // PROBLEM! All threads modifying same x
    }
    
    printf("x = %d (should be 4, but might be 1, 2, 3, or 4!)\n", x);
    return 0;
}