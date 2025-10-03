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
#define MAX 20

int N;
vector<vector<int>> DP_MAX(MAX, vector<int>(MAX, -INF));
vector<vector<int>> DP_MIN(MAX, vector<int>(MAX, INF));
vector<int> Nums;
vector<char> Ops;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		char Temp;
		cin >> Temp;

		if ((int)Temp >= (int)'0' && (int)Temp <= (int)'9')
		{
			Nums.push_back(Temp - '0');
		}
		else
			Ops.push_back(Temp);
	}
}

void Solve()
{
	for (int Len{ 0 }; Len < Nums.size(); ++Len)
	{
		for (int i{ 0 }; i < Nums.size(); ++i)
		{
			if (i + Len >= Nums.size())
				break;

			if (Len == 0)
			{
				DP_MAX[i][i] = Nums[i];
				DP_MIN[i][i] = Nums[i];

				continue;
			}

			for (int j{ 0 }; j < Len; ++j)
			{
				char Op{ Ops[i + j] };

				if (Op == '+')
				{
					DP_MAX[i][i + Len] = max(DP_MAX[i][i + j] + DP_MAX[i + j + 1][i + Len], DP_MAX[i][i + Len]);
					DP_MIN[i][i + Len] = min(DP_MIN[i][i + j] + DP_MIN[i + j + 1][i + Len], DP_MIN[i][i + Len]);
				}
				else if (Op == '-')
				{
					DP_MAX[i][i + Len] = max(DP_MAX[i][i + j] - DP_MIN[i + j + 1][i + Len], DP_MAX[i][i + Len]);
					DP_MIN[i][i + Len] = min(DP_MIN[i][i + j] - DP_MAX[i + j + 1][i + Len], DP_MIN[i][i + Len]);
				}
				else
				{
					DP_MAX[i][i + Len] = max(DP_MAX[i][i + j] * DP_MAX[i + j + 1][i + Len], DP_MAX[i][i + Len]);
					DP_MAX[i][i + Len] = max(DP_MAX[i][i + j] * DP_MIN[i + j + 1][i + Len], DP_MAX[i][i + Len]);
					DP_MAX[i][i + Len] = max(DP_MIN[i][i + j] * DP_MAX[i + j + 1][i + Len], DP_MAX[i][i + Len]);
					DP_MAX[i][i + Len] = max(DP_MIN[i][i + j] * DP_MIN[i + j + 1][i + Len], DP_MAX[i][i + Len]);

					DP_MIN[i][i + Len] = min(DP_MAX[i][i + j] * DP_MAX[i + j + 1][i + Len], DP_MIN[i][i + Len]);
					DP_MIN[i][i + Len] = min(DP_MAX[i][i + j] * DP_MIN[i + j + 1][i + Len], DP_MIN[i][i + Len]);
					DP_MIN[i][i + Len] = min(DP_MIN[i][i + j] * DP_MAX[i + j + 1][i + Len], DP_MIN[i][i + Len]);
					DP_MIN[i][i + Len] = min(DP_MIN[i][i + j] * DP_MIN[i + j + 1][i + Len], DP_MIN[i][i + Len]);
				}
			}
		}
	}

	cout << DP_MAX[0][Nums.size() - 1];
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