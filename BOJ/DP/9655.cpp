#include <iostream>
#include <vector>
using namespace std;

vector<int> DP(1005, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 };

	cin >> N;

	DP[0] = 0;
	DP[1] = 1;
	DP[2] = 2;

	for (int i = 3; i <= N; i++) 
	{
		DP[i] = min(DP[i - 1] + 1, DP[i - 3] + 1);
	}

	if (DP[N] % 2 == 1) 
	{
		cout << "SK";
	}
	else 
	{
		cout << "CY";
	}

	return 0;
}