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

#define endl '\n'
#define INF numeric_limits<ll>::max()
using namespace std;

using ll = long long;
using vertex = tuple<ll, int, bool>;
#define MAX 200'001

struct mySwitch
{
	int row{ 0 };
	int col{ 0 };
	int idx{ 0 };
};

int N{ 0 }, M{ 0 }, K{ 0 };
vector<mySwitch> switches;
vector<vector<ll>> dist(MAX, vector<ll>(2, INF));
vector<vector<vector<pair<int, int>>>> edges(2, vector<vector<pair<int, int>>>(MAX, vector<pair<int, int>>()));
tuple<int, int> start{ -1,-1 };
bool valid{ true };
int goal{ -1 };

void generateGraph()
{
	sort(switches.begin(), switches.end(), [](const mySwitch& lhs, const mySwitch& rhs) {
		if (lhs.col < rhs.col)
			return true;
		else if (lhs.col == rhs.col)
		{
			if (lhs.row < rhs.row)
				return true;
			else
				return false;
		}
		else
			return false;
		});

	if (switches[0].col != 0)
	{
		valid = false;
		return;
	}
	else
	{
		start = make_tuple(switches[0].idx, switches[0].row);
	}

	for (int i{ 0 }; i < K; ++i)
	{
		if (i != 0 && switches[i - 1].col == switches[i].col)
		{
			edges[false][switches[i].idx].push_back({ switches[i - 1].idx,abs(switches[i - 1].row - switches[i].row) });
		}

		if (i != K - 1 && switches[i].col == switches[i + 1].col)
		{
			edges[false][switches[i].idx].push_back({ switches[i + 1].idx,abs(switches[i + 1].row - switches[i].row) });
		}
	}

	sort(switches.begin(), switches.end(), [](const mySwitch& lhs, const mySwitch& rhs) {
		if (lhs.row < rhs.row)
			return true;
		else if (lhs.row == rhs.row)
		{
			if (lhs.col < rhs.col)
				return true;
			else
				return false;
		}
		else
			return false;
		});

	for (int i{ 0 }; i < K; ++i)
	{
		if (i != 0 && switches[i - 1].row == switches[i].row)
		{
			edges[true][switches[i].idx].push_back({ switches[i - 1].idx,abs(switches[i - 1].col - switches[i].col) });
		}

		if (i != K - 1 && switches[i].row == switches[i + 1].row)
		{
			edges[true][switches[i].idx].push_back({ switches[i + 1].idx,abs(switches[i + 1].col - switches[i].col) });
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>>myPQ;
	myPQ.push({ get<1>(start),get<0>(start),false });
	dist[get<0>(start)][false] = get<1>(start);

	while (myPQ.empty() == false)
	{
		auto cur{ myPQ.top() };
		myPQ.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curType{ get<2>(cur) };

		if (dist[src][curType] < curDist)
			continue;

		if (dist[src][!curType] > curDist + 1)
		{
			dist[src][!curType] = curDist + 1;
			myPQ.push({ curDist + 1,src,!curType });
		}

		for (auto& edge : edges[curType][src])
		{
			auto dst{ edge.first };
			auto w{ edge.second };
			auto newDist{ curDist + w };

			if (dist[dst][curType] > newDist)
			{
				dist[dst][curType] = newDist;
				myPQ.push({ newDist,dst,curType });
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M >> K;
	swap(N, M);

	bool dstSwitch{ false };

	for (int i{ 0 }; i < K; ++i)
	{
		int row{ 0 }, col{ 0 };
		cin >> col >> row;

		switches.push_back({ row - 1,col - 1,i });

		if (row == N && col == M)
		{
			dstSwitch = true;
			goal = i;
		}
	}

	if (dstSwitch == false)
	{
		switches.push_back({ N - 1,M - 1,K });
		++K;
		goal = K - 1;
	}

	generateGraph();

	if (valid == false)
	{
		cout << -1;
		return 0;
	}

	dijkstra();

	auto result{ min(dist[goal][true], dist[goal][false]) };
	if (result == INF)
		cout << -1;
	else
		cout << min(dist[goal][true], dist[goal][false]);

	return 0;
}