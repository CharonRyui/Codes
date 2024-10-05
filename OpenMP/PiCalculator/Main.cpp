#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <random>
<<<<<<< HEAD
const long long N = 10000000;

double calParallel() 
{
    long long result = 0;

    #pragma omp parallel num_threads(4)
    {
        int thread_num = omp_get_thread_num();

        //global seed
        std::random_device rd;
        std::mt19937 gen(rd());
        //seed held by each thread
        std::mt19937 thread_gen;
        //use thread id and xor operation to modify a local seed
        //to ensure every thread will access a different random seed and thus keep the thread safety
        thread_gen.seed(rd() ^ thread_num);
        long long local_result = 0;
        std::uniform_real_distribution<> dist(0.0, 1.0);
        #pragma omp for schedule(auto)  //reduction(+:result) 
        for (long long i = 0; i < N; i++)
        {
            // x = dist(thread_gen);
            // y = dist(thread_gen);
            double x = dist(thread_gen);
            double y = dist(thread_gen);
            if (x * x + y * y < 1) local_result++;
        }
        #pragma omp atomic
        result += local_result;
        std::cout << "here is thread" << thread_num << " the result is " << local_result << std::endl;
    }
    return (double)result / N * 4;
}
        


double his() {
    // 全局计数器 result，存放归约结果
    double result = 0.0;

    // 定义并行区域，指定 result 为归约变量
    #pragma omp parallel num_threads(1)
    {
        // 每个线程创建一个独立的随机数生成器
        std::random_device rd;
        int thread_num = omp_get_thread_num();  // 获取当前线程的 ID
        std::mt19937 thread_gen(rd() ^ thread_num);  // 用线程 ID 来播种随机数生成器
        std::uniform_real_distribution<> dist(0.0, 1.0);  // 生成 [0, 1) 之间的随机数

        // 线程局部的计数器
        double local_result = 0.0;
        #pragma omp for
        for (long long i = 0; i < N; i++)
        {
            double x = dist(thread_gen);
            double y = dist(thread_gen);
            if (x * x + y * y < 1) local_result++;
        }

        #pragma omp atomic
        result += local_result;
    }
    return result / N;
}


double calSerial() 
{
=======
#define N 10000000

double calParallel() 
{
    //global seed
>>>>>>> 7c45cdc5b20d6b8ff210259ff7fc3c337cd3a021
    std::random_device rd;
    std::mt19937 gen(rd());
    double result = 0;
    double x, y;
<<<<<<< HEAD
    std::uniform_real_distribution<> dist(0.0, 1.0);
    
    for (long long i = 0; i < N; i++)
    {
        x = dist(gen);
        y = dist(gen);
        // x = (double)rand() / RAND_MAX;
        // y = (double)rand() / RAND_MAX;
=======

    long long i;
    #pragma omp parallel for schedule(auto) reduction(+: result) private(x, y)
    
        // int thread_num = omp_get_thread_num();

        // //seed held by each thread
        // std::mt19937 thread_gen;
        // //use thread id and xor operation to modify a local seed
        // //to ensure every thread will access a different random seed and thus keep the thread safety
        // thread_gen.seed(rd() ^ thread_num);
        // std::uniform_real_distribution<> dist(0.0, 1.0);

        for (i = 0; i < N; i++)
        {
            // x = dist(thread_gen);
            // y = dist(thread_gen);
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;
            if (x * x + y * y < 1) result++;
        }
    

    return result / N;
}


double his() 
{
    double pi;
    int inside = 0;
    double x, y;

    #pragma omp parallel for reduction(+:inside) private(x, y)
    for (long long i = 0; i < N; i++) {
        x = (double)rand() / RAND_MAX; // 生成0到2之间的随机数
        y = (double)rand() / RAND_MAX; // 生成0到2之间的随机数
        if (x * x + y * y <= 1) {
            inside++;
        }
    }

    pi = 4.0 * inside / N;
    //printf("Estimated Pi = %f\n", pi);

    return 0;
}

double calSerial() 
{
    // std::random_device rd;
    // std::mt19937 gen(rd());
    double result = 0;
    double x, y;
    // std::uniform_real_distribution<> dist(0.0, 1.0);
    
    for (long long i = 0; i < N; i++)
    {
        // x = dist(gen);
        // y = dist(gen);
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
>>>>>>> 7c45cdc5b20d6b8ff210259ff7fc3c337cd3a021
        if (x * x + y * y < 1) result++;
    }
    return result / N;
}

int main()
{
    clock_t startParallel = clock();
<<<<<<< HEAD
    double ansParallel = calParallel();
=======
    double ansParallel = calParallel() * 4;
>>>>>>> 7c45cdc5b20d6b8ff210259ff7fc3c337cd3a021
    clock_t endParallel = clock();
    double runTimeParallel = (double)(endParallel - startParallel) / CLOCKS_PER_SEC;
    std::cout << "Parallel result is " << ansParallel << ", and the runtime is " << runTimeParallel << std::endl;
    
    clock_t startSerial = clock();
    double ansSerial = calSerial() * 4;
    clock_t endSerial = clock();
    double runTimeSerial = (double)(endSerial - startSerial) / CLOCKS_PER_SEC;
    std::cout << "Serial result is " << ansSerial << ", and the runtime is " << runTimeSerial << std::endl;

    clock_t startHis = clock();
    double ansHis = his();
    clock_t endHis = clock();
    double runTimeHis = (double)(endHis - startHis) / CLOCKS_PER_SEC;
    std::cout << "His result is " << ansHis << ", and the runtime is " << runTimeHis << std::endl;
    
    return 0;
}
