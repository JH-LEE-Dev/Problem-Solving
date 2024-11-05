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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

void func(int a, int b, int k)
{
	if (k == 1)
	{
		cout << a << ' ' << b << endl;
		return;
	}

	func(a, 6 - a - b, k - 1);
	cout << a << ' ' << b << endl;
	func(6 - a - b, b, k - 1);
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int K{ 0 };
	cin >> K;

	cout << (1 << K) - 1 << endl;
	func(1, 3, K);

	return 0;
}