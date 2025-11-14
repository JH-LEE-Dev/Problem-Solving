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

int n, k;
string num;

void Input()
{
	cin >> n >> k;

	cin >> num;
}

void Solve()
{
	deque<int> myDeque;
	int cnt{ n - k };

	myDeque.push_back(num[0] - '0');
	for (int i{ 1 }; i < n; ++i)
	{
		while (myDeque.empty() == false && myDeque.back() < num[i] - '0' && k != 0)
		{
			myDeque.pop_back();
			--k;
		}

		myDeque.push_back(num[i] - '0');
	}

	while (cnt != 0)
	{
		cout << myDeque.front();
		myDeque.pop_front();
		--cnt;
	}
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