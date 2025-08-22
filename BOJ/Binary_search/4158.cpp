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
vector<ll> A;
vector<ll> B;

void input()
{
	A.clear();
	B.clear();

	for (int i{ 0 }; i < N; ++i)
	{
		ll cd;
		cin >> cd;

		A.push_back(cd);
	}

	for (int i{ 0 }; i < M; ++i)
	{
		ll cd;
		cin >> cd;

		B.push_back(cd);
	}
}

bool bSearch(ll target)
{
	ll left{ 0 };
	ll right{ (ll)B.size() - 1 };

	while (left <= right)
	{
		ll middle{ (left + right) / 2 };
		ll middleNum(B[middle]);

		if (middleNum < target)
			left = middle + 1;
		else
			right = middle - 1;
	}

	if (left >= (ll)B.size() || B[left] != target)
		return false;
	else
		return true;
}

void solve()
{
	int total{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		if (bSearch(A[i]))
			++total;
	}

	cout << total << endl;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (true)
	{
		cin >> N >> M;

		if (N == 0 && M == 0)
			return 0;

		input();
		solve();
	}

	return 0;
}