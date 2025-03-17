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

#define endl '\n'
#define INF numeric_limits<int>::max()

int N, M;
vector<int> arr;
ll maxVal{ -1 };

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		ll temp;
		cin >> temp;
		arr.push_back(temp);
		maxVal = max(maxVal, temp);
	}

	maxVal *= M;
}

void solve()
{
	ll left{ 1 };
	ll right{ maxVal };

	while (left <= right)
	{
		ll middle{ (left + right) / 2 };

		ll total{ 0 };

		for (int i{ 0 }; i < N; ++i)
		{
			total += middle / arr[i];

			if (total >= M)
				break;
		}

		if (total < M)
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