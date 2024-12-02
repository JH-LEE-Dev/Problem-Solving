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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

vector<int> bitmasking((10'000'001 / 32), 0);
int result{ 0 };
int N{ 0 };

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int input;
		cin >> input;

		int idx = input / 32;
		int val = 1 << (input % 32);

		if (!(bitmasking[idx] & val))
		{
			bitmasking[idx] += val;
		}
		else
		{
			result = input;
		}
	}

	cout << result;

	return 0;
}