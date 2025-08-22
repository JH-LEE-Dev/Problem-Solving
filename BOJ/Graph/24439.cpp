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
using State = tuple<int, int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

int N, M;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<vector<int>>> Dist(MAX, vector<vector<int>>(MAX, vector<int>(4, INF)));

//©Л,аб,го,╩С
vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		string Str;
		cin >> Str;

		for (int j{ 0 }; j < M; ++j)
		{
			Table[i][j] = Str[j] - '0';
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

void Bfs()
{
	deque<State> DQ;
	DQ.push_front({ 0,0,0,0 });
	Dist[0][0][0] = 0;

	while (DQ.empty() == false)
	{
		auto Cur{ DQ.front() };
		DQ.pop_front();

		auto R{ get<1>(Cur) };
		auto C{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurType{ get<3>(Cur) };

		if (CurType == 0)
		{
			if (Dist[R][C][1] > CurDist)
			{
				Dist[R][C][1] = CurDist;
				DQ.push_front({ CurDist,R,C,1 });
			}

			if (Dist[R][C][2] > CurDist)
			{
				Dist[R][C][2] = CurDist;
				DQ.push_front({ CurDist,R,C,2 });
			}
		}

		if (CurType > 0 && CurType < 3)
		{
			if (Dist[R][C][3] > CurDist)
			{
				Dist[R][C][3] = CurDist;
				DQ.push_front({ CurDist,R,C,3 });
			}
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (CurType == 0 || CurType == 3)
			{
				if (Table[NewR][NewC] == 1)
					continue;

				auto NewDist{ CurDist + 1 };

				if (Dist[NewR][NewC][CurType] > NewDist)
				{
					Dist[NewR][NewC][CurType] = NewDist;
					DQ.push_back({ NewDist,NewR,NewC,CurType });
				}
			}

			if (CurType == 1)
			{
				if (i < 2)
				{
					auto NewDist{ CurDist + 1 };

					if (Dist[NewR][NewC][CurType] > NewDist)
					{
						Dist[NewR][NewC][CurType] = NewDist;
						DQ.push_back({ NewDist,NewR,NewC,CurType });
					}
				}
			}

			if (CurType == 2)
			{
				if (i >= 2)
				{
					auto NewDist{ CurDist + 1 };

					if (Dist[NewR][NewC][CurType] > NewDist)
					{
						Dist[NewR][NewC][CurType] = NewDist;
						DQ.push_back({ NewDist,NewR,NewC,CurType });
					}
				}
			}
		}
	}
}

void Solve()
{
	Bfs();

	int Result{ INF };

	for (int i{ 0 }; i < 4; ++i)
	{
		Result = min(Result, Dist[N - 1][M - 1][i]);
	}

	if (Result == INF)
		cout << -1;
	else
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