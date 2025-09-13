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

string S, T;

void Input()
{
	cin >> S >> T;
}

void Solve()
{
	while (true)
	{
		if (T == S)
		{
			cout << 1;
			return;
		}

		if (T.empty())
		{
			cout << 0;
			return;
		}

		int Len{ (int)T.length() - 1 };

		if (T[Len] == 'A')
		{
			T.pop_back();
		}
		else
		{
			T.pop_back();
			reverse(T.begin(), T.end());
		}
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