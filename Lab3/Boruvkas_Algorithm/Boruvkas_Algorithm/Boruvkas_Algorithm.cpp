// Boruvkas_Algorithm.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

struct Edge
{
	Edge() = default;

	Edge(size_t vertex1, size_t vertex2, size_t weight) :
		m_vertex1(vertex1),
		m_vertex2(vertex2),
		m_weight(weight)
	{

	}
	size_t m_vertex1, m_vertex2;
	size_t m_weight;

};

struct Graf
{
	size_t vertexCount = 0;
	size_t edgeCount = 0;
	vector<Edge> edgeList;
};

struct Tree
{
	//вектор вершин
};

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

Graf ReadDataFromFile(std::ifstream & input)
{
	Graf data;

	input >> data.vertexCount >> data.edgeCount;

	string tempLine;
	if (getline(input, tempLine).eof())
	{
		return data;
	}
	vector<Edge> tempEdgeList;

	//построчное считывание ребер 
	for (int i = 0; i < static_cast<int>(data.edgeCount); i++)
	{
		getline(input, tempLine);
		stringstream streamLine(tempLine);

		data.edgeList.resize(data.edgeCount);

		int	lineNumber = 0;
		size_t vertex1;
		size_t vertex2;
		size_t weight;

		
		while (!streamLine.eof())
		{
			streamLine >> vertex1; //считали 1 вершину
			streamLine >> vertex2; //считали 2 вершину
			streamLine >> weight; //считали вес

			//теперь надо это все сохранить в лист 
			Edge edge(vertex1, vertex2, weight);

			tempEdgeList.push_back(edge);

			lineNumber++;
		}

		if (input.eof())
		{
			break;
		}

	}

	data.edgeList = move(tempEdgeList);
	return data;
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
	Graf graf = ReadDataFromFile(inputFile);

	//ну дальше кароче сам алгорит Борувки
	/*
	1. все вершины - остравные деревья
	
	*/

    return 0;
}

