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
#define MAX 21

int N{ 0 };
vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
vector<vector<bool>> visited(MAX, vector<bool>(MAX, false));
int total{ 0 };

void input()
{
	cin >> N;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			cin >> dist[i][j];
			total += dist[i][j];
		}
	}

	//����� �����̱⿡ 2�� ����.
	total /= 2;
}

void floydWarshall()
{
	for (int middle{ 1 }; middle <= N; ++middle)
	{
		for (int left{ 1 }; left <= N; ++left)
		{
			for (int right{ 1 }; right <= N; ++right)
			{
				//dist[a][b] == dist[a][a] + dist[a][b] �̷��� ���� ��δ� ���ϸ� �ȵ�.
				if (left == right || left == middle || right == middle)
					continue;

				if (dist[left][right] == dist[left][middle] + dist[middle][right] && visited[left][right] == false)
				{
					total -= dist[left][right];
					visited[left][right] = true;
					//����� �����̱⿡ �Ÿ��� �ߺ����� ���� ���� ����
					visited[right][left] = true;
				}

				if (dist[left][right] > dist[left][middle] + dist[middle][right])
				{
					//�ִ� �Ÿ��� �ƴ� ���� ������ �����. �� �� ���� ����� ��ΰ� ���������� �ٸ� ���� ������ ���.
					total = -1;
					return;
				}
			}
		}
	}
}

void solve()
{
	floydWarshall();

	if (total == -1)
		cout << -1;
	else
		cout << total;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}