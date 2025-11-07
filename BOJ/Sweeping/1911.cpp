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

int n, l;
vector<pair<int, int>> ponds;

void Input()
{
	cin >> n >> l;

	for (int i{ 0 }; i < n; ++i)
	{
		int start, end;
		cin >> start >> end;

		if (start > end)
			swap(start, end);

		ponds.push_back({ start,end });
	}

	sort(ponds.begin(), ponds.end());
}

void Solve()
{
	int pivot{ 0 };
	int cnt{ 0 };

	for (int i{ 0 }; i < n; ++i)
	{
		auto [start, end] {ponds[i]};

		if (pivot - 1 >= end)
			continue;

		if (pivot > start)
		{
			start = pivot;
		}
		else
			pivot = start;

		int w{ end - start };

		int div{ w / l };

		if (w % l != 0)
			++div;

		pivot = pivot + l * div;

		cnt += div;
	}

	cout << cnt;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}