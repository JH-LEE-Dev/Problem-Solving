#include <iostream>
#include <vector>
#include <limits>
#define endl '\n'
using namespace std;

vector<int> DP(5005, numeric_limits<int>::max() - 2);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 };

	cin >> N;

	DP[0] = 0;
	DP[3] = 1;
	DP[5] = 1;

	for (int i = 5; i <= N; ++i)
	{
		DP[i] = min(DP[i - 3] + 1, DP[i - 5] + 1);
	}


	if (DP[N] >= numeric_limits<int>::max() - 2)
		cout << -1;
	else
		cout << DP[N];

	return 0;
}