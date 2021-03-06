// KuhnAlgorithm.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

struct KuhnData
{
	int leftSetCount, rightSetCount;
	std::vector<std::vector<int>> edgeList;
	std::vector<int> matchingPair; //Согласование пар 
	std::vector<bool> usedPair; //Пройденные пары 
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
		return false;
	}
	return true;
}

bool CanOpenFile(std::string const& fileName, std::ifstream& inputFile)
{
	inputFile = std::ifstream(fileName);
	if (!inputFile.is_open())
	{
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

		data.edgeList.resize(data.leftSetCount);

		int	vertexNumber = 0;
		bool isEdge;
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

bool UseKuhn(KuhnData& data, int vertex)
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

void PrintResultKuhn(KuhnData data)
{
	bool isHaveSolution = false;

	for (size_t vertex = 0; vertex < data.rightSetCount; vertex++)
	{
		if (data.matchingPair[vertex] != -1)
		{
			if (!isHaveSolution)
			{
				cout << "Yes\n";
				isHaveSolution = true;
			}
			cout << data.matchingPair[vertex] + 1 << ' ' << vertex + 1 << "\n";
		}
	}

	if (!isHaveSolution)
	{
		cout << "No\n";
	}
}

int main(int argc, char* argv[])
{
	if (!CheckArgumentCount(argc))
	{
		cout << "wrong argument count\n";
		return 1;
	}

	ifstream inputFile;

	if (!CanOpenFile(argv[1], inputFile))
	{
		cout << "Failed to open file for reading!";
		return 1;
	}

	KuhnData graf = ReadDataFromFile(inputFile);
	//cout << graf.leftSetCount << " -- " << graf.rightSetCount << "\n";
	SolveKuhn(graf);

	PrintResultKuhn(graf);

	return 0;
}

