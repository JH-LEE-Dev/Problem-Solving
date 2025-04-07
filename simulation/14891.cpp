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
*  ���� �м�
*	1. ��� ������ �´��� �κ��� �ٸ� ���� ���� ���� �ݴ� �������� ȸ��
*	2. ���� �´��� �κ��� 0,4�� �����.
*
*  ���� �ذ� ����
*	1. �� ��ϰ� ȸ���ϴ� ���⿡ ���� �ε����� �Ű��ִ� ����� ����.
*	2. ȸ���ϴ� ���� ��,���� ������ �´��� ����� ���¿� ���� ȸ����Ŵ.
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
	//1�� �ð� ��������.
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