#include "stdafx.h"

using namespace std;
constexpr int MAX_MATRIX_SIZE = 15;
using matrix = int[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];

bool LoadmatrixFromFile(string const& fileName, matrix &matrix, int & matrixSize)
{
	ifstream matrixFile;
	matrixFile.open(fileName);
	string line;
	if (!matrixFile.is_open())
	{
		return false;
	}
	getline(matrixFile, line);
	matrixSize = stoi(line);
	for (int i = 0; i < matrixSize; i++)
	{
		if (!getline(matrixFile, line))
		{
			return false;
		}
		istringstream row(line);
		for (int j = 0; j < matrixSize; j++)
		{
			row >> matrix[i][j];
			if (row.fail())
				return false;
		}
	}

	return true;
}

void PrintMatrix(matrix const& matrix, int const& matrixSize)
{
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			cout << fixed << setprecision(3) << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

void ResetPermutation(vector<int> & permutation, int size)
{
	for (int i = 0; i < size; i++)
	{
		permutation.push_back(i);
	}
}

size_t CalculateDistanceOfWay(vector<int> const& permutation, matrix matrix)
{
	size_t distance = 0;
	for (int i = 0; i < permutation.size(); i++)
	{
		int j = (i + 1) % permutation.size();
		if (matrix[permutation[i]][permutation[j]] == 0)
		{
			return 0;
		}
		else
		{
			distance += matrix[permutation[i]][permutation[j]];
		}
	}

	return distance;
}

void PrintIntVectorWithOffset1(vector<int> const& arr)
{
	for_each(arr.begin(), arr.end(), [](int item) {cout << item + 1 << " "; });
}

int main(int argc, char * argv[])
{
	matrix matrix;
	int matrixSize;
	string fileName;
	if (argc != 2)
	{
		cout << "wrong argument!\n";
		return 1;
	}
	try
	{
		fileName = argv[1];
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
		return 1;
	}
	LoadmatrixFromFile(fileName, matrix, matrixSize);
	//PrintMatrix(matrix, matrixSize);
	vector<int> permutation;
	vector<int> bestPermutation;
	size_t minLen = 100000;

	ResetPermutation(permutation, matrixSize);
	do
	{
		size_t distance = CalculateDistanceOfWay(permutation, matrix);
		if ((distance != 0) && (minLen > distance))
		{
			minLen = distance;
			bestPermutation = permutation;
		}
	} while (next_permutation(permutation.begin() + 1, permutation.end()));
	
	cout << "Min length: " << minLen << "\n";
	cout << "This route: \n" ;
	PrintIntVectorWithOffset1(bestPermutation);
	cout << "\n";
    return 0;
}

