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

int N;

void input()
{
	cin >> N;
}

void solve()
{
	int cnt{ 0 };

	for (int i{ 1 }; i <= N; ++i)
	{
		int num{ i };

		vector<int> division;

		if (i < 100)
		{
			++cnt;
			continue;
		}

		if (num == 1000)
		{
			int first{ num / 1000 };

			num %= 1000;

			division.push_back(first);
		}

		int second{ num / 100 };

		num %= 100;

		division.push_back(second);

		int third{ num / 10 };

		num %= 10;

		division.push_back(third);

		division.push_back(num);

		if (division.size() > 1)
		{
			int d{ INF };
			bool isValid{ true };

			for (int j{ 1 }; j < division.size(); ++j)
			{
				if (d == INF)
					d = division[j] - division[j - 1];
				else
				{
					if (d != division[j] - division[j - 1])
					{
						isValid = false;
						break;
					}
				}
			}

			if (isValid == true)
				++cnt;
		}
		else
			++cnt;
	}

	cout << cnt;
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