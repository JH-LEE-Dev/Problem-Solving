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
#define MAX 1'000'000'000

int N, M;
vector<int> jewels;

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int temp;
		cin >> temp;

		jewels.push_back(temp);
	}
}

void solve()
{
	int left{ 1 };
	int right{ MAX };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };

		int cnt{ 0 };

		for (int i{ 0 }; i < M; ++i)
		{
			int divide{ jewels[i] / middle };

			if (jewels[i] % middle != 0)
				divide += 1;

			cnt += divide;
		}

		if (cnt > N)
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