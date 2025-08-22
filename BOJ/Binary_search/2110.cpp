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

int N{ 0 }, M{ 0 };
vector<int> houses;
int result{ -1 };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		int house{ 0 };
		cin >> house;

		houses.push_back(house);
	}

	sort(houses.begin(), houses.end());
}

void bSearch()
{
	int left{ 1 };
	int right{ *(--houses.end()) };
	int middle{ 0 };

	while (left <= right)
	{
		middle = (left + right) / 2;

		int cnt{ 0 };
		int cursor{ houses[0] };

		for (int i{ 0 }; i < N; ++i)
		{
			if (houses[i] - cursor >= middle)
			{
				++cnt;
				cursor = houses[i];
			}

			if (cnt >= M - 1)
				break;
		}

		if (cnt >= M - 1)
		{
			left = middle + 1;
			result = middle;
		}
		else
		{
			right = middle - 1;
		}
	}
}

void solve()
{
	bSearch();

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