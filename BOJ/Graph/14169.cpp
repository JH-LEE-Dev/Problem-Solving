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
using vertex = tuple<ll, ll, ll, bool, int>;

#define endl '\n'
#define INF numeric_limits<ll>::max()
#define MAX 100'002

int N;
map<ll, vector<pair<ll, int>>> coords_row;
map<ll, vector<pair<ll, int>>> coords_col;
pair<ll, ll> start;
pair<ll, ll> goal;
vector<vector<ll>> dist(2, vector<ll>(MAX, INF));

void input()
{
	cin >> N;
	cin >> start.first >> start.second;
	cin >> goal.first >> goal.second;

	coords_row[start.first].push_back({ start.second,0 });
	coords_col[start.second].push_back({ start.first,0 });

	for (int i{ 1 }; i <= N; ++i)
	{
		ll r, c;

		cin >> r >> c;

		coords_row[r].emplace_back(c, i);
		coords_col[c].emplace_back(r, i);
	}

	coords_row[goal.first].push_back({ goal.second,N + 1 });
	coords_col[goal.second].push_back({ goal.first,N + 1 });

	for (auto& r : coords_row)
	{
		sort(r.second.begin(), r.second.end());
	}

	for (auto& c : coords_col)
	{
		sort(c.second.begin(), c.second.end());
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	pq.push({ 0,start.first,start.second,0,0 });
	pq.push({ 0,start.first,start.second,1,0 });

	dist[0][0] = 0;
	dist[1][0] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };
		auto curType{ get<3>(cur) };
		auto curIdx{ get<4>(cur) };

		if (dist[curType][curIdx] < curDist)
			continue;

		auto row_it{ lower_bound(coords_row[r].begin(),coords_row[r].end(),make_pair(c,0)) };
		auto col_it{ lower_bound(coords_col[c].begin(),coords_col[c].end(),make_pair(r,0)) };


		if (row_it != coords_row[r].begin())
		{
			auto cur_it{ row_it };
			auto new_it{ --cur_it };

			auto nR{ r };
			auto nC{ new_it->first };
			auto idx{ new_it->second };
			auto newType{ curType };
			auto newDist{ curDist };

			if (curType != 0)
			{
				newDist += 1;
				newType = 1 - curType;

				if (dist[newType][idx] > newDist)
				{
					dist[newType][idx] = newDist;
					pq.push({ newDist,nR,nC,newType,idx });
				}
			}
			else
			{
				if (dist[newType][idx] > newDist)
				{
					dist[newType][idx] = newDist;
					pq.push({ newDist,nR,nC,newType,idx });
				}
			}
		}

		if (row_it != --coords_row[r].end())
		{
			auto cur_it{ row_it };
			auto new_it{ ++cur_it };

			auto nR{ r };
			auto nC{ new_it->first };
			auto idx{ new_it->second };
			auto newType{ curType };
			auto newDist{ curDist };

			if (curType != 0)
			{
				newDist += 1;
				newType = 1 - curType;

				if (dist[newType][idx] > newDist)
				{
					dist[newType][idx] = newDist;
					pq.push({ newDist,nR,nC,newType,idx });
				}
			}
			else
			{
				if (dist[newType][idx] > newDist)
				{
					dist[newType][idx] = newDist;
					pq.push({ newDist,nR,nC,newType,idx });
				}
			}
		}

		if (col_it != coords_col[c].begin())
		{
			auto cur_it{ col_it };
			auto new_it{ --cur_it };

			auto nC{ c };
			auto nR{ new_it->first };
			auto idx{ new_it->second };
			auto newType{ curType };
			auto newDist{ curDist };

			if (curType != 1)
			{
				newDist += 1;
				newType = 1 - curType;

				if (dist[newType][idx] > newDist)
				{
					dist[newType][idx] = newDist;
					pq.push({ newDist,nR,nC,newType,idx });
				}
			}
			else
			{
				if (dist[newType][idx] > newDist)
				{
					dist[newType][idx] = newDist;
					pq.push({ newDist,nR,nC,newType,idx });
				}
			}
		}

		if (col_it != --coords_col[c].end())
		{
			auto cur_it{ col_it };
			auto new_it{ ++cur_it };

			auto nC{ c };
			auto nR{ new_it->first };
			auto idx{ new_it->second };
			auto newType{ curType };
			auto newDist{ curDist };

			if (curType != 1)
			{
				newDist += 1;
				newType = 1 - curType;

				if (dist[newType][idx] > newDist)
				{
					dist[newType][idx] = newDist;
					pq.push({ newDist,nR,nC,newType,idx });
				}
			}
			else
			{
				if (dist[newType][idx] > newDist)
				{
					dist[newType][idx] = newDist;
					pq.push({ newDist,nR,nC,newType,idx });
				}
			}
		}
	}
}

void solve()
{
	dijkstra();

	ll result{ min(dist[0][N + 1], dist[1][N + 1]) };

	if (result == INF)
		cout << -1;
	else
		cout << result;
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