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
#define MAX 40'001

int N;
vector<int> result;
vector<int> port;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;
		cin >> temp;

		port.push_back(temp);
	}
}

int binSearch(int target)
{
	int left{ 0 };
	int right{ (int)result.size() - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ result[middle] };

		if (middleNum < target)
		{
			left = middle + 1;
		}
		else
		{
			right = middle - 1;
		}
	}

	return left;
}

void solve()
{
	for (int i{ 0 }; i < N; ++i)
	{
		int idx{ binSearch(port[i]) };

		if (result.size() <= idx)
		{
			result.push_back(port[i]);
		}
		else
		{
			result[idx] = port[i];
		}
	}

	cout << result.size();
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}