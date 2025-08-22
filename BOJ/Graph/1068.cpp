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

int N;
vector<int> Arr(MAX, 0);
int Start, Banned;

vector<vector<int>> Edges(MAX, vector<int>());

void Input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> Arr[i];

		if (Arr[i] == -1)
			Start = i;
		else
			Edges[Arr[i] + 1].push_back(i);
	}

	cin >> Banned;

	Banned += 1;

	Edges[Banned].clear();
}

void Bfs()
{
	vector<int> Visited(MAX, false);

	if (Start == Banned)
	{
		cout << 0;
		return;
	}

	queue<int> Q;
	Q.push(Start);
	Visited[Start] = true;

	int Cnt{ 0 };

	while (Q.empty() == false)
	{
		auto Src{ Q.front() };
		Q.pop();

		bool bHasChild{ false };

		for (auto& Dst : Edges[Src])
		{
			if (Dst == Banned)
				continue;

			if (Visited[Dst] == false)
			{
				bHasChild = true;
				Visited[Dst] = true;
				Q.push(Dst);
			}
		}

		if (bHasChild == false)
			++Cnt;
	}

	cout << Cnt;
}

void Solve()
{
	Bfs();
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}