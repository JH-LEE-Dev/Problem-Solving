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

/*
*  문제 분석
*	1. 톱니 바퀴는 맞닿은 부분이 다른 극일 때는 서로 반대 방향으로 회전
*	2. 서로 맞닿은 부분은 0,4번 톱니임.
*
*  문제 해결 전략
*	1. 각 톱니가 회전하는 방향에 따라 인덱스를 옮겨주는 기능을 정의.
*	2. 회전하는 바퀴 좌,우의 바퀴를 맞닿은 톱니의 상태에 따라 회전시킴.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()

int K;
vector<vector<int>> wheels(4, vector<int>(8, 0));
vector<pair<int, int>> orders;

void input()
{
	for (int i{ 0 }; i < 4; ++i)
	{
		string wheel;

		cin >> wheel;

		for (int j{ 0 }; j < 8; ++j)
		{
			wheels[i][j] = wheel[j] - '0';
		}
	}

	cin >> K;

	for (int i{ 0 }; i < K; ++i)
	{
		int idx, dir;

		cin >> idx >> dir;

		orders.push_back({ idx,dir });
	}
}

void rotate(int idx, int dir)
{
	//1을 시계 방향으로.
	if (dir == 1)
	{
		vector<int> rotated(8, 0);

		for (int i{ 0 }; i < 8; ++i)
		{
			rotated[(i + 1) % 8] = wheels[idx][i];
		}

		wheels[idx] = rotated;
	}
	else
	{
		vector<int> rotated(8, 0);

		for (int i{ 7 }; i >= 0; --i)
		{
			rotated[i] = wheels[idx][(i + 1) % 8];
		}

		wheels[idx] = rotated;
	}
}

void solve()
{
	for (int i{ 0 }; i < K; ++i)
	{
		int idx{ orders[i].first - 1 };
		int dir{ orders[i].second };

		vector<int> curRotated(4, 0);
		vector<vector<int>> curState = wheels;

		curRotated[idx] = dir;

		rotate(idx, dir);

		for (int i{ idx }; i < 4; ++i)
		{
			if (curRotated[i] != 0)
				continue;

			if (curRotated[i - 1] != 0)
			{
				int additionalDir{ curRotated[i - 1] };

				if (curState[i - 1][2] != curState[i][6])
				{
					curRotated[i] = -additionalDir;
					rotate(i, -additionalDir);
				}
				else
					break;
			}
		}

		for (int i{ idx }; i >= 0; --i)
		{
			if (curRotated[i] != 0)
				continue;

			if (curRotated[i + 1] != 0)
			{
				int additionalDir{ curRotated[i + 1] };

				if (curState[i + 1][6] != curState[i][2])
				{
					curRotated[i] = -additionalDir;
					rotate(i, -additionalDir);
				}
				else
					break;
			}
		}
	}

	int result{ 0 };

	for (int i{ 0 }; i < 4; ++i)
	{
		int score{ (int)pow(2,i) };

		if (wheels[i][0] == 0)
			score = 0;

		result += score;
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