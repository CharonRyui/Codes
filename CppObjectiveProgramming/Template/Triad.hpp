template <typename T, typename U, typename I>

class Triad
{
    T m_num1;
    U m_num2;
    I m_num3;

public:
    Triad(T num1, U num2, I num3);
    T getNum1() const {return m_num1;}
    U getNum2() const {return m_num2;}
    I getNum3() const {return m_num3;}
};