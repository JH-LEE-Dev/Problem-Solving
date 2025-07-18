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
using Vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N, M;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<tuple<int, int, int>> InTable;
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

int Result{ 0 };

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];

			if (i > 0 && i < N - 1 && j > 0 && j < M - 1)
				InTable.push_back({ Table[i][j],i,j });
		}
	}
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0)
		return false;
	else
		return true;
}

bool Bfs(pair<int, int> Start)
{
	queue<Vertex> Q;
	Q.push({ Table[Start.first][Start.second], Start.first,Start.second });

	vector<vector<bool>> TempVisited;
	TempVisited = Visited;
	TempVisited[Start.first][Start.second] = true;

	bool bValid{ true };

	int MaxHeight{ Table[Start.first][Start.second] };
	int OutlineMinHeight{ INF };

	vector<int> Heights;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<1>(Cur) };
		auto C{ get<2>(Cur) };

		Heights.push_back(Table[R][C]);

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Table[NewR][NewC] > MaxHeight)
			{
				OutlineMinHeight = min(Table[NewR][NewC], OutlineMinHeight);
				continue;
			}

			if (NewR == N - 1 || NewC == M - 1 || NewR == 0 || NewC == 0)
			{
				bValid = false;
				break;
			}

			if (TempVisited[NewR][NewC] == false)
			{
				TempVisited[NewR][NewC] = true;
				Q.push({ Table[NewR][NewC],NewR,NewC });
			}

			if (bValid == false)
				break;
		}
	}

	if (bValid)
	{
		Visited = TempVisited;

		for (auto& H : Heights)
		{
			Result += (OutlineMinHeight - H);
		}
	}

	return bValid;
}

void Solve()
{
	sort(InTable.begin(), InTable.end(), greater<tuple<int, int, int>>());

	for (int i{ 0 }; i < InTable.size(); ++i)
	{
		int R{ get<1>(InTable[i]) };
		int C{ get<2>(InTable[i]) };

		if (Visited[R][C] == false)
		{
			Bfs({ R,C });
		}
	}

	cout << Result;
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