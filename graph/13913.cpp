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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;
#define MAX 100'001

int src{ 0 }, dst{ 0 };
vector<int> dist(MAX, INF);
vector<int> parent(MAX, -1);

void bfs()
{
	queue<int> q;
	q.push(src);
	dist[src] = 0;

	while (q.empty() == false)
	{
		auto cur = q.front();
		q.pop();

		int jump{ cur * 2 };
		int left{ cur - 1 };
		int right{ cur + 1 };

		if (jump >= 0 && jump < MAX)
		{
			if (dist[jump] > dist[cur] + 1)
			{
				dist[jump] = min(dist[jump], dist[cur] + 1);
				parent[jump] = cur;
				q.push(jump);
			}
		}

		if (left >= 0 && left < MAX)
		{
			if (dist[left] > dist[cur] + 1)
			{
				dist[left] = min(dist[left], dist[cur] + 1);
				parent[left] = cur;
				q.push(left);
			}
		}

		if (right >= 0 && right < MAX)
		{
			if (dist[right] > dist[cur] + 1)
			{
				dist[right] = min(dist[right], dist[cur] + 1);
				parent[right] = cur;
				q.push(right);
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> src >> dst;

	bfs();

	cout << dist[dst] << endl;

	stack<int> path;

	int cur = dst;

	while (cur != src)
	{
		path.push(cur);
		cur = parent[cur];
	}

	path.push(src);

	while (path.empty() == false)
	{
		cout << path.top() << " ";
		path.pop();
	}

	return 0;
}