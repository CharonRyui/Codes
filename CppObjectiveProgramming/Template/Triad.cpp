#include "Triad.hpp"
#include <iostream>

template <typename T, typename U, typename I>
Triad<T, U, I>::Triad(T num1, U num2, I num3)
    : m_num1{num1}
    , m_num2{num2}
    , m_num3{num3} 
{
}

template <typename T, typename U, typename I>
void print(Triad<T, U, I> t)
{
    std::cout << t.getNum1() << " " << t.getNum2() << " " << t.getNum3() << std::endl;
}