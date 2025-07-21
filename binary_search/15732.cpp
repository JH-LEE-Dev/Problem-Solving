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
using LL = long long;

#define endl '\n'
#define INF numeric_limits<int>::max()

int N, K, D;
vector<int> Arr;
vector<tuple<int, int, int>> Order;

void Input()
{
	cin >> N >> K >> D;

	for (int i{ 0 }; i < K; ++i)
	{
		int Start, End, Range;
		cin >> Start >> End >> Range;

		Order.push_back({ Start,End,Range });
	}
}

LL IsValid(int Target)
{
	LL Cnt{ 0 };

	for (int i{ 0 }; i < K; ++i)
	{
		int Start{ get<0>(Order[i]) };
		int End{ get<1>(Order[i]) };
		int Range{ get<2>(Order[i]) };
		int TempTarget{ Target };

		if (Target < Start)
			continue;

		if (Target > End)
			TempTarget = End;

		Cnt += (TempTarget - Start) / Range;

		++Cnt;
	}

	return Cnt;
}

void Bsearch()
{
	int Result{ 0 };

	int Left{ 1 };
	int Right{ N };

	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };

		LL Cnt{ IsValid(Middle) };

		if (Cnt < D)
		{
			Left = Middle + 1;
		}
		else
		{
			Result = Middle;

			Right = Middle - 1;
		}
	}

	cout << Result;
}

void Solve()
{
	Bsearch();
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