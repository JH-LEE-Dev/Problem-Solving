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

int M, N;
#define endl '\n'
#define INF numeric_limits<int>::max()

vector<int> cookie;
int maxVal{ 0 };

void input()
{
	cin >> M >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;
		cin >> temp;

		cookie.push_back(temp);
		maxVal = max(maxVal, temp);
	}
}

int bSearch()
{
	int left{ 1 };
	int right{ maxVal };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };

		int cnt{ 0 };

		for (int i{ 0 }; i < N; ++i)
		{
			cnt += cookie[i] / middle;
		}

		if (cnt >= M)
			left = middle + 1;
		else
		{
			right = middle - 1;
		}
	}

	return left - 1;
}

void solve()
{
	sort(cookie.begin(), cookie.end());

	cout << bSearch();
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