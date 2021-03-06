// CombinationGenerator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void IncrementComb(vector <bool>& comb, int position)
{
	if (comb[position] == false)
	{
		comb[position] = true;
	} 
	else
	{
		comb[position] = false;
		if (comb.size() > position + 1)
		{
			IncrementComb(comb, position + 1);
		}
	}
}

void PrintVector(vector<bool> comb)
{
	copy(comb.begin(), comb.end(), ostream_iterator<int>(cout, " "));
	cout << "\n";
}

void PrintAllCombination(int arrSize)
{
	vector <bool> comb;

	for (int i = 0; i < arrSize; ++i)
	{
		comb.push_back(0);
	}

	PrintVector(comb);
	cout << "\n\n\n";
	int counter = 0;
	// Должно получиться 2^arrSize комбинаций
	while (counter < pow(2, arrSize))
	{
		IncrementComb(comb, 0);
		PrintVector(comb);
		//Сюда вставить сборку рюкзака
		counter++;

	}
}

int main()
{
	int arrSize = 0;
	cout << "Enter array size: ";
	cin >> arrSize;

	PrintAllCombination(arrSize);

    return 0;
}

