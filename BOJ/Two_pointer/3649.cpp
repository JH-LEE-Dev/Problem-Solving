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

int X, N;
vector<int> lego;

bool done{ false };
int delta{ -1 };
pair<int, int> result;
bool isValid{ false };

void input()
{
	done = false;
	lego.clear();
	result = make_pair(-1, -1);
	delta = -1;
	isValid = false;

	string x;

	cin >> x;

	if (x.length() == 0)
	{
		done = true;
		return;
	}

	X = stoi(x);

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;
		cin >> temp;

		lego.push_back(temp);
	}
}

void solve()
{
	sort(lego.begin(), lego.end());

	int left{ 0 };
	int right{ (int)lego.size() - 1 };

	while (left < right)
	{
		int sum{ lego[left] + lego[right] };

		if (sum == X * 10'000'000)
		{
			auto curDelta{ abs(lego[left] - lego[right]) };

			if (curDelta > delta)
			{
				isValid = true;
				delta = curDelta;

				result.first = left;
				result.second = right;
			}

			++left;
			--right;

			continue;
		}

		if (sum < X * 10'000'000)
			++left;
		else
			--right;
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