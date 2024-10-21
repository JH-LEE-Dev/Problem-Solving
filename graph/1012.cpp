#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

#define endl '\n'
using namespace std;

int N{ 0 }, M{ 0 }, K{ 0 }, counting{ 0 };
vector<vector<int>> table(51, vector<int>(51, 0));
vector<vector<bool>> visited(51, vector<bool>(51, 0));
set<pair<int, int>> cabbage;

void dfs()
{
	if (cabbage.empty())
		return;

	queue<pair<int, int>> myQueue;
	myQueue.push(*cabbage.begin());

	while (!myQueue.empty())
	{
		pair<int, int> current_vertex = myQueue.front();
		myQueue.pop();

		if (visited[current_vertex.first][current_vertex.second] == false)
		{
			cabbage.erase(pair<int, int>(current_vertex.first, current_vertex.second));

			if (current_vertex.first - 1 >= 0)
			{
				if (visited[current_vertex.first - 1][current_vertex.second] == false && table[current_vertex.first - 1][current_vertex.second] == 1)
					myQueue.push(pair<int, int>(current_vertex.first - 1, current_vertex.second));
			}

			if (current_vertex.second - 1 >= 0)
			{
				if (visited[current_vertex.first][current_vertex.second - 1] == false && table[current_vertex.first][current_vertex.second - 1] == 1)
					myQueue.push(pair<int, int>(current_vertex.first, current_vertex.second - 1));
			}

			if (current_vertex.first + 1 >= 0)
			{
				if (visited[current_vertex.first + 1][current_vertex.second] == false && table[current_vertex.first + 1][current_vertex.second] == 1)
					myQueue.push(pair<int, int>(current_vertex.first + 1, current_vertex.second));
			}

			if (current_vertex.second + 1 >= 0)
			{
				if (visited[current_vertex.first][current_vertex.second + 1] == false && table[current_vertex.first][current_vertex.second + 1] == 1)
					myQueue.push(pair<int, int>(current_vertex.first, current_vertex.second + 1));
			}

			visited[current_vertex.first][current_vertex.second] = true;

			if (cabbage.empty())
			{
				break;
			}
		}
	}

	++counting;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T{ 0 };
	cin >> T;
	string input;

	while (T != 0)
	{
		cin >> N >> M >> K;

		for (int i{ 0 }; i < K; ++i)
		{
			int first{ 0 }, second{ 0 };
			cin >> first >> second;
			table[first][second] = 1;
			cabbage.insert(pair<int, int>(first, second));
		}

		while (!cabbage.empty())
		{
			dfs();
		}

		cout << counting << endl;
		counting = 0;

		table = vector<vector<int>>(51, vector<int>(51, 0));
		visited = vector<vector<bool>>(51, vector<bool>(51, 0));
		--T;
	}

	return 0;
}