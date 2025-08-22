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
*	���� �ذ� ����
*	1. dfs�� �־��� ���ڿ��� ���� �ε����� ���ڸ� �湮�Ѵ�.
*	2. ���� �湮�� ���ڰ� ���ڿ��� ������ ���ڶ��, ��������� dfs �Ÿ��� ���ڿ��� ���̷� ���� ���� result�� ���Ͽ�
*		�� ū ���� �����ϰ�, ��ǥ�� �����Ѵ�.
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