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

#define MAX 1'001
#define endl '\n'
#define INF numeric_limits<int>::max()

ll T{ 0 }, nA{ 0 }, nB{ 0 };
vector<ll> A;
vector<ll> B;

vector<ll> sumA;
vector<ll> sumB;

void input()
{
	cin >> T >> nA;

	for (int i{ 0 }; i < nA; ++i)
	{
		ll temp{ 0 };
		cin >> temp;

		A.push_back(temp);
	}

	cin >> nB;

	for (int i{ 0 }; i < nB; ++i)
	{
		ll temp{ 0 };
		cin >> temp;

		B.push_back(temp);
	}
}

void calcSum()
{
	for (int i{ 0 }; i < nA; ++i)
	{
		ll tempA{ 0 };

		for (int j{ i }; j < nA; ++j)
		{
			tempA += A[j];
			sumA.push_back(tempA);
		}
	}

	for (int i{ 0 }; i < nB; ++i)
	{
		ll tempB{ 0 };

		for (int j{ i }; j < nB; ++j)
		{
			tempB += B[j];
			sumB.push_back(tempB);
		}
	}

	sort(sumA.begin(), sumA.end());
	sort(sumB.begin(), sumB.end());
}

void binarySearch()
{
	ll result{ 0 };

	for (int i{ 0 }; i < sumA.size(); ++i)
	{
		auto tempA{ sumA[i] };
		auto target{ T - tempA };

		auto iter_left{ lower_bound(sumB.begin(),sumB.end(),target) };

		auto iter_right{ upper_bound(sumB.begin(),sumB.end(),target) };

		if (iter_left == iter_right)
			continue;

		result += iter_right - iter_left;
	}

	cout << result;
}

void solve()
{
	calcSum();
	binarySearch();
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