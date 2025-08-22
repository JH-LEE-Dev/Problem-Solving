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
#define MAX 1'001

int R, C;
vector<vector<char>> Table(MAX, vector<char>(MAX));
set<string> CharSet;

int Result{ 0 };

void Input()
{
	cin >> R >> C;

	for (int i{ 0 }; i < R; ++i)
	{
		for (int j{ 0 }; j < C; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

void Bsearch()
{
	int Left{ 0 };
	int Right{ R - 1 };

	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };

		bool IsValid{ true };

		for (int i{ 0 }; i < C; ++i)
		{
			string Str;

			for (int j{ Middle }; j < R; ++j)
			{
				Str += Table[j][i];
			}

			if (CharSet.find(Str) != CharSet.end())
			{
				IsValid = false;
				break;
			}
			else
				CharSet.insert(Str);
		}

		if (IsValid)
		{
			Left = Middle + 1;
			Result = max(Result, Middle);
		}
		else
			Right = Middle - 1;
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