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
#define INF numeric_limits<ll>::max()

ll N{ 0 };
vector<ll> A;
vector<ll> B;
vector<ll> C;
vector<ll> D;

vector<ll> AB_Partial;
vector<ll> CD_Partial;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		ll a, b, c, d;

		cin >> a >> b >> c >> d;

		A.push_back(a);
		B.push_back(b);
		C.push_back(c);
		D.push_back(d);
	}
}

void partialSum()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			AB_Partial.push_back({ A[i] + B[j] });
			CD_Partial.push_back({ C[i] + D[j] });
		}
	}

	sort(AB_Partial.begin(), AB_Partial.end());
	sort(CD_Partial.begin(), CD_Partial.end());
}

int lowerBound(ll target)
{
	ll left{ 0 };
	ll right{ (int)CD_Partial.size() - 1 };

	while (left <= right)
	{
		ll middle{ (left + right) / 2 };
		ll middleNum{ CD_Partial[middle] };

		if (middleNum < target)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}

	return left;
}

ll upperBound(ll target)
{
	ll left{ 0 };
	ll right{ (ll)CD_Partial.size() - 1 };

	while (left <= right)
	{
		ll middle{ (left + right) / 2 };
		ll middleNum{ CD_Partial[middle] };

		if (middleNum <= target)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}

	return left;
}

void solve()
{
	partialSum();

	ll result{ 0 };

	for (int i{ 0 }; i < AB_Partial.size(); ++i)
	{
		ll left{ lowerBound(-AB_Partial[i]) };
		ll right{ upperBound(-AB_Partial[i]) };

		result += (right - left);
	}

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