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
#define MAX 21

enum ROLLING_DIR { EAST = 1, WEST, NORTH, SOUTH };

vector<int> dir_row{ 0,0,-1,1 };
vector<int> dir_col{ 1,-1,0,0 };
//�� �� �� �� �Ʒ� ��
vector<int> dice{ 0,0,0,0,0,0 };
//�ʱ� ����
//3,4,2,5,1,6

//���� ����
// 6,1,2,5,3,4 - ���� �Ѹ� - dir[0]
//3,4,6,1,2,5 - ���� �Ѹ� - dir[2]
//1,6,2,5,4,3 - ���� �Ѹ� - dir[1]
//3,4,1,6,5,2 - ���� �Ѹ� - dir[3]

int N, M, X, Y, K;
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<ROLLING_DIR> query;

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> N >> M >> X >> Y >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];
		}
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int q;
		cin >> q;

		ROLLING_DIR temp{ (ROLLING_DIR)q };
		query.push_back(temp);
	}
}

void solve()
{
	auto r{ X };
	auto c{ Y };

	for (int i{ 0 }; i < K; ++i)
	{
		auto q{ query[i] };

		switch (q)
		{
		case EAST:
		{
			int dir_idx{ 0 };
			int nR{ r + dir_row[dir_idx] };
			int nC{ c + dir_col[dir_idx] };

			if (isValid(nR, nC) == false)
				continue;

			int swapping_1{ dice[0] };
			int swapping_2{ dice[1] };
			int swapping_3{ dice[4] };
			int swapping_4{ dice[5] };

			dice[0] = swapping_4;
			dice[1] = swapping_3;
			dice[4] = swapping_1;
			dice[5] = swapping_2;

			if (table[nR][nC] == 0)
			{
				table[nR][nC] = dice[4];
			}
			else
			{
				dice[4] = table[nR][nC];
				table[nR][nC] = 0;
			}

			cout << dice[5] << endl;

			r = nR;
			c = nC;

			break;
		}
		case WEST:
		{
			int dir_idx{ 1 };
			int nR{ r + dir_row[dir_idx] };
			int nC{ c + dir_col[dir_idx] };

			if (isValid(nR, nC) == false)
				continue;

			int swapping_1{ dice[0] };
			int swapping_2{ dice[1] };
			int swapping_3{ dice[4] };
			int swapping_4{ dice[5] };

			dice[0] = swapping_3;
			dice[1] = swapping_4;
			dice[4] = swapping_2;
			dice[5] = swapping_1;

			if (table[nR][nC] == 0)
			{
				table[nR][nC] = dice[4];
			}
			else
			{
				dice[4] = table[nR][nC];
				table[nR][nC] = 0;
			}

			cout << dice[5] << endl;

			r = nR;
			c = nC;

			break;
		}
		case NORTH:
		{
			int dir_idx{ 2 };
			int nR{ r + dir_row[dir_idx] };
			int nC{ c + dir_col[dir_idx] };

			if (isValid(nR, nC) == false)
				continue;

			int swapping_1{ dice[2] };
			int swapping_2{ dice[3] };
			int swapping_3{ dice[4] };
			int swapping_4{ dice[5] };

			dice[2] = swapping_4;
			dice[3] = swapping_3;
			dice[4] = swapping_1;
			dice[5] = swapping_2;

			if (table[nR][nC] == 0)
			{
				table[nR][nC] = dice[4];
			}
			else
			{
				dice[4] = table[nR][nC];
				table[nR][nC] = 0;
			}

			cout << dice[5] << endl;

			r = nR;
			c = nC;

			break;
		}
		case SOUTH:
		{
			int dir_idx{ 3 };
			int nR{ r + dir_row[dir_idx] };
			int nC{ c + dir_col[dir_idx] };

			if (isValid(nR, nC) == false)
				continue;

			int swapping_1{ dice[2] };
			int swapping_2{ dice[3] };
			int swapping_3{ dice[4] };
			int swapping_4{ dice[5] };

			dice[2] = swapping_3;
			dice[3] = swapping_4;
			dice[4] = swapping_2;
			dice[5] = swapping_1;

			if (table[nR][nC] == 0)
			{
				table[nR][nC] = dice[4];
			}
			else
			{
				dice[4] = table[nR][nC];
				table[nR][nC] = 0;
			}

			cout << dice[5] << endl;

			r = nR;
			c = nC;

			break;
		}
		}
	}
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