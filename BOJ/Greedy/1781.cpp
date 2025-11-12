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

int n;
vector<pair<int, int>> problems;

void Input()
{
	cin >> n;

	for (int i{ 0 }; i < n; ++i)
	{
		int t, cnt;
		cin >> t >> cnt;

		problems.push_back({ t,-cnt });
	}
}

void Solve()
{
	int result{ 0 };

	sort(problems.begin(), problems.end());

	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i{ 0 }; i < n; ++i)
	{
		//pq.size는 현재까지 소비한 시간이다.
		if (problems[i].first <= pq.size())
		{
			if (pq.top() < -problems[i].second)
			{
				pq.pop();
				pq.push(-problems[i].second);
			}
		}
		else
			pq.push(-problems[i].second);
	}

	while (pq.empty() == false)
	{
		result += pq.top();
		pq.pop();
	}

	cout << result;
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