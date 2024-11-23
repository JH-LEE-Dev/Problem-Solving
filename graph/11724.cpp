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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 1'005

vector<vector<int>> edges(MAX, vector<int>());
vector<bool> visited(MAX, false);
int N{ 0 }, M{ 0 };
int result{ 0 };

void dfs(int start)
{
	stack<int> myStack;
	myStack.push(start);

	while (myStack.empty() == false)
	{
		auto cur = myStack.top();
		myStack.pop();

		if (visited[cur] == false)
		{
			visited[cur] = true;

			for (auto& dst : edges[cur])
			{
				myStack.push(dst);
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 };

		cin >> src >> dst;

		edges[src].push_back(dst);
		edges[dst].push_back(src);
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		if (visited[i] == false)
		{
			++result;
			dfs(i);
		}
	}

	cout << result;

	return 0;
}