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
#define INF 1e9
#define MAX 2'005
using namespace std;

int V{ 0 }, E{ 0 }, cCount{ 0 }, start{ 0 };
int must_src{ 0 }, must_dst{ 0 };
vector<int> candidate;

vector < vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist_first(MAX, INF);
vector<int> dist_second(MAX, INF);
vector<int> dist_third(MAX, INF);

void djk(int src, vector<int>& _dist)
{
	priority_queue<pair<int, int>> pQ;
	pQ.push({ 0,src });
	_dist[src] = 0;

	while (!pQ.empty())
	{
		auto cur = pQ.top();
		pQ.pop();

		int curDist = -cur.first;

		for (auto& it : edges[cur.second])
		{
			int newDist = curDist + it.second;

			if (_dist[it.first] > newDist)
			{
				_dist[it.first] = newDist;
				pQ.push({ -newDist,it.first });
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

	while (T != 0)
	{
		edges = vector < vector<pair<int, int>>>(MAX, vector<pair<int, int>>());
		dist_first = vector<int>(MAX, INF);
		dist_second = vector<int>(MAX, INF);
		dist_third = vector<int>(MAX, INF);
		candidate.clear();

		cin >> V >> E >> cCount;
		cin >> start >> must_src >> must_dst;

		for (int i{ 0 }; i < E; ++i)
		{
			int src{ 0 }, dst{ 0 }, w{ 0 };

			cin >> src >> dst >> w;

			edges[src].push_back({ dst,w });
			edges[dst].push_back({ src,w });
		}

		for (int i{ 0 }; i < cCount; ++i)
		{
			int must{ 0 };
			cin >> must;
			candidate.push_back(must);
		}

		djk(start, dist_first);
		djk(must_src, dist_second);
		djk(must_dst, dist_third);

		vector<int> result;

		for (auto& it : candidate)
		{
			if (dist_first[it] == dist_first[must_src] + dist_second[must_dst] + dist_third[it])
				result.push_back(it);
			else if (dist_first[it] == dist_first[must_dst] + dist_second[must_dst] + dist_second[it])
				result.push_back(it);
		}

		sort(result.begin(), result.end(), less<int>());

		for (auto& it : result)
		{
			cout << it << " ";
		}

		cout << endl;
		--T;
	}

	return 0;
}