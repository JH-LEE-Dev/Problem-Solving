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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

long long N{ 0 }, K{ 0 };

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> K;

	long long left{ 1 };
	long long right{ K };
	long long middle{ 0 };

	while (left < right)
	{
		middle = (left + right) / 2;

		int sum{ 0 };

		for (int i{ 1 }; i <= N; ++i)
		{
			sum += min(N, middle / i);
		}

		if (sum < K)
		{
			left = middle + 1;
		}
		else
		{
			right = middle;
		}
	}

	cout << right;

	return 0;
}