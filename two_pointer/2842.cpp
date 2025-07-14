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
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));
vector<vector<int>> Weight(MAX, vector<int>(MAX, 0));

pair<int, int> Start;

vector<int> Dir_Row{ 0,0,1,-1,1,-1,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0,1,-1,-1,1 };
int TotalCnt{ 0 };
int Result{ INF };
vector<int> Weights;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> Table[i][j];

			if (Table[i][j] == 'P')
			{
				Start.first = i;
				Start.second = j;
			}

			if (Table[i][j] == 'K')
			{
				++TotalCnt;
			}
		}
	}

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> Weight[i][j];

			Weights.push_back(Weight[i][j]);
		}
	}
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= N || C < 0)
		return false;
	else
		return true;
}

bool Bfs(int Min, int Max)
{
	if (Weight[Start.first][Start.second] < Min || Weight[Start.first][Start.second]> Max)
		return false;

	int Cnt{ 0 };

	vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));
	queue<tuple< int, int>> Q;
	Q.push({ Start.first,Start.second });
	Visited[Start.first][Start.second] = true;

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<0>(Cur) };
		auto C{ get<1>(Cur) };

		if (Table[R][C] == 'K')
			++Cnt;

		if (Cnt == TotalCnt)
			return true;

		for (int i{ 0 }; i < 8; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if (Weight[NewR][NewC] < Min || Weight[NewR][NewC] > Max)
				continue;

			if (Visited[NewR][NewC] == false)
			{
				Visited[NewR][NewC] = true;
				Q.push({ NewR,NewC });
			}
		}
	}

	return false;
}

void TwoPointer()
{
	int Left{ 0 };
	int Right{ 0 };

	while (true)
	{
		Right = Left;

		if (Left >= Weights.size())
			break;

		while (Left <= Right)
		{
			if (Bfs(Weights[Left], Weights[Right]) == true)
			{
				Result = min(Result, Weights[Right] - Weights[Left]);
				++Left;
				break;
			}
			else
			{
				++Right;

				if (Right >= Weights.size())
				{
					++Left;
					break;
				}
			}
		}
	}
}

void Solve()
{
	sort(Weights.begin(), Weights.end());
	Weights.erase(unique(Weights.begin(), Weights.end()), Weights.end());

	TwoPointer();

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