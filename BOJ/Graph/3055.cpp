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

int N, M;
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));
vector<pair<int, int>> Waters;
pair<int, int> Start;
pair<int, int> End;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0 || Table[R][C] == 'X')
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

			if (Table[i][j] == 'S')
			{
				Start.first = i;
				Start.second = j;
			}

			if (Table[i][j] == 'D')
			{
				End.first = i;
				End.second = j;
			}

			if (Table[i][j] == '*')
				Waters.push_back({ i,j });
		}
	}
}

void Bfs()
{
	queue<tuple<int, int, int, int>> Q;
	vector<vector<bool>> Visited_Water(MAX, vector<bool>(MAX, false));
	vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));

	Dist[Start.first][Start.second] = 0;
	Q.push({ 0,0,Start.first,Start.second });

	for (int i{ 0 }; i < Waters.size(); ++i)
	{
		auto [R, C] {Waters[i]};

		Visited_Water[R][C] = true;
		Q.push({ 0,1,R,C });
	}

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto [CurDist, CurType, R, C] {Cur};

		if (R == End.first && C == End.second)
		{
			cout << CurDist;
			return;
		}

		if (CurType == 0)
		{
			for (int i{ 0 }; i < 4; ++i)
			{
				auto NewR{ R + Dir_Row[i] };
				auto NewC{ C + Dir_Col[i] };
				auto NewDist{ CurDist + 1 };

				if (IsValid(NewR, NewC) == false || Visited_Water[NewR][NewC] == true)
					continue;

				if (Dist[NewR][NewC] > NewDist)
				{
					bool bWaterValid{ true };

					if (NewR != End.first || NewC != End.second)
					{
						for (int i{ 0 }; i < 4; ++i)
						{
							auto CheckR{ NewR + Dir_Row[i] };
							auto CheckC{ NewC + Dir_Col[i] };

							if (IsValid(CheckR, CheckC) == false)
								continue;

							if (Visited_Water[CheckR][CheckC] == true)
							{
								bWaterValid = false;
								break;
							}
						}
					}

					if (bWaterValid)
					{
						Dist[NewR][NewC] = NewDist;
						Q.push({ NewDist,CurType,NewR,NewC });
					}
				}
			}
		}
		else
		{
			for (int i{ 0 }; i < 4; ++i)
			{
				auto NewR{ R + Dir_Row[i] };
				auto NewC{ C + Dir_Col[i] };

				if (IsValid(NewR, NewC) == false)
					continue;

				if (NewR == End.first && NewC == End.second)
					continue;

				if (Visited_Water[NewR][NewC] == false)
				{
					Visited_Water[NewR][NewC] = true;
					Q.push({ 0,CurType,NewR,NewC });
				}
			}
		}
	}

	cout << "KAKTUS";
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