// task2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

typedef vector<vector<int>> matrix;

void PrepareMatrix(matrix &matr, ifstream &input)
{
	string vertexAmount;
	getline(input, vertexAmount);
	auto number = stoi(vertexAmount);

	vector<int> row(number, 0);
	matr.assign(number, row);
}

void FillMatrix(matrix &matr, std::string const &s)
{
	istringstream inputStream(s);
	unsigned int from, to, capacity;
	inputStream >> from >> to >> capacity;

	if ((from >= matr.size()) || (to >= matr.size()) || (from == to))
	{
		std::cout << "Incorrect edge: " << from << " " << to << std::endl;
	}
	else
	{
		matr[from][to] = capacity;
	}
}

void LoadMatrix(matrix &matr, string const &input)
{
	ifstream inputFile(input);
	string itemString;
	PrepareMatrix(matr, inputFile);

	while (getline(inputFile, itemString))
	{
		FillMatrix(matr, itemString);
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Input format: <program>.exe <inputFile>\n";
		return 1;
	}

	matrix egdes;

	string fileName = argv[1];

	LoadMatrix(egdes, fileName);

    return 0;
}

