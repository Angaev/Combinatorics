#include "stdafx.h"
using namespace std;

struct Thing
{
	int number = 0;
	int weight = 0;
	int cost = 0;
};

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
	for (int i = 0; i < listThings.size(); ++i)
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


	return 0;
}