// task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;

void PrintPermutation(const vector <size_t> printable)
{
	copy(printable.begin() + 1, printable.end() - 1, ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}


int main()
{
	constexpr size_t size = 10;
	boost::timer timer;
	vector <size_t> currentPermutation(size + 2);
	vector <size_t> reversePermutation(size + 2);
	vector <size_t> direction(size + 2);

	for (size_t i = 1; i <= size; i++)
	{
		currentPermutation[i] = i;
		reversePermutation[i] = i;
		direction[i] = -1;
	}

	direction[1] = 0;
	size_t m = size + 1;
	currentPermutation[0] = m;
	currentPermutation[size + 1] = m;
	timer.restart();
	while (m != 1)
	{
		m = size;

		while (currentPermutation[reversePermutation[m] + direction[m]] > m)
		{
			direction[m] *= -1;
			m = m - 1;
		}

		//PrintPermutation(currentPermutation);
		swap(currentPermutation[reversePermutation[m]], currentPermutation[reversePermutation[m] + direction[m]] );
		swap(reversePermutation[currentPermutation[reversePermutation[m]]], reversePermutation[m]);
	}

	cout << timer.elapsed() << endl;
    return 0;
}

