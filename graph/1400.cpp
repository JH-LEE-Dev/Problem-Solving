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
using crossRoad = tuple<char, int, int>;
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 21

int N, M;
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<pair<int, int>> crossCoord(MAX);
map<pair<int, int>, tuple<bool, int, int>> crossRoads;
pair<int, int> s;
pair<int, int> e;

// ����, �ϻ�
vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

vector<vector<int>> dist(MAX, vector<int>(MAX, INF));

bool input()
{
	table = vector<vector<char>>(MAX, vector<char>(MAX));
	crossCoord.clear();
	crossRoads.clear();

	cin >> N >> M;

	if (N == 0 && M == 0)
		return false;

	int cnt{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] == 'A')
			{
				s.first = i;
				s.second = j;

				continue;
			}

			if (table[i][j] == 'B')
			{
				e.first = i;
				e.second = j;

				continue;
			}

			if ((int)table[i][j] >= (int)('0') && (int)table[i][j] <= (int)('9'))
			{
				crossCoord[table[i][j] - '0'] = make_pair(i, j);

				++cnt;
			}
		}
	}

	for (int i{ 0 }; i < cnt; ++i)
	{
		int temp;
		cin >> temp;

		char init;
		cin >> init;

		int a, b;

		cin >> a >> b;

		bool dir{ false };

		if (init == '|')
		{
			//a�� �������� �����ϱ� ���ؼ�(a�� �ʱ� ��ȣ���� Ȱ��ȭ �ð�) '|' ������ ���� a�� b�� �ٲ��ش�.
			//�� '|' ������ Ȱ��ȭ �ð� b�� a ��ġ�� ������.
			swap(a, b);
			dir = true;
		}

		crossRoads[make_pair(crossCoord[i].first, crossCoord[i].second)] = { dir,a,b };
	}

	return true;
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0 || table[r][c] == '.')
		return false;
	else
		return true;
}

void dijkstra()
{
	dist = vector<vector<int>>(MAX, vector<int>(MAX, INF));

	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,s.first,s.second });
	dist[s.first][s.second] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[r][c] < curDist)
			continue;

		if (r == e.first && c == e.second)
		{
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };

			if (isValid(nR, nC) == false)
				continue;

			auto newDist{ curDist + 1 };

			if ((int)table[nR][nC] >= (int)('0') && (int)table[nR][nC] <= (int)('9'))
			{
				bool dir{ get<0>(crossRoads[make_pair(nR,nC)]) };
				int a{ get<1>(crossRoads[make_pair(nR,nC)]) };
				int b{ get<2>(crossRoads[make_pair(nR,nC)]) };

				// i�� ���� �� �������� �����Ƿ� i/2�� �ؼ� bool�� ���ϰ� ���� üũ.
				// 0,1 -> '-' ���� , 2,3 -> '|' ����
				bool dirCur{ (int)(i / 2) };

				int remain{ curDist % (a + b) };

				//���� �ð����� ���� ���� ������ �� �ִ�.
				//���� ��ȣ���� '-'�������� 1,2�� ���� ������ 2�ʿ��� �� ��ȣ���� �ǳ� �� ���ٴ� ���̴�. �� 2�ʱ��� �����ִٴ� ���̴�.
				if (remain < a)
				{
					//�ʱ� ������ Ȱ��ȭ �ð� �ȿ� ������ ���,
					//��ȣ���� �ʱ� ����� ���� �� ������ ���ٸ�, �׳� �������� �ǰ�,
					//������ �ٸ��ٸ�, ���� ������ �Ǳ⸦ ��ٷ��� �ϹǷ� Ȱ��ȭ �ð� b�� ���� �Ѵ�.
					if (dirCur != dir)
					{
						newDist += (a - remain);
					}
				}
				else
				{
					//���� �� ��° ������ Ȱ��ȭ �ð����� �����ߴٸ�, �ʱ� ����� �� ������ ���ٸ�, ù ��° Ȱ��ȭ �ð����� ���� �ϹǷ�
					//���� �ֱ���� ��ٸ���.
					//���� �ʱ� ����� �ٸ��ٸ�, �׳� �������� �ȴ�.
					if (dirCur == dir)
					{
						newDist += (a + b - remain);
					}
				}
			}

			if (dist[nR][nC] > newDist)
			{
				dist[nR][nC] = newDist;
				pq.push({ newDist,nR,nC });
			}
		}
	}
}

void solve()
{
	while (true)
	{
		if (input() == false)
			return;

		dijkstra();

		if (dist[e.first][e.second] == INF)
			cout << "impossible" << endl;
		else
			cout << dist[e.first][e.second] << endl;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}