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

	//양방향 간선이기에 2로 나눔.
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
				//dist[a][b] == dist[a][a] + dist[a][b] 이렇게 같은 경로는 평가하면 안됨.
				if (left == right || left == middle || right == middle)
					continue;

				if (dist[left][right] == dist[left][middle] + dist[middle][right] && visited[left][right] == false)
				{
					total -= dist[left][right];
					visited[left][right] = true;
					//양방향 간선이기에 거리를 중복으로 빼는 것을 방지
					visited[right][left] = true;
				}

				if (dist[left][right] > dist[left][middle] + dist[middle][right])
				{
					//최단 거리가 아닌 값이 제공된 경우임. 즉 더 적은 비용의 경로가 존재하지만 다른 값이 제공된 경우.
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