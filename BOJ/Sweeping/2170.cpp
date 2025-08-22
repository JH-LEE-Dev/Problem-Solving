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
#define MAX 1'000'001

int N;
vector<pair<int, int>> Arr;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int Src, Dst;
		cin >> Src >> Dst;

		Arr.push_back({ Src,Dst });
	}
}

void Solve()
{
	sort(Arr.begin(), Arr.end());

	int Left{ -INF };
	int Right{ -INF };
	int Result{ 0 };

	for (auto& Range : Arr)
	{
		if (Right > Range.first)
		{
			if (Right < Range.second)
			{
				Result += Range.second - Right;
				Right = max(Right, Range.second);
			}
		}
		else
		{
			Result += Range.second - Range.first;
			Left = Range.first;
			Right = Range.second;
		}
	}

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