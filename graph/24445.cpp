#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <algorithm>

#define endl '\n'
using namespace std;

int N{ 0 }, M{ 0 }, R{ 0 };

class Graph
{
public:
	Graph(int N) : V(N)
	{
		edge_list = vector<vector<int>>(100'005, vector<int>());
	}
	auto vertices() const { return V; }
	auto& edges() const { return edge_list; }
	auto edges(int v) const
	{
		return edge_list[v];
	}

	void add_edge(int src, int dst, int weight)
	{
		if (src >= 1 && src <= V && dst >= 1 && dst <= V)
			edge_list[src].push_back(dst);
	}

	void sortByGreater()
	{
		for (int i{ 1 }; i <= V; ++i)
		{
			sort(edge_list[i].begin(), edge_list[i].begin() + edge_list[i].size(), greater<int>());
		}
	}

private:
	unsigned V;
	vector<vector<int>> edge_list;
};

void breadth_first_search(const Graph& G, int start)
{
	queue<int> Queue;
	vector<bool> visited(N + 5, false);
	vector<int> visit_order(N + 5, 0);
	Queue.push(start);

	int order{ 0 };

	while (!Queue.empty())
	{
		auto current_vertex = Queue.front();
		Queue.pop();

		if (visited[current_vertex] == false)
		{
			++order;
			visited[current_vertex] = true;
			visit_order[current_vertex] = order;

			for (auto& e : G.edges(current_vertex))
			{
				if (visited[e] == false)
				{
					Queue.push(e);
				}
			}
		}
	}

	for (int i{ 1 }; i <= N; ++i)
	{
		cout << visit_order[i] << endl;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M >> R;

	Graph G(N);

	map<int, vector<pair<int, int>>> edge_map;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 }, weight{ 0 };
		cin >> src >> dst;

		G.add_edge(src, dst, weight);
		G.add_edge(dst, src, weight);
	}
	G.sortByGreater();

	breadth_first_search(G, R);
}