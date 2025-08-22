#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

#define endl '\n'
using namespace std;

int N{ 0 };
vector<char> color(100'005, 0);
vector<int> black;
vector<vector<int>> edge(100'005, vector<int>());

vector<int> parent(100'005, 0);
vector<int> ran(100'005, 0);
vector<int> counting(100'005, 1);
vector<bool> visited(100'005, false);


int find(int u)
{
	if (u == parent[u])
		return u;

	return parent[u] = find(parent[u]);
}

void union_set(int u, int v)
{
	u = find(u);
	v = find(v);

	if (u == v)
		return;

	if (ran[u] > ran[v])
		swap(u, v);

	parent[u] = v;
	counting[v] += counting[u];

	if (ran[u] == ran[v])
		ran[v]++;
}

void bfs(int idx)
{
	queue<int> q;

	q.push(idx);

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (auto& it : edge[cur])
		{
			if (color[it] == 'B' || visited[it] == true)
				continue;

			visited[it] = true;

			q.push(it);

			if (color[it] == 'R')
				union_set(cur, it);
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	string input;
	cin >> N;

	for (int i{ 0 }; i < N - 1; ++i)
	{
		int src{ 0 }, dst{ 0 };
		cin >> src >> dst;

		edge[src].push_back(dst);
		edge[dst].push_back(src);
	}

	cin >> input;

	for (int i{ 1 }; i <= input.length(); ++i)
	{
		color[i] = input[i - 1];

		if (color[i] == 'B')
		{
			black.push_back(i);
		}
		else
		{
			parent[i] = i;
			ran[i] = 1;
		}
	}

	long long result{ 0 };

	for (int i{ 1 }; i <= input.length(); ++i)
	{
		if (color[i] == 'R')
		{
			bfs(i);
		}
	}

	for (int i{ 0 }; i < black.size(); ++i)
	{
		for (auto& it : edge[black[i]])
		{
			if (color[it] == 'R')
				result += counting[find(it)];
		}
	}

	cout << result;

	return 0;
}
