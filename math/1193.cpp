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
#define MAX 10'000'001

int N;

void input()
{
	cin >> N;
}

void solve()
{
	int total{ 1 };
	int cnt{ 1 };

	for (int i{ 2 }; i < MAX; ++i)
	{
		if (total >= N)
			break;

		++cnt;
		total += i;
	}

	if (cnt % 2 == 0)
	{
		if (total != cnt)
			total -= (cnt - 1);

		int up{ 1 };
		int down{ cnt };

		while (true)
		{
			if (total == N)
				break;

			++total;

			++up;
			--down;
		}

		cout << up << '/' << down;
	}
	else
	{
		if (total != cnt)
			total -= (cnt - 1);
		else
		{
			cout << 1 << '/' << cnt;

			return;
		}

		int up{ cnt };
		int down{ 1 };

		while (true)
		{
			if (total == N)
				break;

			++total;

			--up;
			++down;
		}

		cout << up << '/' << down;
	}
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