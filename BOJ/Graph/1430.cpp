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
#define MAX 51

int N, R, D;
pair<int, int> enemy;
vector<vector<int>> edges(MAX, vector<int>());
vector<pair<int, int>> tower;
vector<int> dist(MAX, INF);

float result{ 0 };

void input()
{
	cin >> N >> R >> D >> enemy.first >> enemy.second;

	for (int i{ 0 }; i < N; ++i)
	{
		pair<int, int> temp;
		cin >> temp.first >> temp.second;

		tower.push_back(temp);
	}
}

void generateGraph()
{
	for (int i{ 0 }; i < N; ++i)
	{
		auto src{ tower[i] };

		for (int j{ i }; j < N; ++j)
		{
			if (i == j)
				continue;

			auto dst{ tower[j] };

			float deltaX{ (float)abs(src.first - dst.first) };
			float deltaY{ (float)abs(src.second - dst.second) };

			float distance{ hypot(deltaX,deltaY) };

			if (distance <= (float)R)
			{
				edges[i].push_back(j);
				edges[j].push_back(i);
			}
		}
	}
}

void bfs()
{
	queue<int> q;

	for (int i{ 0 }; i < N; ++i)
	{
		float deltaX{ (float)abs(enemy.first - tower[i].first) };
		float deltaY{ (float)abs(enemy.second - tower[i].second) };

		float distance{ hypot(deltaX,deltaY) };

		if (distance <= (float)R)
		{
			q.push(i);
			dist[i] = 0;
			result += D;
		}
	}

	while (q.empty() == false)
	{
		auto src{ q.front() };
		q.pop();

		for (auto& dst : edges[src])
		{
			if (dist[dst] == INF)
			{
				dist[dst] = dist[src] + 1;
				q.push(dst);
			}
		}
	}
}

void solve()
{
	generateGraph();

	bfs();

	for (int i{ 0 }; i < N; ++i)
	{
		if (dist[i] == 0)
			continue;

		result += ((float)D / pow(2, dist[i]));
	}

	cout << result;
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