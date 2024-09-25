#include <iostream>
#include <vector>
#include <omp.h>

//partly merge
std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) 
{
    std::vector<int> result{};
    unsigned int leftLength = 0;
    unsigned int rightLength = 0;

    //make sure every part is sorted minor to prior
    while (leftLength < left.size() && rightLength < right.size()) 
    {
        if (left.at(leftLength) < right.at(rightLength)) 
        {
            result.push_back(left.at(leftLength));
            leftLength++;
        } 
        else 
        {
            result.push_back(right.at(rightLength));
            rightLength++;
        } 
    }

    //push left elements into the vector result
    while (leftLength < left.size()) 
    {
        result.push_back(left.at(leftLength));
        leftLength++;
    }
    while (rightLength < right.size()) 
    {
        result.push_back(right.at(rightLength));
        rightLength++;
    }

    return result;
}


std::vector<int> mergeSort(std::vector<int>& vec, int threads) 
{
    //terminant judgement
    if (vec.size() == 1) return vec;

    std::vector<int>::iterator mid = vec.begin() + (vec.size() / 2);
    std::vector<int> left {vec.begin(), mid};
    std::vector<int> right{mid, vec.end()};

    //optimization with openmp
    if (threads > 1) 
    {
        #pragma omp parallel sections 
        {
            #pragma omp section 
            {
                left =  mergeSort(left, threads / 2);
            }
            #pragma omp section 
            {
                right = mergeSort(right, threads - threads / 2);
            }
        }
    } 
    else 
    {
        left = mergeSort(left, 1);
        right = mergeSort(right, 1);
    }

    return merge(left, right);
} 


int main(int argc, char *argv[]) 
{

    omp_set_num_threads(8);

    std::vector<int> vec(1000000);
    for (int i = 0; i < vec.size(); i++) 
    {
        vec.at(i) = (long long)(i * i) % 1000000;
    }
    vec = mergeSort(vec, 1);
    for (int i = 0; i < vec.size(); i++) 
    {
        std::cout << vec.at(i) << "\t";
    }
    return 0;
}