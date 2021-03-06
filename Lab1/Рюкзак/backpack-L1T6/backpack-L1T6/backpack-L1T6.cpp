#include "stdafx.h"
using namespace std;

struct Thing
{
	int number = 0;
	int weight = 0;
	int cost = 0;
};

void IncrementComb(vector <bool>& combination, size_t startPosition)
{
	if (combination[startPosition] == false)
	{
		combination[startPosition] = true;
	}
	else
	{
		combination[startPosition] = false;
		if (combination.size() > startPosition + 1)
		{
			IncrementComb(combination, startPosition + 1);
		}
	}
}

Thing AssembleBackPack(const vector<Thing>& listThings, const vector<bool>& combination)
{
	Thing tempBackPack;
	tempBackPack.weight = 0;
	tempBackPack.cost = 0;

	for (size_t i = 0; i < combination.size(); ++i)
	{
		if (combination[i])
		{
			tempBackPack.weight += listThings[i].weight;
			tempBackPack.cost += listThings[i].cost;
		}
	}

	return tempBackPack;
}

void FindBestCombination(const vector<Thing>& listThings, int backpackCapacity, vector <bool>& totalCombination)
{
	vector <bool> comb;
	int totalCost = 0;
	size_t quantityThings = listThings.size();

	//резервируем массив под комбинации
	for (size_t i = 0; i < quantityThings; ++i)
	{
		comb.push_back(0);
	}

	int counter = 0;
	//перебираем все комбинации, собираем на каждый рюкзак, сохряняем лучший результат
	while (counter < pow(2, quantityThings))
	{
		IncrementComb(comb, 0);
		Thing backPack;

		backPack = AssembleBackPack(listThings, comb);
		if (backPack.weight <= backpackCapacity && backPack.cost > totalCost)
		{
			totalCost = backPack.cost;
			totalCombination = comb;
		}
		counter++;
	}
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

void PrintListThings(const vector<Thing>& listThings)
{
	cout << "\n";
	int counter = 0;
	for (int i = 0; i < int(listThings.size()); ++i)
	{
		cout << "number: " << listThings[i].number << " weight: " << listThings[i].weight << " cost: " << listThings[i].cost << "\n";
	}
}

void PrintNumberThingsByCombination(const vector<Thing>& listThings, const vector<bool>& combination)
{
	for (size_t i = 0; i < combination.size(); ++i)
	{
		if (combination[i])
		{
			cout << listThings[i].number << " ";
		}
	}
	cout << "\n";
}

int main(int argc, char *argv[])
/*
Use arguments: <backPackCapacity> <file with data>
*/
{
	if (argc != 3)
	{
		cout << "Too few arguments \n";
		return 1;
	}

	int backpackCapacity = 0;

	try
	{
		backpackCapacity = stoi(argv[1]);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
		return 1;
	}

	cout <<"Backpack capacity " << backpackCapacity << "\n";

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

	vector <bool> bestCombination;
	FindBestCombination(listThings, backpackCapacity, bestCombination);
	PrintNumberThingsByCombination(listThings, bestCombination);
	return 0;
}