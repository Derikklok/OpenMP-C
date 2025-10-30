#include <stdio.h>
#include <omp.h>

int main()
{
    int max;
    int num_array[10] = {4, 2, 3, 1, 5, 6, 7, 8, 9, 10};
    max = num_array[0];
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < 10; i++)
    {
        #pragma omp critical
        if (num_array[i]>max)
        {
            max = num_array[i];
        };
        
    };
    
    printf("max = %d\n", max);

return 0;
}