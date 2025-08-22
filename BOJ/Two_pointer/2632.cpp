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

void solve()
{
	cumulativeSum();

	sort(cA.begin(), cA.end());
	sort(cB.begin(), cB.end());

	int result{ 0 };

	int left{ 0 };
	int right{ (int)cB.size() - 1 };

	while (left != cA.size() && right != -1)
	{
		if (cA[left] + cB[right] == T)
		{
			int cursorL{ left };
			int cursorR{ right };

			int cntL{ 0 };
			int cntR{ 0 };

			while (cA[cursorL] == cA[left])
			{
				++cursorL;
				++cntL;

				if (cursorL >= cA.size())
					break;
			}

			while (cB[cursorR] == cB[right])
			{
				--cursorR;
				++cntR;

				if (cursorR >= cB.size())
					break;
			}

			result += cntL * cntR;

			left = cursorL;
			right = cursorR;
		}
		else
		{
			if (cA[left] + cB[right] > T)
				--right;
			else
				++left;
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