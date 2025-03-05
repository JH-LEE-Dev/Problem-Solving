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
#define MAX 501

int N, M;
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<vector<bool>> visited(MAX, vector<bool>(MAX, false));

vector<int> dir_row{ 0,0,-1,1 };
vector<int> dir_col{ 1,-1,0,0 };

int result{ 0 };

void input()
{
	cin >> N >> M;

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

void dfs(int r, int c, int total, int cnt)
{
	if (cnt == 4)
	{
		result = max(result, total);
	}
	else
	{
		for (int i{ 0 }; i < 4; ++i)
		{
			int nR{ r + dir_row[i] };
			int nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false || visited[nR][nC] == true)
				continue;

			visited[nR][nC] = true;
			dfs(nR, nC, total + table[nR][nC], cnt + 1);
			visited[nR][nC] = false;
		}
	}
}

int halfcross(int r, int c, int total)
{
	int nR{ r };
	int nC{ c };
	int cnt{ 0 };
	int minVal{ INF };

	if (isValid(nR + 1, nC))
	{
		minVal = min(minVal, table[nR + 1][nC]);
		total += table[nR + 1][nC];
		++cnt;
	}

	if (isValid(nR, nC + 1))
	{
		minVal = min(minVal, table[nR][nC + 1]);
		total += table[nR][nC + 1];
		++cnt;
	}

	if (isValid(nR - 1, nC))
	{
		minVal = min(minVal, table[nR - 1][nC]);
		total += table[nR - 1][nC];
		++cnt;
	}

	if (isValid(nR, nC - 1))
	{
		minVal = min(minVal, table[nR][nC - 1]);
		total += table[nR][nC - 1];
		++cnt;
	}

	if (cnt == 4)
	{
		return total -= minVal;
	}
	else if (cnt == 3)
	{
		return total;
	}
	else
	{
		return 0;
	}
}

void solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			visited[i][j] = true;
			dfs(i, j, table[i][j], 1);
			int temp = halfcross(i, j, table[i][j]);
			result = max(temp, result);
			visited[i][j] = false;
		}
	}

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