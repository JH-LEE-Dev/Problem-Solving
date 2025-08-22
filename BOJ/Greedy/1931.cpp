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

vector<pair<int, int>> jobs;
int N{ 0 };

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		pair<int, int> job;
		cin >> job.second >> job.first;

		jobs.push_back(job);
	}
}

void solve()
{
	sort(jobs.begin(), jobs.end());

	int result{ 1 };
	int endTime{ jobs[0].first };

	for (int i{ 1 }; i < N; ++i)
	{
		if (jobs[i].second >= endTime)
		{
			++result;
			endTime = jobs[i].first;
		}
	}

	cout << result;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}