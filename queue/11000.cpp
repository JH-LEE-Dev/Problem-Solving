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
#define MAX 200'001

int N;
vector<pair<int, int>> Times;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int Src, Dst;
		cin >> Src >> Dst;

		Times.push_back({ Src,Dst });
	}
}

void Solve()
{
	sort(Times.begin(), Times.end());

	priority_queue<int, vector<int>, greater<int>> EndTimes;
	EndTimes.push({ Times[0].second });

	for (int i{ 1 }; i < N; ++i)
	{
		if (Times[i].first >= EndTimes.top())
		{
			EndTimes.pop();
			EndTimes.push(Times[i].second);
		}
		else
		{
			EndTimes.push(Times[i].second);
		}
	}

	cout << EndTimes.size();
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