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
#define MAX 100'001

int N{ 0 };
vector<int> boat;

using vertex = tuple<int, int, int>;
enum SIDE { START, GOAL };
int result{ 0 };

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int input;
		cin >> input;

		boat.push_back(input);
	}

	sort(boat.begin(), boat.begin() + N, greater<int>());
}

bool dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	vector<vector<int>> dist((1 << N), vector<int>(2, INF));

	if (N == 1)
	{
		result = boat[0];
		return true;
	}

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			if (i == j)
				continue;

			if (boat[i] > boat[j])
			{
				int state{ 0 };
				state |= (1 << i);
				state |= (1 << j);

				if (dist[state][GOAL] > boat[i])
				{
					pq.push({ boat[i],GOAL,state });
					dist[state][GOAL] = boat[i];
				}
			}
		}
	}

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto src{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto boat_state{ get<2>(cur) };

		if (dist[boat_state][src] < curDist)
			continue;

		if (boat_state == (1 << N) - 1)
		{
			result = curDist;
			return true;
		}

		if (src == START)
		{
			for (int i{ 0 }; i < N; ++i)
			{
				if ((boat_state & (1 << i)) == (1 << i))
					continue;

				for (int j{ 0 }; j < N; ++j)
				{
					if (i == j)
						continue;

					if (boat[i] > boat[j])
					{
						int state{ boat_state };

						if ((state & (1 << j)) == (1 << j))
							continue;

						state |= (1 << i);
						state |= (1 << j);

						if (dist[state][GOAL] > curDist + boat[i])
						{
							pq.push({ curDist + boat[i],GOAL,state });
							dist[state][GOAL] = curDist + boat[i];
						}
					}
				}
			}
		}
		else
		{
			for (int i{ 0 }; i < N; ++i)
			{
				if ((boat_state & (1 << i)) != (1 << i))
					continue;

				auto temp_state{ boat_state };

				temp_state = temp_state & ~(1 << i);

				if (dist[temp_state][START] > curDist + boat[i])
				{
					pq.push({ curDist + boat[i],START,temp_state });
					dist[temp_state][START] = curDist + boat[i];
				}
			}
		}
	}

	return false;
}

void solve()
{
	if (dijkstra())
	{
		cout << result;
	}
	else
	{
		cout << -1;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}