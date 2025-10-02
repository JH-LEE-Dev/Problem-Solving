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
#define MAX 101

int N, M, Q;
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));
vector<int> Heights;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0)
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
		}
	}

	cin >> Q;

	for (int i{ 0 }; i < Q; ++i)
	{
		int H;
		cin >> H;

		Heights.push_back(H);
	}
}

void Bfs(pair<int, int> Start, vector<vector<bool>>& Visited)
{
	if (Table[Start.first][Start.second] == '.')
		return;

	Visited[Start.first][Start.second] = true;
	queue<pair<int, int>> Q;
	Q.push(Start);
	bool bValid{ true };
	set<pair<int, int>> ClusterQuery;
	vector<pair<int, int>> ClusterVector;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [R, C] {Cur};
		if (R == N - 1)
		{
			bValid = false;
		}

		ClusterQuery.insert({ R,C });
		ClusterVector.push_back({ R,C });

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false || Table[NewR][NewC] == '.')
				continue;

			if (Visited[NewR][NewC] == false)
			{
				Visited[NewR][NewC] = true;
				Q.push({ NewR,NewC });
			}
		}
	}

	if (bValid == false)
		return;

	int MinDelta{ INF };

	sort(ClusterVector.begin(), ClusterVector.end(), greater<pair<int, int>>());

	for (const auto& P : ClusterVector)
	{
		auto [R, C] {P};

		auto NewR{ R };

		while (true)
		{
			NewR += 1;

			if (ClusterQuery.find({ NewR,C }) != ClusterQuery.end())
				break;

			if (IsValid(NewR, C) == false || Table[NewR][C] == 'x')
			{
				MinDelta = min(MinDelta, NewR - R - 1);
				break;
			}
		}
	}

	for (const auto& P : ClusterVector)
	{
		auto [R, C] {P};

		auto NewR{ R };

		for (int i{ 0 }; i < MinDelta; ++i)
		{
			int PrevR{ NewR };
			NewR += 1;

			Table[PrevR][C] = '.';
			Table[NewR][C] = 'x';
		}
	}
}

void Throw(int H, int Type)
{
	int Dir{ 1 };
	int C{ -1 };

	if (Type == 1)
	{
		Dir = -1;
		C = M;
	}

	int R{ N - H };

	int NewC{ C };

	while (true)
	{
		NewC += Dir;

		if (IsValid(R, NewC) == false)
			break;

		if (Table[R][NewC] == 'x')
		{
			Table[R][NewC] = '.';

			vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));

			if (IsValid(R - 1, NewC) == true)
				Bfs({ R - 1,NewC }, Visited);

			if (IsValid(R + 1, NewC) == true && Visited[R + 1][NewC] == false)
				Bfs({ R + 1,NewC }, Visited);

			if (Dir == -1)
			{
				if (IsValid(R, NewC - 1) == true)
				{
					if (Visited[R][NewC - 1] == false)
						Bfs({ R,NewC - 1 }, Visited);
				}
			}
			else
			{
				if (IsValid(R, NewC + 1) == true)
				{
					if (Visited[R][NewC + 1] == false)
						Bfs({ R,NewC + 1 }, Visited);
				}
			}

			break;
		}
	}
}

void Solve()
{
	int Dir{ 0 };

	for (int i{ 0 }; i < Q; ++i)
	{
		Throw(Heights[i], Dir);
		Dir = 1 - Dir;
	}

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cout << Table[i][j];
		}

		cout << endl;
	}
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