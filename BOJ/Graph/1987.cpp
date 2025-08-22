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
*	문제 분석
*	1. 좌측 상단 칸에서 움직이기 시작하여, 지금까지 밟지 않았던 알파벳만을 밟고 이동.
*
*	문제 해결 전략
*	1. 좌측 상단에서 시작하여, visited 배열을 구성하고 dfs 과정에서 방문하지 않은 알파벳일 때만 이동.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 21

int R, C;
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<bool> visited_Alphabet(27, false);
vector<vector<bool>> visited(MAX, vector<bool>(MAX, false));

int result{ 1 };

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	cin >> R >> C;

	for (int i{ 0 }; i < R; ++i)
	{
		for (int j{ 0 }; j < C; ++j)
		{
			cin >> table[i][j];
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= R || r < 0 || c >= C || c < 0)
		return false;
	else
		return true;
}

void dfs(int r, int c, int dist)
{
	if (visited_Alphabet[table[r][c] - 'A'] == true)
	{
		result = max(result, dist - 1);
		return;
	}

	visited_Alphabet[table[r][c] - 'A'] = true;
	visited[r][c] = true;

	for (int i{ 0 }; i < 4; ++i)
	{
		auto nR{ r + dir_row[i] };
		auto nC{ c + dir_col[i] };

		if (isValid(nR, nC) == false)
			continue;

		dfs(nR, nC, dist + 1);
	}

	visited_Alphabet[table[r][c] - 'A'] = false;
	visited[r][c] = false;
}

void solve()
{
	dfs(0, 0, 1);

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