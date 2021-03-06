// Task2_v2.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <boost/timer.hpp>
using namespace std;

int main()
{
	const size_t SIZE = 12;

	vector<size_t> pi;

	for (size_t i = 1; i <= SIZE; ++i)
	{
		pi.push_back(i);
	}
	//copy(pi.begin(), pi.end(), ostream_iterator<size_t>(cout, " "));
	//cout << "\n";
	boost::timer timer;
	timer.restart();
	bool elementToMoveFound = true;

	do
	{
		elementToMoveFound = false;
		size_t m = 0;
		for (size_t i = pi.size() - 1; i > 0; --i)
		{
			if (pi[i - 1] < pi[i])
			{
				m = i - 1;
				elementToMoveFound = true;
				break;
			}
		}

		if (elementToMoveFound)
		{
			size_t k = m + 1;
			size_t min = pi[k];
			for (size_t i = m + 1; i < pi.size(); ++i)
			{
				if ((pi[i] > pi[m]) && (pi[i] < min))
				{
					k = i;
					min = pi[i];
				}
			}
			swap(pi[m], pi[k]);

			reverse(pi.begin() + m + 1, pi.end());
		}

		//copy(pi.begin(), pi.end(), ostream_iterator<size_t>(cout, " "));
		//cout << "\n";
	} while (elementToMoveFound);
	double time = timer.elapsed();
	cout << time << "\n";
	return 0;
}