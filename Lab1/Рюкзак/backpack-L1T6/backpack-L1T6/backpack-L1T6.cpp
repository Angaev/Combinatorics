// backpack-L1T6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;

bool checkCountParametrs(const int argc)
{
	if (argc != 2)
	{
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (checkCountParametrs(argc))
	{
		cout << "Wrong count of paramets! Use: file-name, weight \n";
		return 1;
	}
    return 0;
}

