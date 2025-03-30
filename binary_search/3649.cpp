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
using ll = long long;

#define endl '\n'
#define INF numeric_limits<int>::max()


int X;
int N;

vector<int> lego;
int delta{ -1 };

pair<int, int> result;
bool done{ false };
bool isValid{ false };

void input()
{
	lego.clear();
	delta = -1;
	result = pair<int, int>(-1, -1);
	isValid = false;

	string x;
	getline(cin, x);

	if (x.length() == 0)
	{
		done = true;
		return;
	}

	X = stoi(x);

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		ll temp;
		cin >> temp;

		lego.push_back(temp);
	}
}

int lowerBound(int left, int len)
{
	int right{ (int)lego.size() - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ lego[middle] };

		if (middleNum < len)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return left;
}

void solve()
{
	sort(lego.begin(), lego.end());

	for (int i{ 0 }; i < N - 1; ++i)
	{
		auto idx{ lowerBound(i + 1, X * 10'000'000 - lego[i]) };

		if (idx < 0 || idx >= lego.size())
			continue;

		if (lego[i] + lego[idx] == X * 10'000'000)
		{
			isValid = true;

			auto curDelta{ abs(lego[i] - lego[idx]) };

			if (delta < curDelta)
			{
				result = make_pair(i, idx);
				delta = curDelta;
			}
		}
	}

	if (isValid)
	{
		cout << "yes " << lego[result.first] << ' ' << lego[result.second] << endl;
	}
	else
	{
		cout << "danger" << endl;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (true)
	{
		input();

		if (done == true)
			break;

		solve();

		cin.ignore();
	}

	return 0;
}