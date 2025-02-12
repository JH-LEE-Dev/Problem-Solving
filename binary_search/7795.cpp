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

int T{ 0 }, A{ 0 }, B{ 0 };
vector<int> arr_A;
vector<int> arr_B;

void input()
{
	cin >> T;
}

void inputCase()
{
	arr_A.clear();
	arr_B.clear();

	cin >> A >> B;

	for (int i{ 0 }; i < A; ++i)
	{
		int temp{ 0 };
		cin >> temp;

		arr_A.push_back(temp);
	}

	for (int i{ 0 }; i < B; ++i)
	{
		int temp{ 0 };
		cin >> temp;

		arr_B.push_back(temp);
	}
}

int binarySearch(int Target)
{
	int left{ 0 };
	int right{ B - 1 };
	int middle{ (left + right) / 2 };
	int middleNum{ arr_B[middle] };

	while (left <= right)
	{
		middle = (left + right) / 2;
		middleNum = arr_B[middle];

		if (middleNum < Target)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return left;
}

void solve()
{
	for (int i{ 0 }; i < T; ++i)
	{
		int total{ 0 };

		inputCase();

		sort(arr_B.begin(), arr_B.end());

		for (int j{ 0 }; j < A; ++j)
		{
			total += binarySearch(arr_A[j]);
		}

		cout << total << endl;
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