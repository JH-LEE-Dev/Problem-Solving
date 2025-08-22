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

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 500'001

int N, M;
vector<int> parent(MAX, -1);
vector<int> ran(MAX, 1);

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

	for (int i{ 0 }; i < N; ++i)
	{
		parent[i] = i;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int src, dst;
		cin >> src >> dst;

		if (find(src) == find(dst))
		{
			cout << i + 1;
			return;
		}

		merge(src, dst);
	}

	cout << 0;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	return 0;
}