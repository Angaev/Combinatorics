// Task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "iostream"
#include "string"
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct vertexEdgeCount
{
	int vertexCount = 0;
	int edgeCount = 0;
};

struct edge
{
	int vertex1 = 0;
	int vertex2 = 0;
	float weight = 0;
};

vector<vector<float>> LoadEdge(ifstream& file, vertexEdgeCount vertexEdge)
{
	vector<vector<float>> tempMatrix(vertexEdge.vertexCount, vector<float>(vertexEdge.vertexCount, 0.0));

	for (int counter = 0; counter < vertexEdge.edgeCount; ++counter)
	{
		int edgeFirst, edgeSecond;
		float edgeWeight;
		file >> edgeFirst >> edgeSecond >> edgeWeight;
		tempMatrix[edgeFirst - 1][edgeSecond - 1] = edgeWeight;
		tempMatrix[edgeSecond - 1][edgeFirst - 1] = edgeWeight;
	}
	return tempMatrix;
}

void PrintMatrix(vector<vector<float>>& matrix, int Num)
{
	for (int i = 0; i < Num; i++)
	{
		for (int j = 0; j < Num; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n";
}

void AddComponent(vector<int>& component, int oldNum, int newNum)
{
	for (int &elem : component)
	{
		if (elem == oldNum)
		{
			elem = newNum;
		}
	}
}

float GetSumMatrix(vector<vector<float>>& matrix)
{
	float num = 0;
	for (int i = 0; i < static_cast<int>(matrix.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(matrix.size()); j++)
		{
			num += matrix[i][j];
		}
	}
	return num;
}

bool GetNextEdge(vector<vector<float>> matrix, vector<int>& component, int compNum, edge& newEdge, vector<bool>& isVertexSelected)
{
	float minNum = GetSumMatrix(matrix);
	int newVertex1 = 0;
	int newVertex2 = 0;
	for (int i = 0; i < static_cast<int>(matrix.size()); i++)
	{
		if (component[i] == compNum)
		{
			for (int j = 0; j < static_cast<int>(matrix.size()); j++)
			{
				if ((matrix[i][j] < minNum) && (matrix[i][j] != 0) && (component[j] != compNum))
				{
					minNum = matrix[i][j];
					newVertex1 = i;
					newVertex2 = j;
				}
			}
		}
	}

	if (minNum == GetSumMatrix(matrix))
	{
		return false;
	}
	else
	{
		if ((!isVertexSelected[newVertex1]) && isVertexSelected[newVertex2])
		{
			component[newVertex1] = component[newVertex2];
		}
		else
		{
			AddComponent(component, component[newVertex2], compNum);
		}
		if (!isVertexSelected[newVertex1]) isVertexSelected[newVertex1] = true;
		if (!isVertexSelected[newVertex2]) isVertexSelected[newVertex2] = true;
		newEdge.vertex1 = newVertex1;
		newEdge.vertex2 = newVertex2;
		newEdge.weight = minNum;
		return true;
	}
}

vector<int> CreatePermutation(int vertexCount)
{
	vector<int> result(vertexCount, 0);
	for (int i = 0; i < vertexCount; i++)
	{
		result[i] = i;
	}
	return result;
}

void BoruvkasAlgorithm(vector<vector<float>> matrix, int vertexCount, vector<edge>& edgesList)
{
	vector<int> component = CreatePermutation(vertexCount);
	vector<bool> isVertexSelected(matrix.size(), false);
	*isVertexSelected.begin() = true;
	int i = 1;
	while (edgesList.size() < (matrix.size() - 1))
	{
		vector<int>uniqueComponent = component;
		sort(uniqueComponent.begin(), uniqueComponent.end());
		auto last = unique(uniqueComponent.begin(), uniqueComponent.end());
		uniqueComponent.erase(last, uniqueComponent.end());
		int j = 1;
		for (auto comp : uniqueComponent)
		{
			edge newEdge;
			if (GetNextEdge(matrix, component, comp, newEdge, isVertexSelected))
			{
				edgesList.push_back(newEdge);
			}
			j++;
		}
		i++;
	}
}


float GetMinWeightSpanningTree(vector<edge> egdes)
{
	float sumWeight = 0;
	for (const edge& edge: egdes)
	{
		sumWeight += edge.weight;
	}
	return sumWeight;
}

int main(const int argc, const char* argv[])
{
	if (argc != 2) 
	{
		cout << "Wrong argument count\n";
		return 1;
	}

	string fileName = argv[1];
	vertexEdgeCount vertexEdge;
	
	ifstream file;
	file.open(fileName);
	if (!file)
	{
		cout << "Can't open file \n";
		return 1;
	}
	file >> vertexEdge.vertexCount >> vertexEdge.edgeCount;
	vector<vector<float>> matrix = LoadEdge(file, vertexEdge);
	vector<edge>egdes;
	BoruvkasAlgorithm(matrix, vertexEdge.vertexCount, egdes);

	cout << GetMinWeightSpanningTree(egdes) << "\n";
	for (const edge& edge : egdes)
	{
		cout << edge.vertex1 + 1 << " " << edge.vertex2 + 1 << "  " << edge.weight << "\n";
	}
}

