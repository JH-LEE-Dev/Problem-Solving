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
#define MAX 100'001

int N, K;
vector<int> Arr;
int Max;
int Result;

void Input()
{
	cin >> N >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Max += Temp;
		Arr.push_back(Temp);
	}
}

void Bsearch()
{
	int Left{ 1 };
	int Right{ Max };

	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };

		int Sum{ 0 };
		int Cnt{ 0 };

		for (int i{ 0 }; i < N; ++i)
		{
			Sum += Arr[i];

			if (Sum >= Middle)
			{
				++Cnt;
				Sum = 0;
			}
		}

		if (Cnt >= K)
		{
			Result = max(Middle, Result);
			Left = Middle + 1;
		}
		else
		{
			Right = Middle - 1;
		}
	}
}

void Solve()
{
	Bsearch();

	cout << Result;
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