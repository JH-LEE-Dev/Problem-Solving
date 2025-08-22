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

int N, M, L;
vector<int> stopBy;
vector<int> dist;

void input()
{
	cin >> N >> M >> L;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;
		cin >> temp;

		stopBy.push_back(temp);
	}

	stopBy.push_back(0);
	stopBy.push_back(L);
	sort(stopBy.begin(), stopBy.end());

	for (int i{ 0 }; i < stopBy.size(); ++i)
	{
		if (i > 0)
			dist.push_back(stopBy[i] - stopBy[i - 1]);
	}
}

void solve()
{
	int left{ 1 };
	int right{ L };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };

		int cnt{ 0 };

		for (int i{ 0 }; i < dist.size(); ++i)
		{
			cnt += dist[i] / middle;

			if (dist[i] % middle == 0)
				cnt -= 1;
		}

		if (middle == 70)
			int a = 0;

		if (cnt > M)
			left = middle + 1;
		else
			right = middle - 1;
	}

	cout << left;
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