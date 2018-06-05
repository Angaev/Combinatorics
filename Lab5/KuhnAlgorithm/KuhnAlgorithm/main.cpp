// KuhnAlgorithm.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

struct KuhnData
{
	int leftSetCount, rightSetCount;
	std::vector<std::vector<int>> edgeList;
	std::vector<int> matchingPair; //Согласование пар массива
	std::vector<bool> usedPair; //Пройденные пары массива
};

using namespace std;

void PrintStringVector(vector<int> const& vec)
{
	for (auto i = vec.begin(); i != vec.end(); ++i)
		std::cout << *i << ' ';
	cout << "\n";
}

bool CheckArgumentCount(int argc)
{
	if (argc != 2)
	{
		cout << "wrong argument count\n";
		return false;
	}
	return true;
}

bool CanOpenFile(std::string const& fileName, std::ifstream& inputFile)
{
	inputFile = std::ifstream(fileName);
	if (!inputFile.is_open())
	{
		cout << "Failed to open file for reading!";
		return false;
	}

	return true;
}

KuhnData ReadDataFromFile(ifstream& input)
{
	KuhnData data;

	input >> data.leftSetCount >> data.rightSetCount;
	
	string tempLine;
	if (getline(input, tempLine).eof())
	{
		return data;
	}

	//построчное считывание
	for (int i = 0; i < data.leftSetCount; i++)
	{
		getline(input, tempLine);
		stringstream streamLine(tempLine);

		int	vertexNumber = 0;
		bool isEdge = false;
		while (!streamLine.eof())
		{
			streamLine >> isEdge;
			if (isEdge)
			{
				data.edgeList[i].push_back(vertexNumber);
			}

			vertexNumber++;
		}

		if (input.eof())
		{
			break;
		}

	}

	return data;
}

bool UseKuhn(KuhnData& data, size_t vertex)
{
	if (data.usedPair[vertex])
	{
		return false;
	}

	data.usedPair[vertex] = true;
	for (size_t i = 0; i < data.edgeList[vertex].size(); ++i)
	{
		int to = data.edgeList[vertex][i];
		if (data.matchingPair[to] == -1 || UseKuhn(data, data.matchingPair[to]))
		{
			data.matchingPair[to] = vertex;
			return true;
		}
	}
	return false;
}

void SolveKuhn(KuhnData & data)
{
	data.matchingPair.assign(data.rightSetCount, -1);
	for (int vertexNumber = 0; vertexNumber < data.leftSetCount; vertexNumber++)
	{
		data.usedPair.assign(data.leftSetCount, false);
		UseKuhn(data, vertexNumber);
	}
}

int main(int argc, char* argv[])
{
	if (CheckArgumentCount(argc))
	{
		return 1;
	}

	ifstream inputFile;

	if (!CanOpenFile(argv[1], inputFile))
	{
		return 1;
	}

	KuhnData graf = ReadDataFromFile(inputFile);



	return 0;
}

