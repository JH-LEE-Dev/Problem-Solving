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

vector<string> result(100000, "");

void func(int N, int leftTop, bool middle)
{
	if (middle == true)
	{
		for (int i{ 0 }; i < N; ++i)
		{
			for (int j{ 0 }; j < N; ++j)
			{
				result[leftTop + i] += ' ';
			}
		}
	}
	else
	{
		if (N == 3)
		{
			for (int i{ 0 }; i < N; ++i)
			{
				for (int j{ 0 }; j < N; ++j)
				{
					if (i == 1 && j == 1)
						result[leftTop + i] += ' ';
					else
						result[leftTop + i] += '*';
				}
			}
		}
		else
		{
			for (int i{ 0 }; i < 3; ++i)
			{
				for (int j{ 0 }; j < 3; ++j)
				{
					if (i == 1 && j == 1)
						func(N / 3, leftTop + i * (N / 3), true);
					else
						func(N / 3, leftTop + i * (N / 3), false);
				}
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 };
	cin >> N;

	func(N, 0, false);

	for (int i{ 0 }; i < N; ++i)
	{
		cout << result[i] << endl;
	}

	return 0;
}