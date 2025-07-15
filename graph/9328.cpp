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

int T, N, M;
vector<vector<char>> Table;
vector<vector<bool>> Visited_KeyOrMoney;
vector<int> Key;

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };
int Result;
int Cnt{ 0 };

bool IsValid(int R, int C)
{
	if (R >= N + 2 || R < 0 || C >= M + 2 || C < 0 || Table[R][C] == '*')
		return false;
	else
		return true;
}

void Input()
{
	Table = vector<vector<char>>(MAX, vector<char>(MAX, '.'));
	Visited_KeyOrMoney = vector<vector<bool>>(MAX, vector<bool>(MAX, false));
	Key = vector<int>(27, 0);
	Result = 0;

	cin >> N >> M;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= M; ++j)
		{
			cin >> Table[i][j];
		}
	}

	string Str;
	cin >> Str;

	if (Str[0] == '0')
		return;

	for (int i{ 0 }; i < Str.length(); ++i)
	{
		Key[Str[i] - 'a'] = 1;
	}
}

void Bfs(pair<int, int> Start)
{
	vector<vector<bool>>Visited(MAX, vector<bool>(MAX, false));

	Visited[Start.first][Start.second] = true;
	queue<pair<int, int>> Q;
	Q.push(Start);

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ get<0>(Cur) };
		auto C{ get<1>(Cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto NewR{ R + Dir_Row[i] };
			auto NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false)
				continue;

			if ((int)Table[NewR][NewC] >= (int)'A' && (int)Table[NewR][NewC] <= (int)'Z')
			{
				if (Key[Table[NewR][NewC] - 'A'] == 0)
					continue;
			}

			if ((int)Table[NewR][NewC] >= (int)'a' && (int)Table[NewR][NewC] <= (int)'z')
			{
				if (Visited_KeyOrMoney[NewR][NewC] == false)
				{
					Key[Table[NewR][NewC] - 'a'] = 1;
					++Cnt;
					Visited_KeyOrMoney[NewR][NewC] = true;
				}
			}

			if (Table[NewR][NewC] == '$')
			{
				if (Visited_KeyOrMoney[NewR][NewC] == false)
				{
					Visited_KeyOrMoney[NewR][NewC] = true;
					++Result;
				}
			}

			if (Visited[NewR][NewC] == false)
			{
				Visited[NewR][NewC] = true;
				Q.push({ NewR,NewC });
			}
		}
	}
}

void Solve()
{
	cin >> T;

	for (int i{ 0 }; i < T; ++i)
	{
		Input();

		while (true)
		{
			Cnt = 0;

			Bfs({ 0,0 });

			if (Cnt == 0)
				break;
		}

		cout << Result << endl;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}