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
	try
	{
		if ((from >= matr.size()) || (to >= matr.size()) || (from == to))
		{
			throw;
		}
		else
		{
			matr[from][to] = capacity;
		}
	}
	catch (...)
	{
		std::cout << "Incorrect edge: " << from << " " << to << std::endl;
	}
	
}

matrix PrepareFlowMatrix(int size)
{
	matrix flowMatrix(size, vector<int>(size));
	return flowMatrix;
}

unsigned PushRelabelToFront(matrix input, matrix & output)
{
	//количество вершин
	const unsigned vertexAmount = input.size();
	//высота вектора
	std::vector<int> vertexHeight(vertexAmount, 0);
	vertexHeight[0] = vertexAmount;


	for (unsigned int i = 1; i < vertexAmount; ++i)
	{
		output[0][i] = input[0][i];
		output[i][0] = -input[0][i];
	}

	vector<int> currentVertexRow(vertexAmount);
	copy(output[0].begin(), output[0].end(), currentVertexRow.begin());

	while (true)
	{
		unsigned currentVertex = 1;
		for (unsigned i = currentVertex; i < vertexAmount; ++i)
		{
			if (currentVertexRow[i] > 0)
			{
				currentVertex = i;
				break;
			}

			if (i == vertexAmount - 1)
				currentVertex = ++i;
		}

		if (currentVertex == vertexAmount - 1)
		{
			break;
		}

		unsigned nextDistanationVertex = 0;
		for (unsigned i = nextDistanationVertex; i < vertexAmount; ++i)
		{
			if ((input[currentVertex][i] - output[currentVertex][i])
				&& (vertexHeight[currentVertex] == vertexHeight[i] + 1))
			{
				nextDistanationVertex = i;
				break;
			}

			if (i == vertexAmount - 1)
				nextDistanationVertex = ++i;
		}

		if (nextDistanationVertex < vertexAmount)
		{
			int minFlowDiff = min(
				currentVertexRow[currentVertex],
				input[currentVertex][nextDistanationVertex] - output[currentVertex][nextDistanationVertex]
			);

			output[currentVertex][nextDistanationVertex] += minFlowDiff;
			output[nextDistanationVertex][currentVertex] = -output[currentVertex][nextDistanationVertex];

			currentVertexRow[currentVertex] -= minFlowDiff;
			currentVertexRow[nextDistanationVertex] += minFlowDiff;
		}
		else
		{
			int minFlow = INT_MAX;
			for (unsigned i = 0; i < vertexAmount; ++i)
				if (input[currentVertex][i] - output[currentVertex][i] > 0)
					minFlow = std::min(minFlow, vertexHeight[i]);
			try
			{
				if (minFlow == INT_MAX)
					throw;
			}
			catch (...)
			{
				cout << "failed \n";
			}
			vertexHeight[currentVertex] = minFlow + 1;
		}
	}

	unsigned flow = 0;
	for (unsigned i = 0; i < vertexAmount; ++i)
	{
		if (input[0][i])
		{
			flow += output[0][i];
		}
	}
	return flow;
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

void PrintFlowVertex(matrix flowMatrix)
{
	for (size_t i = 0; i < flowMatrix.size(); i++)
	{
		for (size_t j = 0; j < flowMatrix.size(); j++)
		{
			if (flowMatrix[i][j] > 0)
			{
				cout << i << " " << j << " " << flowMatrix[i][j] << "\n";
			}
		}
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

	matrix flowMatrix = PrepareFlowMatrix(egdes.size());
	cout << "Max flow " << PushRelabelToFront(egdes, flowMatrix) << "\n";
	PrintFlowVertex(flowMatrix);
    return 0;
}

