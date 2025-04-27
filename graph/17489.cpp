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
*	1. dfs로 주어진 문자열의 다음 인덱스의 문자를 방문한다.
*	2. 현재 방문한 문자가 문자열의 마지막 문자라면, 현재까지의 dfs 거리를 문자열의 길이로 나눈 값을 result와 비교하여
*		더 큰 값을 저장하고, 좌표도 저장한다.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 101

int N, M, S;
string str;
vector<vector<char>> table(MAX, vector<char>(MAX));

vector<vector<bool>> visited(MAX, vector<bool>(MAX, false));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

bool bCycle{ false };

int result{ 0 };
pair<int, int> resultCoord;

void input()
{
	cin >> N >> M >> S;

	cin >> str;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0)
		return false;
	else
		return true;
}

void dfs(pair<int, int> coord, int idx, int cnt)
{
	if (bCycle)
		return;

	visited[coord.first][coord.second] = true;

	if (idx == S - 1)
		idx = -1;

	if (idx == -1)
	{
		if (result < cnt)
		{
			result = cnt;
			resultCoord.first = coord.first;
			resultCoord.second = coord.second;
		}
	}

	for (int i{ 0 }; i < 4; ++i)
	{
		auto nR{ coord.first + dir_row[i] };
		auto nC{ coord.second + dir_col[i] };

		if (isValid(nR, nC) == false)
			continue;

		if (table[nR][nC] == str[idx + 1])
		{
			if (visited[nR][nC] == true)
			{
				if (idx == -1)
				{
					bCycle = true;
					return;
				}
			}
			else
			{
				dfs({ nR,nC }, idx + 1, cnt + 1);
			}
		}
	}

	visited[coord.first][coord.second] = false;
}

void solve()
{
	dfs({ 0,0 }, 0, 1);

	if (result == 0 || bCycle)
		cout << -1;
	else
		cout << result / S << endl << resultCoord.first + 1 << ' ' << resultCoord.second + 1;
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