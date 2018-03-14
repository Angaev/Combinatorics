#include "stdafx.h"
using namespace std;

/*
тесты 
1. Что это не жадный алгоритм
2. Что весь рюкзак заполняется (10 предметов, вместимость 10, цена каждого 1)
3. Дорогой предмет (100 руб, вес >= 1/2 грузоподъемности), и другие (вес = 1/2 рюкзака, цена дешевка), в результате в рюкзаке будет один дорогой предмет и пустое место
*/

struct Thing
{
	int number = 0;
	int weight = 0;
	int cost = 0;
};

Thing AssembleBackPack(const vector<Thing> & listThings, const vector<int> & combination)
{
	Thing tempBackPack;
	tempBackPack.weight = 0;
	tempBackPack.cost = 0;

	for (size_t i = 1; i < combination.size(); ++i)
	{
		tempBackPack.weight += listThings[combination[i]].weight;
		tempBackPack.cost += listThings[combination[i]].cost;
	}

	return tempBackPack;
}

void printBestAssemlyBackPack(const vector<Thing> & listThings, int backpackCapacity)
{
	int totalCost = 0;

	size_t counter = 1;
	size_t listSize = listThings.size() - 1;
	vector<int> totalCombination;
	Thing backPack;

	
	while (counter <= listSize)
	{
		vector<int> tempCombination(counter + 1);
		tempCombination[0] = -1;

		for (size_t i = 1; i <= counter; ++i)
		{
			tempCombination[i] = i;
		}
		size_t j = 1;

		while (j != 0)
		{
			backPack = AssembleBackPack(listThings, tempCombination);

			if (backPack.weight < backpackCapacity && backPack.cost > totalCost)
			{
				totalCost = backPack.cost;
				totalCombination = tempCombination;
			}

			j = counter;

			while (tempCombination[j] == listSize - counter + j)
			{
				j--;
			}
			tempCombination[j]++;
			for (size_t i = j + 1; i <= counter; ++i)
			{
				tempCombination[i] = tempCombination[i - 1] + 1;
			}
		}
		counter++;
	}

	copy(totalCombination.begin() + 1, totalCombination.end(), ostream_iterator<int>(cout, " "));
	cout << "\n";
}

bool loadListThings(string path, vector<Thing> & listThings)
{
	ifstream file;
	file.open(path);
	if (!file.is_open())
	{
		return false;
	}

	Thing thing;
	thing.number = 0;
	while (!file.eof())
	{
		thing.number++;
		file >> thing.weight;
		file >> thing.cost;
		listThings.push_back(thing);
	}
	return true;
}

void printListThings(const vector<Thing> & listThings)
{
	cout << "\n";
	int counter = 0;
	for (int i = 0; i < int(listThings.size()); ++i)
	{
		cout << "number: " << listThings[i].number << " weight: " << listThings[i].weight << " cost: " << listThings[i].cost << "\n";
	}
}

int main(int argc, char *argv[])
/*
Use arguments: <backPackCapacity> <file with data>
*/
{
	if (argc < 3)
	{
		cout << "Too few arguments \n";
		return 1;
	}

	int backpackCapacity = stoi(argv[1]);
	cout <<"Backpack capacity " <<backpackCapacity << "\n";

	vector<Thing> listThings;
	
	if (!loadListThings(argv[2], listThings))
	{
		cout << "Error on read file! \n";
		return 1;
	}
	else
	{
		cout << "Load list of things! \n";
	}

	cout << "It's best to take things with numbers: \n";
	printBestAssemlyBackPack(listThings, backpackCapacity);
	return 0;
}