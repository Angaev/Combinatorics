// Task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <algorithm>
using namespace std;

const int MAXN = 10;
vector<int> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];

void IS_CUTPOINT(int v)
{
	cout << "Point: " << v << " \n";
}

void dfs(int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min(fup[v], tin[to]);
		else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] >= tin[v] && p != -1)
				IS_CUTPOINT(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
		IS_CUTPOINT(v);
}

int main() {
	int n = 5; //количество верших в входном графе
	//... чтение n и g ...

	g[0].push_back(1);
	g[0].push_back(2);

	g[1].push_back(0);
	g[1].push_back(2);
	g[1].push_back(3);
	g[1].push_back(4);

	g[2].push_back(0);
	g[2].push_back(1);

	g[3].push_back(1);
	//g[3].push_back(4);

	g[4].push_back(1);
	//g[4].push_back(3);


	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	dfs(0);
}
