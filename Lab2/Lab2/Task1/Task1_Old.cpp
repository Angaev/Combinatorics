// Task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

void PrintMatrix(vector<vector<int>> &matrix, int const vertexCount)
{
	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			cout << matrix[i][j]<<" ";
		}
		cout << "\n";
	}
}

bool LoadVertexCount(ifstream & file, int &vertexCount)
{
	if (file >> vertexCount)
	{
		if (vertexCount >= 1 && vertexCount <= 400)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool LoadEdgeCount(ifstream & file, int const& vertexCount, int & edgeCount)
{
	if (file >> edgeCount)
	{
		if (edgeCount >= 0 && edgeCount <= ((vertexCount * (vertexCount-1) / 2)))
		{
			return true;
		}
		return false;
	}
	return false;
}

bool LoadGrafFromFile(string const& fileName, int &vertexCount, int &edgeCount, vector<vector<int>> &matrix)
{
	ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		cout << "Can't open file\n";
		return false;
	}

	if (!LoadVertexCount(file, vertexCount))
	{
		cout << "Can't read vertex from file\n";
		return false;
	}

	if (!LoadEdgeCount(file, vertexCount, edgeCount))
	{
		cout << "Can't read egde from file\n";
		return false;
	}
	int vertex1 = 0;
	int vertex2 = 0;

	for (int i = 0; i < vertexCount; i++)
	{
		matrix.push_back(vector<int> {});
	}

	for (int i = 0; i < vertexCount; i++)
	{
		matrix[i].push_back(0);
	}

	/*
	while (file >> vertex1 && file >> vertex2)
	{
		matrix[vertex1 - 1][vertex2 - 1] = 1;
	}*/
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong angument count \n";
		return false;
	}
	string fileName = argv[1];
	int vertexCount = 0;
	int edgeCount = 0;
	vector<vector<int>> matrix;
	LoadGrafFromFile(fileName, vertexCount, edgeCount, matrix);
	//PrintMatrix(matrix, vertexCount);
    return 0;
}

