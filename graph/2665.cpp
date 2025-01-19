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
using vertex = tuple<int, int, int>;

#define MAX 51
#define endl '\n'
#define INF numeric_limits<int>::max()

enum COLOR { BLACK, WHITE };
int N{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, WHITE));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		string str;
		cin >> str;

		for (int j{ 0 }; j < str.length(); ++j)
		{
			if (str[j] == '0')
				table[i][j] = BLACK;
			else
				table[i][j] = WHITE;
		}
	}
}

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= N || col < 0)
		return false;
	else
		return true;
}

void bfs()
{
	vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

	deque<vertex> q;
	q.push_front({ 0,0,0 });

	while (q.empty() == false)
	{
		auto cur{ q.front() };
		q.pop_front();

		auto row{ get<0>(cur) };
		auto col{ get<1>(cur) };
		auto curCount{ get<2>(cur) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nRow{ row + dir_row[i] };
			auto nCol{ col + dir_col[i] };

			if (isValid(nRow, nCol) == false)
				continue;

			if (table[nRow][nCol] == WHITE)
			{
				if (dist[nRow][nCol] > curCount)
				{
					dist[nRow][nCol] = curCount;
					q.push_front({ nRow,nCol,curCount });
				}
			}
			else
			{
				if (dist[nRow][nCol] > curCount + 1)
				{
					dist[nRow][nCol] = curCount + 1;
					q.push_back({ nRow,nCol,curCount + 1 });
				}
			}
		}
	}

	cout << dist[N - 1][N - 1];
}

void solve()
{
	bfs();
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}
}