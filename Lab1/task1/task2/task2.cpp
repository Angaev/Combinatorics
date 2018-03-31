// task2.cpp: определяет точку входа для консольного приложения.
//

/*
Реализовать алгоритм порождения перестановок в лексикографическом
порядке с выводом времени работы до сотых секунд.
*/
#include "stdafx.h"


int main()
{
	std::vector<size_t> v = { 3, 2, 1 };
	boost::timer t;

	t.restart();
	std::sort(v.begin(), v.end());
	do
	{
		copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
		std::cout << std::endl;
	} while (std::next_permutation(v.begin(), v.end()));
	double duration = t.elapsed();

	std::cout << duration << std::endl;
	return 0;
}
