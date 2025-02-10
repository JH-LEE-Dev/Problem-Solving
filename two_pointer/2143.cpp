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

map<ll, ll> sumA;
map<ll, ll> sumB;

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

			sumA[tempA] += 1;
		}
	}

	for (int i{ 0 }; i < nB; ++i)
	{
		ll tempB{ 0 };

		for (int j{ i }; j < nB; ++j)
		{
			tempB += B[j];

			sumB[tempB] += 1;
		}
	}
}

void twoPointer()
{
	ll result{ 0 };

	auto left{ sumA.begin() };
	auto right{ --(sumB.end()) };

	//right.begin()에서 -- 연산자 적용하면 end가 되므로 둘 다 end를 종료 기준으로 잡았음
	while (left != sumA.end() && right != sumB.end())
	{
		ll sum = left->first + right->first;

		if (sum == T)
		{
			result += (left->second) * (right->second);
			--right;
			++left;
		}

		if (sum < T)
			left++;
		else if (sum > T)
			right--;
	}

	cout << result;
}

void solve()
{
	calcSum();
	twoPointer();
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