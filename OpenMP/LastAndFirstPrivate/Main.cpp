#include <iostream>
#include <omp.h>

int main(int argc, char *argv[]) {
    
    int firstNum = 100l;
    int lastNum = 3003;
    int threadId;
    int num = 999;

    #pragma omp parallel private(threadId, num) num_threads(4)
    {
        threadId = omp_get_thread_num();
        std::cout << "FFFF  this is " << threadId << " my firstNum is " << firstNum << " my num is " << num << std::endl;
        
        //using firstprivate, the initialization of the variable will be the same
        //using lastprivate, after a for, the final circulation's value will be held by every thread
        #pragma omp for firstprivate(firstNum) lastprivate(lastNum)
        for (int i = 0; i < 12; i++) {
            lastNum = i * i;
            std::cout << "MMMM   this is " << threadId << " my lastNum is " << lastNum << std::endl;
        }

        std::cout << "LLLL   this is " << threadId << " my lastNum is " << lastNum << std::endl;
    }
    
    
    return 0;
}