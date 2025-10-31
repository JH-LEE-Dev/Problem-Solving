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

int l, c;
vector<char> arr;

void Input()
{
	cin >> l >> c;

	for (int i{ 0 }; i < c; ++i)
	{
		char temp;
		cin >> temp;

		arr.push_back(temp);
	}

	sort(arr.begin(), arr.end());
}

void Dfs(int cnt, int idx, int a, int b, string str)
{
	if (cnt == l)
	{
		if (a >= 1 && b >= 2)
			cout << str << '\n';

		return;
	}

	for (int i = idx; i < c; i++)
	{
		char c{ arr[i] };
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
			Dfs(cnt + 1, i + 1, a + 1, b, str + c);
		else
			Dfs(cnt + 1, i + 1, a, b + 1, str + c);
	}
}

void Solve()
{
	Dfs(0, 0, 0, 0, "");
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