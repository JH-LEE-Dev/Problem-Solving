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

int N{ 0 }, M{ 0 }, T{ 0 };
vector<int> A;
vector<int> B;

void input()
{
	cin >> T;
}

void inputArray()
{
	A.clear();
	B.clear();

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp{ 0 };
		cin >> temp;

		A.push_back(temp);
	}

	cin >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int temp{ 0 };
		cin >> temp;

		B.push_back(temp);
	}
}

bool lowerBound(int target)
{
	int left{ 0 };
	int right{ N - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ A[middle] };

		if (middleNum < target)
			left = middle + 1;

		if (middleNum > target)
			right = middle - 1;

		if (middleNum == target)
			return true;
	}

	return false;
}

void solve()
{
	for (int i{ 0 }; i < T; ++i)
	{
		inputArray();

		sort(A.begin(), A.end());

		for (int i{ 0 }; i < M; ++i)
		{
			if (lowerBound(B[i]))
				cout << 1 << endl;
			else
				cout << 0 << endl;
		}
	}
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