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

int T, N, K;
vector<int> Arr;
int Delta{ INF };
int Cnt{ 0 };

void Input()
{
	Arr.clear();

	cin >> N >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);
	}
}

void Bsearch(int Start, int Val)
{
	int Left{ Start };
	int Right{ N - 1 };

	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };

		if (Arr[Middle] + Val < K)
		{
			Left = Middle + 1;
		}
		else
		{
			Right = Middle - 1;
		}

		if (abs(K - (Arr[Middle] + Val)) == Delta)
		{
			++Cnt;
		}
		else if (abs(K - (Arr[Middle] + Val)) < Delta)
		{
			Cnt = 1;
			Delta = abs(K - (Arr[Middle] + Val));
		}
	}
}

void Solve()
{
	cin >> T;

	for (int i{ 0 }; i < T; ++i)
	{
		Input();

		Delta = INF;
		Cnt = 0;

		sort(Arr.begin(), Arr.end());

		for (int j{ 0 }; j < N - 1; ++j)
		{
			Bsearch(j + 1, Arr[j]);
		}

		cout << Cnt << endl;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}