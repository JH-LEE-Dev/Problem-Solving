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
#define MAX 102

int N, M;
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
queue<pair<int, int>> Candidates;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

int TotalCnt{ 0 };
int MeltedTotal{ 0 };
int Time{ 1 };

bool IsValid(int R, int C)
{
	if (R >= N + 1 || R < 0 || C >= M + 1 || C < 0 || Table[R][C] == 1)
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> M;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= M; ++j)
		{
			cin >> Table[i][j];

			if (Table[i][j] == 1)
				++TotalCnt;
		}
	}

	Candidates.push({ 0,0 });
}

void Bfs()
{
	queue<pair<int, int>> Q;

	while (Candidates.empty() == false)
	{
		Q.push(Candidates.front());
		auto Cur{ Candidates.front() };

		Table[Cur.first][Cur.second] = 0;
		Visited[Cur.first][Cur.second] = true;
		Candidates.pop();
	}

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ Cur.first };
		auto C{ Cur.second };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Visited[NewR][NewC] == false)
			{
				Visited[NewR][NewC] = true;
				Q.push({ NewR,NewC });
			}
		}
	}
}

void Melting()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= M; ++j)
		{
			if (Table[i][j] == 1)
			{
				int Cnt{ 0 };

				for (int k{ 0 }; k < 4; ++k)
				{
					auto NewR{ i + Dir_Row[k] };
					auto NewC{ j + Dir_Col[k] };

					if (IsValid(NewR, NewC) == true)
					{
						if (Visited[NewR][NewC] == true)
						{
							++Cnt;

							if (Cnt == 2)
							{
								Candidates.push({ i,j });
								break;
							}
						}
					}
				}
			}
		}
	}
}

void Solve()
{
	while (true)
	{
		Bfs();
		Melting();

		MeltedTotal += Candidates.size();

		if (TotalCnt == MeltedTotal)
		{
			cout << Time;
			return;
		}

		++Time;
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