#include <iostream>
#include "Triad.cpp"
using namespace std;

int main(int argc, char **argv)
{
    Triad<int, int, int> t1{ 1, 2, 3 };
	print(t1);
	std::cout << '\n';
	std::cout << t1.getNum1() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1, 2.3, "Hello"s };
	print(t2);
	std::cout << '\n';

    return 0;
}