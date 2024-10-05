#include <iostream>

class Fraction
{
    int m_numerator{0};
    int m_denominator{1};

public:

    Fraction() = default;

    explicit Fraction(int numerator = 0, int denominator = 1)
        : m_numerator{numerator}
        , m_denominator{denominator}
    {}

    Fraction multiple(const Fraction& f) 
    {
        m_denominator *= f.m_denominator;
        m_numerator *= f.m_numerator;
        return *this;
    }

    int getNumerator() const {return m_numerator;}
    int getDenominator() const {return m_denominator;}
};

void print(Fraction f) {
    std::cout << f.getNumerator() << '/' << f.getDenominator() << '\n';
}

int main() {
    Fraction f1{1, 2};
    Fraction f2{3, 4};
    print(f1.multiple(f2));
    return 0;
}