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

int N, R, L;
int maxTime{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	cin >> N >> L >> R;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> table[i][j];
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= N || c < 0)
		return false;
	else
		return true;
}

void dfs(vector<vector<int>>& _visited, pair<int, int> s, int& cnt, int& total, int& idx)
{
	stack<pair<int, int>> st;
	_visited[s.first][s.second] = idx;
	cnt = 1;
	total += table[s.first][s.second];

	st.push(s);

	while (st.empty() == false)
	{
		auto cur{ st.top() };
		st.pop();

		auto r{ cur.first };
		auto c{ cur.second };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == true && _visited[nR][nC] == -1 && _visited[nR][nC] != -2)
			{
				int delta{ abs(table[r][c] - table[nR][nC]) };

				if (delta >= L && delta <= R)
				{
					st.push({ nR,nC });
					_visited[nR][nC] = idx;

					++cnt;
					total += table[nR][nC];
				}
			}
		}
	}
}

void solve()
{
	while (true)
	{
		vector<vector<int>> visited(MAX, vector<int>(MAX, -1));

		int idx{ 0 };
		++maxTime;

		for (int i{ 0 }; i < N; ++i)
		{
			for (int j{ 0 }; j < N; ++j)
			{

			}
		}

		for (int i{ 0 }; i < v.size(); ++i)
		{
			auto cur{ v[i] };

			int tempCnt{ 0 };
			int tempTotal{ 0 };

			if (visited[cur.first][cur.second] != -1)
				continue;

			dfs(visited, cur, tempCnt, tempTotal, idx);

			for (int i{ 0 }; i < N; ++i)
			{
				for (int j{ 0 }; j < N; ++j)
				{
					if (visited[i][j] == idx)
					{
						table[i][j] = tempTotal / tempCnt;
					}
				}
			}

			++idx;
		}
	}
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