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
#define MAX 51

enum DIR { NOR, EA, SO, WE, NONE };
DIR initDir{ NOR };

int N{ 0 }, M{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
pair<int, int> start;

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };
int result{ 0 };

bool isValid(int row, int col)
{
	if (row >= N || row < 0 || col >= M || col < 0)
		return false;
	else
		return true;
}

bool isUnCleaned(int row, int col)
{
	for (int i{ 0 }; i < 4; ++i)
	{
		auto nR{ row + dir_row[i] };
		auto nC{ col + dir_col[i] };

		if (isValid(nR, nC) == false || table[nR][nC] == 1 || table[nR][nC] == 2)
			continue;

		return true;
	}

	return false;
}

void input()
{
	int dir{ 0 };

	cin >> N >> M;
	cin >> start.first >> start.second >> dir;

	initDir = (DIR)dir;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];
		}
	}
}

void solve()
{
	auto cur_row{ start.first };
	auto cur_col{ start.second };
	auto dir{ initDir };

	if (table[cur_row][cur_col] == 0)
	{
		table[cur_row][cur_col] = 2;
		++result;
	}

	while (true)
	{
		if (isUnCleaned(cur_row, cur_col) == false)
		{
			auto nR{ cur_row };
			auto nC{ cur_col };

			switch (dir)
			{
			case 0:
				nR += 1;
				break;
			case 1:
				nC -= 1;
				break;
			case 2:
				nR -= 1;
				break;
			case 3:
				nC += 1;
				break;
			}

			if (isValid(nR, nC) == false || table[nR][nC] == 1)
			{
				cout << result;
				return;
			}

			cur_row = nR;
			cur_col = nC;
		}
		else
		{
			while (true)
			{
				auto nR{ cur_row };
				auto nC{ cur_col };

				//dir의 범위가 0~3이고 90도 반 시계 회전하면 1을 빼주면 된다. 
				//그래서 음수인 경우를 해결하기 위해 (dir - 1 + 4) % 4를 한다.
				dir = DIR(((int)(dir)+3) % 4);

				switch (dir)
				{
				case 0:
					nR -= 1;
					break;
				case 1:
					nC += 1;
					break;
				case 2:
					nR += 1;
					break;
				case 3:
					nC -= 1;
					break;
				}

				if (isValid(nR, nC) == false || table[nR][nC] == 1)
				{
					continue;
				}

				if (table[nR][nC] == 0)
				{
					table[nR][nC] = 2;

					cur_row = nR;
					cur_col = nC;

					++result;

					break;
				}
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