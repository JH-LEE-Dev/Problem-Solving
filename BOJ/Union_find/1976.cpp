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
*	���� �м�
*	1. �� ������ ���� ������ �־�����, ���� ��ȹ�� �������� Ȯ���ؾ� �Ѵ�.
	�� ���� ��ȹ ���õ��� ���� ����� �� �ִ��� Ȯ���Ѵ�.

	���� �ذ� ���� (union find)
	1. ���� ����� �������� ���� �������� merge�Ѵ�.
	2. ���� ��ȹ���� ��� ���� �θ� ������ �ִٸ�, ������ ��ȹ�̴�.
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