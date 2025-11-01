#include <stdio.h>
#include <omp.h>

int main(){
    int wallHeight = 4;
    omp_set_num_threads(wallHeight); 

    #pragma omp parallel
    {

        for (int i = 0; i < 1; i++)
        {
            /* code */
            printf("===============\n");
        }
        
    }
    return 0;
}