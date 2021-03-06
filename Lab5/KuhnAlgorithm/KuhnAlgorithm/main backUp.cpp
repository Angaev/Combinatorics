// KuhnAlgorithm.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

struct KuhnData
{
	int firstSetCount, secondSetCount;
	std::vector<std::vector<int>> edgeList;
	std::vector<int> matchingPairArr; //Согласование пар массива
	std::vector<bool> usedPairArr; //Пройденные пары массива
};

using namespace std;

void PrintStringVector(vector<int> const& vec)
{
	for (auto i = vec.begin(); i != vec.end(); ++i)
		std::cout << *i << ' ';
	cout << "\n";
}

void AddValueToMatrix(vector<vector<int>> &matrix, vector<int> const& wordVector)
{
	matrix.push_back(wordVector);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong argument count! \n";
		return 1;
	}
	string fileName = argv[1];
	ifstream matrixFile;
	matrixFile.open(fileName);
	if (!matrixFile.is_open())
	{
		cout << "Can't open file \n";
		return 1;
	}


	int p, q = 0;

	string input;
	try
	{
		matrixFile >> input;
		p = stoi(input);
		input.clear();

		matrixFile >> input;
		q = stoi(input);
		input.clear();
	}
	catch (const exception & e)
	{
		cout << e.what() << "\n";
	}

	if ((p < 1) && (q > 100))
	{
		cout << "Wrong vertex count! \n";
		return 1;
	}
	cout << "p: " << p << " q: " << q << "\n";

	vector<vector<int>> matrix;
	int counter = 1;

	while (std::getline(matrixFile, input))
	{
		vector<int> wordVector;
		std::size_t prev = 0, pos;
		while ((pos = input.find_first_of(" ", prev)) != std::string::npos)
		{
			if (pos > prev)
				wordVector.push_back(stoi(input.substr(prev, pos - prev)));
			prev = pos + 1;
		}
		if (prev < input.length())
			wordVector.push_back(stoi(input.substr(prev, std::string::npos)));
		//PrintStringVector(wordVector);
		AddValueToMatrix(matrix, wordVector);
		counter++;
	}

	PrintStringVector(matrix[1]);
	PrintStringVector(matrix[2]);
	PrintStringVector(matrix[3]);
	PrintStringVector(matrix[4]);
	PrintStringVector(matrix[5]);


	return 0;
}

