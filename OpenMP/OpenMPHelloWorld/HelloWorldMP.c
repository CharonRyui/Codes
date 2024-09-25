#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
    int threadsNum;
    int threadID;
    int countNum = 0;

    omp_set_num_threads(7);
    
    #pragma omp parallel /*num_threads(7)*/ private(threadID, threadsNum)
    {

        threadID = omp_get_thread_num();
        printf("Hello World! This is %d\n", threadID);
        printf("%d\n", countNum);
        countNum++;

        if (threadID == 0) 
        {
            threadsNum = omp_get_num_threads();
            printf("Here are %d threads in total\n", threadsNum);
        }
        
    }
    return 0;
}