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
*	1. ���ͽ�Ʈ�� �˰����� Ȱ���Ͽ�, Ž���Ѵ�.
*	2. ���� �¿� ���� Ÿ�Ϸ� �̵��ϴ� �ð��� 1��, ���� ���� Ÿ���� �ǹ��̶��, �����Ǵ� �ð� Tb�� ���ؼ� 1+Tb�� �Ÿ��� �Ѵ�.
*	3. ���ͽ�Ʈ�� �˰��򿡼� dq�� top�� Tg���� ũ�ٸ�, ���İ� ����� ���̹Ƿ� �˰����� �����ϰ� �������� ���� Ÿ�ϵ��� ����Ѵ�.
*	4. �������� ���� Ÿ�ϵ���, �Ÿ��� INF�̰ų� Tg���� ũ��.
*/

using namespace std;
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX	1'001

int N, M, Tg, Tb, X, B;
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

vector<pair<int, int>> virus;
vector<pair<int, int>> buildings;

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

void input()
{
	cin >> N >> M;

	cin >> Tg >> Tb >> X >> B;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == '#')
			{
				buildings.push_back({ i,j });
			}

			if (table[i][j] == '*')
			{
				virus.push_back({ i,j });
			}
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

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	for (int i{ 0 }; i < X; ++i)
	{
		dist[virus[i].first][virus[i].second] = 0;
		pq.push({ 0,virus[i].first,virus[i].second });
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[r][c] < curDist)
			continue;

		if (curDist > Tg)
			return;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };
			auto newDist{ curDist + 1 };

			if (isValid(nR, nC) == false)
				continue;

			if (table[nR][nC] == '#')
			{
				newDist += Tb;

				if (dist[nR][nC] > newDist)
				{
					pq.push({ newDist,nR,nC });
					dist[nR][nC] = newDist;
				}
			}
			else
			{
				if (dist[nR][nC] > newDist)
				{
					pq.push({ newDist,nR,nC });
					dist[nR][nC] = newDist;
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

	vector<pair<int, int>> result;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (dist[i][j] <= Tg)
				continue;

			result.push_back({ i,j });
		}
	}

	for (int i{ 0 }; i < result.size(); ++i)
	{
		cout << result[i].first + 1 << ' ' << result[i].second + 1 << endl;
	}

	if (result.size() == 0)
		cout << -1;
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