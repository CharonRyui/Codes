#include <iostream>
#include <omp.h>
#include <random>

#define N 10000000 // 总的迭代次数

double calParallel()
{
    double result = 0.0;  // 全局计数器 result

    // 定义并行区域，使用 reduction 进行归约
    #pragma omp parallel reduction(+:result)
    {
        // 线程独立的随机数生成器
        std::random_device rd;
        thread_local std::mt19937 thread_gen(rd() ^ omp_get_thread_num());
        std::uniform_real_distribution<> dist(0.0, 1.0);

        // 使用动态调度
        #pragma omp for schedule(dynamic)
        for (long long i = 0; i < N; i++)
        {
            double x = dist(thread_gen);  // 生成随机 x
            double y = dist(thread_gen);  // 生成随机 y

            // 判断点是否落在单位圆内
            if (x * x + y * y < 1)
            {
                result += 1.0;  // 累加局部结果
            }
        }
    }

    return result / N;
}

double calSerial()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    double result = 0.0;
    for (long long i = 0; i < N; i++)
    {
        double x = dist(gen);
        double y = dist(gen);

        if (x * x + y * y < 1)
        {
            result++;
        }
    }
    return result / N;
}

int main()
{
    // 并行计算
    clock_t startParallel = clock();
    double ansParallel = calParallel() * 4;  // 并行计算 PI
    clock_t endParallel = clock();
    double runTimeParallel = (double)(endParallel - startParallel) / CLOCKS_PER_SEC;
    std::cout << "Parallel result is " << ansParallel << ", and the runtime is " << runTimeParallel << " seconds." << std::endl;

    // 串行计算
    clock_t startSerial = clock();
    double ansSerial = calSerial() * 4;  // 串行计算 PI
    clock_t endSerial = clock();
    double runTimeSerial = (double)(endSerial - startSerial) / CLOCKS_PER_SEC;
    std::cout << "Serial result is " << ansSerial << ", and the runtime is " << runTimeSerial << " seconds." << std::endl;

    return 0;
}
