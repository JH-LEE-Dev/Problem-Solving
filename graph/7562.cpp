#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define endl '\n'
using namespace std;

#define MAX 300
int N{ 0 }, K{ 0 };
pair<int, int> src;
pair<int, int> dst;
queue<pair<int, int>> myQueue;
vector<vector<bool>> visited(MAX + 5, vector<bool>(MAX + 5, false));

vector<vector<int>> dist(MAX + 5, vector<int>(MAX + 5, numeric_limits<int>::max()));

int x_dir[8] = { -1,-2 ,-2,-1,1,2,1,2 };
int y_dir[8] = { -2,-1,1,2,-2,-1,2 ,1 };

void bfs()
{
	visited = vector<vector<bool>>(MAX + 5, vector<bool>(MAX + 5, false));
	dist = vector<vector<int>>(MAX + 5, vector<int>(MAX + 5, numeric_limits<int>::max()));
	myQueue.push(src);

	visited[src.first][src.second] = true;

	dist[src.first][src.second] = 0;

	while (!myQueue.empty())
	{
		auto current_vertex{ myQueue.front() };
		myQueue.pop();

		for (int i{ 0 }; i < 8; ++i)
		{
			int newX = current_vertex.first + x_dir[i];
			int newY = current_vertex.second + y_dir[i];

			if (newX >= 0 && newX < N && newY >= 0 && newY < N && visited[newX][newY] == false)
			{
				myQueue.push({ newX,newY });
				visited[newX][newY] = true;
				dist[newX][newY] = dist[current_vertex.first][current_vertex.second] + 1;
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T{ 0 };
	cin >> T;

	for (int i{ 0 }; i < T; ++i)
	{
		cin >> N;
		cin >> src.first >> src.second;
		cin >> dst.first >> dst.second;

		bfs();

		cout << dist[dst.first][dst.second] << endl;
	}

	return 0;
}