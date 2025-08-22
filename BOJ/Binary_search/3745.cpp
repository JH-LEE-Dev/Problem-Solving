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

int N;
vector<int> arr;

void input()
{
	arr.clear();

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;
		cin >> temp;

		arr.push_back(temp);
	}
}

void solve()
{
	while (true)
	{
		if (cin >> N)
		{
			input();

			vector<int> result;

			for (int i{ 0 }; i < N; ++i)
			{
				auto it{ lower_bound(result.begin(),result.end(),arr[i]) };

				if (it == result.end())
					result.push_back(arr[i]);
				else
					*it = arr[i];
			}

			cout << result.size() << endl;

			cin.ignore();
		}
		else
			break;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}