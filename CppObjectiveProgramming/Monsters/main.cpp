#include "MonsterGenerator.hpp"
//if you include MonsterGenerator.cpp here, you will get a multiple defined error
//caused by including cpp which include hpp again and try to define another static method with class definition
int main()
{
	Monster m{ MonsterGenerator::generate() };
	m.print();

	return 0;
}