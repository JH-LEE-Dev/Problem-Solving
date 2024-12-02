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

vector<int> bitmasking(((1 << 25) / 32), 0);

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int input;

	while (true)
	{
		cin >> input;

		if (cin.eof())
			break;

		int idx = input / 32;
		int val = 1 << (input % 32);

		if (!(bitmasking[idx] & val))
		{
			bitmasking[idx] += val;
			cout << input << " ";
		}
	}

	return 0;
}