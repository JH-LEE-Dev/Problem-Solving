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

int r, c;
int n, k;
int minW{ 0 };
int maxW{ 0 };
vector<int> wrongItems;

void Input()
{
	cin >> r >> c >> n >> k;

	maxW = 1'000'000;

	for (int i{ 0 }; i < k; ++i)
	{
		int _r, _c;
		cin >> _r >> _c;

		wrongItems.push_back(_c);

		minW = max(minW, _r);
	}

	sort(wrongItems.begin(), wrongItems.end());
}

bool Check(int w)
{
	int cnt{ 1 };
	int pivot{ wrongItems[0] + w - 1 };

	for (const auto& row : wrongItems)
	{
		if (row <= pivot)
			continue;

		pivot = row + w - 1;
		++cnt;

		if (cnt > n)
			return false;
	}

	return true;
}

void Bsearch()
{
	int left{ minW };
	int right{ maxW };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };

		if (Check(middle))
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
		}
	}

	cout << left;
}

void Solve()
{
	Bsearch();
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