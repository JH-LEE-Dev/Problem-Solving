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
using ll = long long;
using vertex = tuple<ll, string>;


#define MAX 101
#define endl '\n'
#define INF numeric_limits<ll>::max()

ll R{ 0 }, N{ 0 }, M{ 0 }, K{ 0 };
unordered_multimap<string, tuple<string, string, ll>> edges;
vector<string> cities;
unordered_set<string> discount_1;
unordered_set<string> discount_2;
unordered_map<string, ll> price;

ll result{ 0 };
ll result_discount{ 0 };

void input()
{
	discount_1.insert({ "Mugunghwa" });
	discount_1.insert({ "ITX-Cheongchun" });
	discount_1.insert({ "ITX-Saemaeul" });
	discount_2.insert({ "S-Train" });
	discount_2.insert({ "V-Train" });

	cin >> N >> R;

	for (int i{ 0 }; i < N; ++i)
	{
		string input;
		cin >> input;
	}

	cin >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		string input;
		cin >> input;

		cities.push_back(input);
	}

	cin >> K;

	for (int i{ 0 }; i < K; ++i)
	{
		string traffic, src, dst;
		ll w{ 0 };

		cin >> traffic >> src >> dst >> w;
		w *= 2;

		edges.insert({ src,{dst,traffic,w} });
		edges.insert({ dst,{src,traffic,w} });
	}
}

void dijkstra()
{
	int cnt{ 0 };
	++cnt;

	unordered_map<string, ll> dist;
	dist[*cities.begin()] = 0;

	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,*cities.begin() });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		if (src == cities[cnt])
		{
			if (cnt == M - 1)
			{
				result += curDist;
				return;
			}

			++cnt;
			dist.clear();
			pq = priority_queue<vertex, vector<vertex>, greater<vertex>>();
			dist[src] = curDist;
		}

		auto edge{ edges.equal_range(src) };

		for (auto it{ edge.first }; it != edge.second; ++it)
		{
			auto dst{ get<0>(it->second) };
			auto traffic{ get<1>(it->second) };
			auto w{ get<2>(it->second) };
			auto newDist{ w + curDist };

			if (dist.find(dst) != dist.end())
			{
				if (dist[dst] > newDist)
				{
					dist[dst] = newDist;
					pq.push({ newDist,dst });
				}
			}
			else
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void dijkstra_discount()
{
	int cnt{ 0 };
	++cnt;

	unordered_map<string, ll> dist;
	dist[*cities.begin()] = 0;

	priority_queue<vertex, vector<vertex>, greater<vertex>>pq;
	pq.push({ 0,*cities.begin() });

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };

		if (dist[src] < curDist)
			continue;

		if (src == cities[cnt])
		{
			if (cnt == M - 1)
			{
				result_discount += curDist;
				return;
			}

			++cnt;
			dist.clear();
			pq = priority_queue<vertex, vector<vertex>, greater<vertex>>();
			dist[src] = curDist;
		}

		auto edge{ edges.equal_range(src) };

		for (auto it{ edge.first }; it != edge.second; ++it)
		{
			auto dst{ get<0>(it->second) };
			auto traffic{ get<1>(it->second) };
			auto w{ get<2>(it->second) };


			if (discount_1.find(traffic) != discount_1.end())
				w = 0;
			else if (discount_2.find(traffic) != discount_2.end())
				w /= 2;

			auto newDist{ w + curDist };

			if (dist.find(dst) != dist.end())
			{
				if (dist[dst] > newDist)
				{
					dist[dst] = newDist;
					pq.push({ newDist,dst });
				}
			}
			else
			{
				dist[dst] = newDist;
				pq.push({ newDist,dst });
			}
		}
	}
}

void solve()
{
	dijkstra();
	dijkstra_discount();

	if (result / 2 > result_discount / 2 + R)
		cout << "Yes";
	else
		cout << "No";
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