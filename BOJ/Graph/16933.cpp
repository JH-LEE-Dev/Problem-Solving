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
#define MAX 1'001

int N, M, K;
int result{ INF };
vector<vector<int>> table(MAX, vector<int>(MAX, INF));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(11, INF)));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> N >> M >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		string str;
		cin >> str;

		for (int j{ 0 }; j < M; ++j)
		{
			table[i][j] = str[j] - '0';
		}
	}
}

void bfs()
{
	queue<tuple<int, int, int, int>> q;
	q.push({ 1,0,0,0 });
	dist[0][0][0] = 1;

	while (q.empty() == false)
	{
		auto cur{ q.front() };
		q.pop();

		auto r{ get<2>(cur) };
		auto c{ get<3>(cur) };
		auto curDist{ get<0>(cur) };
		auto curBreak{ get<1>(cur) };
		auto curDay{ curDist % 2 };

		if (r == N - 1 && c == M - 1)
		{
			result = min(result, curDist);
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };
			auto newDist{ curDist + 1 };
			auto newBreak{ curBreak };

			if (isValid(nR, nC) == false)
				continue;

			if (table[nR][nC] == 1)
			{
				if (newBreak + 1 > K)
					continue;

				if (curDay == 1)
				{
					newBreak += 1;

					if (dist[nR][nC][newBreak] > newDist)
					{
						dist[nR][nC][newBreak] = newDist;
						q.push({ newDist,newBreak,nR,nC });
					}
				}
				else
				{
					q.push({ newDist,newBreak,r,c });
				}
			}
			else
			{
				if (dist[nR][nC][newBreak] > newDist)
				{
					dist[nR][nC][newBreak] = newDist;
					q.push({ newDist,newBreak,nR,nC });
				}
			}
		}
	}
}

void solve()
{
	bfs();

	if (result == INF)
		cout << -1;
	else
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