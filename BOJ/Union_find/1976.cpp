#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>
#include <limits>
#include <tuple>
#include <string>
#include <cmath>
#include <bitset>
#include <iomanip>

/*
*	문제 분석
*	1. 각 도시의 연결 정보가 주어지고, 여행 계획이 가능한지 확인해야 한다.
	즉 여행 계획 도시들이 서로 연결될 수 있는지 확인한다.

	문제 해결 전략 (union find)
	1. 서로 연결된 정점들을 같은 집합으로 merge한다.
	2. 여행 계획들이 모두 같은 부모를 가지고 있다면, 가능한 계획이다.
*
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 201

int N, M;
vector<int> parent(MAX, 0);
vector<int> ran(MAX, 0);
vector<int> stopBy;

int find(int u)
{
	if (parent[u] == u)
		return u;

	return parent[u] = find(parent[u]);
}

void merge(int u, int v)
{
	int par_u{ find(u) };
	int par_v{ find(v) };

	if (par_u == par_v)
		return;

	if (ran[par_u] > ran[par_v])
		swap(par_u, par_v);

	parent[par_u] = par_v;

	if (ran[par_u] == ran[par_v])
		++ran[par_u];
}

void input()
{
	cin >> N >> M;

	for (int i{ 1 }; i <= N; ++i)
	{
		parent[i] = i;
		ran[i] = 1;
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			int edge;
			cin >> edge;

			if (edge == 1)
			{
				merge(i, j);
			}
		}
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int vertex;
		cin >> vertex;

		stopBy.push_back(vertex);
	}
}

void solve()
{
	int resultParent{ -1 };

	resultParent = find(stopBy[0]);

	for (int i{ 1 }; i < M; ++i)
	{
		auto curParent{ find(stopBy[i]) };

		if (curParent != resultParent)
		{
			cout << "NO";
			return;
		}
	}

	cout << "YES";
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}