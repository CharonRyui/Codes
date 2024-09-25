#include <iostream>
#include <omp.h>

int main() {

    int my_id;

    #pragma omp parallel private(my_id) num_threads(3) 
    {   
        my_id = omp_get_thread_num();
        std::cout << "all is running this, my id is " << my_id << std::endl;

        //if the tasks in each section is too simple to tackle, the first thread that had come would probably make all tasks done before others get ready
        #pragma omp sections
        {
            #pragma omp section 
            {
                  std::cout << "who is running this section1? " << my_id << std::endl;
                  for (int i = 0 ; i < 1000000; i++) {};
            }

            #pragma omp section 
            {
                std::cout << "who is running this section2? " << my_id << std::endl;
                for (int i = 0 ; i < 1000000; i++) {};
            }

            #pragma omp section 
            {
                std::cout << "who is running this section3? " << my_id << std::endl;
                for (int i = 0 ; i < 1000000; i++) {};
            }
        }
    }

    return 0;
}