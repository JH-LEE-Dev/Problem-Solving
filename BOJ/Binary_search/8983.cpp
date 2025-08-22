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

vector<pair<int, int>> animal;
vector<int> gun;

int M, N, L;

int getDist(int x, int y, int gun)
{
	return abs(gun - x) + y;
}

void input()
{
	cin >> M >> N >> L;

	for (int i{ 0 }; i < M; ++i)
	{
		int temp;
		cin >> temp;

		gun.push_back(temp);
	}

	for (int i{ 0 }; i < N; ++i)
	{
		int x, y;
		cin >> x >> y;

		animal.push_back({ x,y });
	}
}

bool bSearch(pair<int, int> target)
{
	int x{ target.first };
	int y{ target.second };

	int left{ 0 };
	int right{ M - 1 };

	while (left <= right)
	{
		int mid{ (left + right) / 2 };
		int midNum{ gun[mid] };

		int dist{ getDist(x,y,midNum) };

		if (dist > L)
		{
			if (x < midNum)
			{
				right = mid - 1;
			}
			else if (x > midNum)
			{
				left = mid + 1;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}

	return false;
}

void solve()
{
	sort(gun.begin(), gun.end());
	int ret{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		auto result{ bSearch(animal[i]) };

		if (result)
			++ret;
	}

	cout << ret;
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