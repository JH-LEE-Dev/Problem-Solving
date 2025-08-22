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

int T, N, M;
vector<int> A;
vector<int> B;

vector<int> cA;
vector<int> cB;

int totalSumA{ 0 };
int totalSumB{ 0 };

void input()
{
	cin >> T;

	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		int temp;
		cin >> temp;

		A.push_back(temp);

		totalSumA += temp;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int temp;
		cin >> temp;

		B.push_back(temp);

		totalSumB += temp;
	}

	cA.push_back(totalSumA);
	cA.push_back(0);
	cB.push_back(totalSumB);
	cB.push_back(0);
}

void cumulativeSum()
{
	for (int i{ 0 }; i < N; ++i)
	{
		int idx{ i };
		int cnt{ 0 };
		int sum{ 0 };

		while (true)
		{
			if (cnt == N - 1)
				break;

			sum += A[idx];
			cA.push_back(sum);
			idx = (idx + 1) % N;
			++cnt;
		}
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int idx{ i };
		int cnt{ 0 };
		int sum{ 0 };

		while (true)
		{
			if (cnt == M - 1)
				break;

			sum += B[idx];
			cB.push_back(sum);
			idx = (idx + 1) % M;
			++cnt;

			if (cnt == M - 1)
				break;
		}
	}
}

int Lower_bSearch(int target)
{
	int left{ 0 };
	int right{ (int)cB.size() - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ cB[middle] };

		if (target > middleNum)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return left;
}

int Upper_bSearch(int target)
{
	int left{ 0 };
	int right{ (int)cB.size() - 1 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };
		int middleNum{ cB[middle] };

		if (target >= middleNum)
			left = middle + 1;
		else
			right = middle - 1;
	}

	return left;
}

void solve()
{
	cumulativeSum();

	sort(cA.begin(), cA.end());
	sort(cB.begin(), cB.end());

	int result{ 0 };

	for (int i{ 0 }; i < cA.size(); ++i)
	{
		int idx_left{ Lower_bSearch(T - cA[i]) };
		int idx_right{ Upper_bSearch(T - cA[i]) };

		if (cB[idx_left] == T - cA[i])
		{
			result += idx_right - idx_left;
		}
	}

	cout << result;
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