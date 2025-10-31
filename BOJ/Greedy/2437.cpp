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

int n;
vector<int> arr;

void Input()
{
	cin >> n;

	for (int i{ 0 }; i < n; ++i)
	{
		int temp;
		cin >> temp;
		arr.push_back(temp);
	}
}

void Solve()
{
	sort(arr.begin(), arr.end());

	int sum{ 0 };

	for (int i{ 0 }; i < n; ++i)
	{
		if (sum + 1 < arr[i])
			break;

		sum += arr[i];
	}

	cout << sum + 1;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}