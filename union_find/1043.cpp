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
*	문제 해결 전략
*	1. 파티를 하나의 집합으로 보고, 진실을 아는 사람이 속해 있는 지를 유니온 파인드로 체크.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 51

int N, M;
vector<int> parent(MAX, 0);
vector<int> ran(MAX, 1);
vector<int> theyKnows;
vector<vector<int>> party(MAX, vector<int>());

int find(int v)
{
	if (parent[v] == v)
		return v;

	return parent[v] = find(parent[v]);
}

void merge(int u, int v)
{
	int p_u{ find(u) };
	int p_v{ find(v) };

	if (p_u == p_v)
		return;

	if (ran[p_u] > ran[p_v])
		swap(p_u, p_v);

	parent[p_u] = p_v;

	if (ran[p_u] == ran[p_v])
		++ran[p_v];
}

void input()
{
	for (int i{ 0 }; i < MAX; ++i)
	{
		parent[i] = i;
	}

	cin >> N >> M;

	int cnt;

	cin >> cnt;

	for (int i{ 0 }; i < cnt; ++i)
	{
		int num;
		cin >> num;

		theyKnows.push_back(num);
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int cnt;

		cin >> cnt;

		for (int j{ 0 }; j < cnt; ++j)
		{
			int num;
			cin >> num;

			if (party[i].size() == 0)
				party[i].push_back(num);
			else
				merge(party[i][0], num);
		}
	}
}

void solve()
{
	int result{ M };

	for (int i{ 0 }; i < M; ++i)
	{
		if (party[i].size() == 0)
			continue;

		int p_u{ find(party[i][0]) };

		for (int j{ 0 }; j < theyKnows.size(); ++j)
		{
			int p_v{ find(theyKnows[j]) };

			if (p_u == p_v)
			{
				--result;
				break;
			}
		}
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