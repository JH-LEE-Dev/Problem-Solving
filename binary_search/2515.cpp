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
#define MAX 300'001

int N, S;
vector<pair<int, int>> portraits;

vector<int> DP(MAX, 0);

void input()
{
	cin >> N >> S;

	for (int i{ 0 }; i < N; ++i)
	{
		int h, p;
		cin >> h >> p;

		portraits.push_back({ h,p });
	}
}

int upperBound(int target, int limit)
{
	int left{ 0 };
	int right{ limit };

	while (left <= right)
	{
		int middleIdx{ (left + right) / 2 };
		int num{ portraits[middleIdx].first };

		if (target >= num)
			left = middleIdx + 1;
		else
			right = middleIdx - 1;
	}

	if (left >= N)
		return 0;
	else
		return left + 1;
}

void solve()
{
	sort(portraits.begin(), portraits.end());

	//DP[0]을 기저로 사용하기 위해 i를 1부터 하고 그림 인덱스는 i-1로 설정.
	for (int i{ 1 }; i <= N; ++i)
	{
		int idx{ upperBound(portraits[i - 1].first - S,i - 1) };

		if (idx != 0 && portraits[idx - 1].first > portraits[i - 1].first - S)
		{
			--idx;
		}

		DP[i] = max(DP[i - 1], DP[idx] + portraits[i - 1].second);
	}

	cout << DP[N];
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