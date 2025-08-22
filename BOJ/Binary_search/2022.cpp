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

double x, y, c;

void input()
{
	cin >> x >> y >> c;
}

double func(double num)
{
	auto left{ 1 / sqrt((x * x - num * num)) };
	auto right{ 1 / sqrt((y * y - num * num)) };

	return left + right;
}

void bSearch()
{
	double left{ 0 };
	double right{ (double)min(x,y) };

	while (abs(left - right) > 1e-4)
	{
		double middle{ (left + right) / 2 };

		double result{ func(middle) };

		if (result < (double)1 / c)
			left = middle;
		else
			right = middle;
	}

	cout << (left + right) / 2;
}

void solve()
{
	bSearch();
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