// task2.cpp: определяет точку входа для консольного приложения.
//

/*
Реализовать алгоритм порождения перестановок в лексикографическом
порядке с выводом времени работы до сотых секунд.
*/
#include "stdafx.h"
#define size_permutation 3
#define size_array 5
using namespace std;


int main()
{
	boost::timer t;
	vector<int> c;
	c.push_back(-1);
	int n = size_array;
	int k = size_permutation;

	int i = 1;
	for (i = 1; i <= k; ++i)
	{
		c.push_back(i);
	}
	int j = 1;
	t.restart();

	while (j != 0)
	{
		copy(c.begin() + 1, c.begin() + 1 + k, ostream_iterator<size_t>(cout, " "));
		cout << "\n";
		j = k;
		while (c[j] == (n - k + j))
		{
			j = j - 1;
		}
		c[j] = c[j] + 1;
		for (i = j +1; i <= k; i++)
		{
			c[i] = c[i - 1] + 1;
		}
	}

	double duration = t.elapsed();
	cout << duration << endl;
	return 0;
}
