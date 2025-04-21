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
*	1.���ͽ�Ʈ�� �˰����� Ȱ���Ѵ�.
*	2.4���⿡ ���� ������ �����ϴ��� Ȯ���ϱ� ���ؼ�, ������ ��,�� �ε����� �����ϴ� �迭�� �����Ͽ�,
*	  4�������� ���� ��ȸ���� �ʰ� ������ �����ϴ��� ������ O(1)�� Ȯ���Ѵ�.
*	3.�̺� Ž������ ���� ����� ���� ������ �˾Ƴ��� ���ؼ�, ������ ��,���� �����ϴ� �迭�� ����Ѵ�.
*/

using namespace std;
using vertex = tuple<int, int, int, bool>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 501

vector<vector<char>> table(MAX, vector<char>(MAX));
int N, t;
pair<int, int> goal;
vector<vector<int>> row(MAX, vector<int>());
vector<vector<int>> col(MAX, vector<int>());

vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(2, INF)));

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	cin >> N >> t >> goal.first >> goal.second;

	for (int i{ 0 }; i < N; ++i)
	{
		string str;
		cin >> str;

		for (int j{ 0 }; j < N; ++j)
		{
			table[i][j] = str[j];

			if (table[i][j] == '#')
			{
				row[i].push_back(j);
				col[j].push_back(i);
			}
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

int bSearch_row(int r, int target)
{
	int left{ 0 };
	int right{ (int)row[r].size() - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ row[r][middle] };

		if (middleNum < target)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return left;
}

int bSearch_col(int c, int target)
{
	int left{ 0 };
	int right{ (int)col[c].size() - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ col[c][middle] };

		if (middleNum < target)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return left;
}

bool areThereAnyWarp_row(int r, int c, int dir, pair<int, int>& _warp)
{
	if (row[r].size() == 0)
		return false;

	//���� ������ �� ū ���� ������ �ִ���,
	if (dir == 1)
	{
		int idx{ bSearch_row(r, c) };

		if (idx >= row[r].size())
			return false;

		//���� ���� ��ǥ���, �̺� Ž���� ����� ���� ��ǥ�� ���� ���̴�.
		//���� ���� ��ĭ �о��ش�.
		if (row[r][idx] == c)
		{
			if (idx == row[r].size() - 1)
				return false;
			else
				idx += 1;
		}

		_warp.first = r;
		_warp.second = row[r][idx];
	}
	else
	{
		int idx{ bSearch_row(r, c) };

		if (idx == 0 && row[r][0] >= c)
			return false;

		idx -= 1;

		_warp.first = r;
		_warp.second = row[r][idx];
	}

	return true;
}

bool areThereAnyWarp_col(int r, int c, int dir, pair<int, int>& _warp)
{
	if (col[c].size() == 0)
		return false;

	//���� �ຸ�� �� ū �࿡ ������ �ִ���,
	if (dir == 1)
	{
		int idx{ bSearch_col(c, r) };

		if (idx >= col[c].size())
			return false;

		//���� ���� ��ǥ���, �̺� Ž���� ����� ���� ��ǥ�� ���� ���̴�.
		//���� ���� ��ĭ �о��ش�.
		if (col[c][idx] == r)
		{
			if (idx == col[c].size() - 1)
				return false;
			else
				idx += 1;
		}

		_warp.first = col[c][idx];
		_warp.second = c;
	}
	else
	{
		int idx{ bSearch_col(c, r) };

		if (idx == 0 && col[c][0] >= r)
			return false;

		idx -= 1;

		_warp.first = col[c][idx];
		_warp.second = c;
	}

	return true;
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,0,0,false });
	dist[0][0][false] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto curMode{ get<3>(cur) };

		if (dist[r][c][curMode] < curDist)
			continue;

		if (r == goal.first - 1 && c == goal.second - 1)
		{
			cout << curDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };
			auto newDist{ curDist + 1 };
			auto newMode{ false };

			if (isValid(nR, nC) == false)
				continue;

			if (dist[nR][nC][newMode] > newDist)
			{
				dist[nR][nC][newMode] = newDist;
				pq.push({ newDist,nR,nC,newMode });
			}
		}

		auto newWarpDist{ curDist + 1 };

		if (curMode == false)
		{
			newWarpDist += t;
			curMode = true;
		}

		pair<int, int> nxtWarp;

		if (areThereAnyWarp_row(r, c, 0, nxtWarp))
		{
			if (dist[nxtWarp.first][nxtWarp.second][curMode] > newWarpDist)
			{
				dist[nxtWarp.first][nxtWarp.second][curMode] = newWarpDist;
				pq.push({ newWarpDist,nxtWarp.first,nxtWarp.second,curMode });
			}
		}

		if (areThereAnyWarp_row(r, c, 1, nxtWarp))
		{
			if (dist[nxtWarp.first][nxtWarp.second][curMode] > newWarpDist)
			{
				dist[nxtWarp.first][nxtWarp.second][curMode] = newWarpDist;
				pq.push({ newWarpDist,nxtWarp.first,nxtWarp.second,curMode });
			}
		}

		if (areThereAnyWarp_col(r, c, 0, nxtWarp))
		{
			if (dist[nxtWarp.first][nxtWarp.second][curMode] > newWarpDist)
			{
				dist[nxtWarp.first][nxtWarp.second][curMode] = newWarpDist;
				pq.push({ newWarpDist,nxtWarp.first,nxtWarp.second,curMode });
			}
		}

		if (areThereAnyWarp_col(r, c, 1, nxtWarp))
		{
			if (dist[nxtWarp.first][nxtWarp.second][curMode] > newWarpDist)
			{
				dist[nxtWarp.first][nxtWarp.second][curMode] = newWarpDist;
				pq.push({ newWarpDist,nxtWarp.first,nxtWarp.second,curMode });
			}
		}
	}
}

void solve()
{
	dijkstra();
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