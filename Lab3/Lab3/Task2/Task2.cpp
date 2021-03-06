// Task2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "iostream"
#include "string"
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<float>> matrix;

matrix GetGraf(ifstream& file, int vertexCount)
{
	matrix matrix(vertexCount, vector<float>(vertexCount, 0.0));
	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			file >> matrix[i][j];
		}
	}
	return matrix;
}

int GetVertexCount(ifstream& file)
{
	int count;
	file >> count;
	return count;
}

float GetSumMatrixElement(matrix matrix)
{
	float sum = 0;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix.size(); j++)
		{
			sum += matrix[i][j];
		}
	}
	return sum;
}

int GetDegreeVertex(int i, matrix inputMatrix, float sumMatrixElement)
{
	int degreeVertex = 0;
	for (size_t j = 0; j < inputMatrix.size(); j++)
	{
		if ((inputMatrix[i][j] > 0) && (inputMatrix[i][j] < sumMatrixElement))
		{
			degreeVertex++;
		}
	}
	return degreeVertex;
}

matrix GetKirchhoffMatrix(matrix inputMatrix, float sumMatrixElement)
{
	matrix kirchhoffMatrix;
	kirchhoffMatrix.resize(inputMatrix.size());
	for (size_t i = 0; i < inputMatrix.size(); i++)
	{
		kirchhoffMatrix[i].resize(inputMatrix.size());
	}
	for (size_t i = 0; i < inputMatrix.size(); i++)
	{
		for (size_t j = 0; j < inputMatrix.size(); j++)
		{
			if (i == j) 
			{
				kirchhoffMatrix[i][j] = GetDegreeVertex(i, inputMatrix, sumMatrixElement);
			}
			if ((i != j) && (inputMatrix[i][j] > 0) && (inputMatrix[i][j] < sumMatrixElement))
			{
				kirchhoffMatrix[i][j] = -1;
			}
		}
	}
	return kirchhoffMatrix;
}

void calculateMinorIndex(int counterValue, int minorValue, int& index)
{
	if (counterValue > minorValue)
	{
		index = counterValue + 1;
	}
	else
	{
		index = counterValue;
	}
}

matrix GetMatrixMinor(matrix inputMatrix, int row, int col)
{
	int size = inputMatrix.size();
	matrix minor(size - 1, vector<float>(size - 1, 0.0));
	int rowIndex, colIndex;
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size - 1; j++)
		{
			calculateMinorIndex(i, row, rowIndex);
			calculateMinorIndex(j, col, colIndex);
			minor[i][j] = inputMatrix[rowIndex][colIndex];
		}
	}

	return minor;
}

bool IsNullRow(int row, matrix inputMatrix)
{
	bool result = true;
	for (size_t i = 0; i < inputMatrix.size(); i++)
	{
		result = (abs(inputMatrix[row][i]) < FLT_EPSILON);
		if (!result)
		{
			return false;
		}
	}
	return result;
}

float GetDeterminant(matrix inputMatrix)
{
	for (size_t i = 0; i < inputMatrix.size() - 1; i++)
	{
		if (!(abs(inputMatrix[i][i]) < FLT_EPSILON))
		{
			float c = inputMatrix[i][i];
			for (size_t j = i + 1; j < inputMatrix.size(); j++)
			{
				float d = inputMatrix[j][i];
				for (size_t k = 0; k < inputMatrix.size(); k++)
				{
					inputMatrix[j][k] -= (d / c) * inputMatrix[i][k];
				}
			}
		}
		else
		{
			if (IsNullRow(i, inputMatrix))
			{
				break;
			}
			for (size_t k = 0; k < inputMatrix.size(); k++)
			{
				swap(inputMatrix[i][k], inputMatrix[i + 1][k]);
			}
		}
	}

	float determinant = 1;
	for (size_t i = 0; i < inputMatrix.size(); i++)
	{
		determinant *= inputMatrix[i][i];
	}

	return determinant;
}

float GetSpanningTreeCount(matrix kirchhoff, float sumMatrixElement)
{
	matrix minor = GetMatrixMinor(kirchhoff, 0, 0);
	return GetDeterminant(minor);
}

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong count arguments \n";
		return 1;
	}

	string fileName = argv[1];
	ifstream file(fileName);
	if (!file)
	{
		cout << "Can't open file \n";
		return 1;
	}
	int vertexCount = GetVertexCount(file);
	if ((vertexCount < 1) || (vertexCount > 8))
	{
		cout << "Wrong count vertex \n";
		return 1;
	}
	matrix graf = GetGraf(file, vertexCount);
	float sumMatrixElement = GetSumMatrixElement(graf);
	matrix kirchhoff = GetKirchhoffMatrix(graf, sumMatrixElement);

	cout << GetSpanningTreeCount(kirchhoff, sumMatrixElement) << "\n";
	return 0;
}

