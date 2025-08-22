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
#define MAX 51

int N;
vector<int> Arr;
vector<int> DP(MAX, 0);

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);
	}
}

void Solve()
{
	sort(Arr.begin(), Arr.end(), greater<int>());

	DP[0] = 0;
	DP[1] = Arr[0];

	for (int i{ 2 }; i <= N; ++i)
	{
		DP[i] = max(DP[i - 1] + Arr[i - 1], DP[i - 2] + Arr[i - 2] * Arr[i - 1]);
	}

	cout << DP[N];
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