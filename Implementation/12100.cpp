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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 25

int N{ 0 }, result{ -1 };
vector<vector<int>> table(MAX, vector<int>(MAX, 0));

enum DIR { UP, DOWN, LEFT, RIGHT };

int pushing(DIR dir, vector<vector<int>>& _table)
{
	int maxValue{ -1 };

	vector<vector<bool>> merged(N, vector<bool>(N, false));

	switch (dir)
	{
	case UP:
		for (int row{ 1 }; row < N; ++row)
		{
			for (int col{ 0 }; col < N; ++col)
			{
				auto rowCursor = row;
				auto colCursor = col;

				maxValue = max(maxValue, _table[row][col]);

				while (rowCursor > 0)
				{
					if (_table[rowCursor][colCursor] != 0 && _table[rowCursor][colCursor] == _table[rowCursor - 1][colCursor] && merged[rowCursor - 1][colCursor] == false)
					{
						_table[rowCursor - 1][colCursor] = _table[rowCursor][colCursor] * 2;
						_table[rowCursor][colCursor] = 0;
						merged[rowCursor - 1][colCursor] = true;

						maxValue = max(maxValue, _table[rowCursor - 1][colCursor]);

						break;
					}
					else
					{
						if (_table[rowCursor - 1][colCursor] == 0)
						{
							_table[rowCursor - 1][colCursor] = _table[rowCursor][colCursor];
							_table[rowCursor][colCursor] = 0;
						}
						else
						{
							break;
						}
					}
					--rowCursor;
				}
			}
		}
		break;
	case DOWN:
		for (int row{ N - 2 }; row >= 0; --row)
		{
			for (int col{ 0 }; col < N; ++col)
			{
				auto rowCursor = row;
				auto colCursor = col;

				maxValue = max(maxValue, _table[row][col]);

				while (rowCursor < N - 1)
				{
					if (_table[rowCursor][colCursor] != 0 && _table[rowCursor][colCursor] == _table[rowCursor + 1][colCursor] && merged[rowCursor + 1][colCursor] == false)
					{
						_table[rowCursor + 1][colCursor] = _table[rowCursor][colCursor] * 2;
						_table[rowCursor][colCursor] = 0;
						merged[rowCursor + 1][colCursor] = true;

						maxValue = max(maxValue, _table[rowCursor + 1][colCursor]);

						break;
					}
					else
					{
						if (_table[rowCursor + 1][colCursor] == 0)
						{
							_table[rowCursor + 1][colCursor] = _table[rowCursor][colCursor];
							_table[rowCursor][colCursor] = 0;
						}
						else
						{
							break;
						}
					}
					++rowCursor;
				}
			}
		}
		break;
	case LEFT:
		for (int row{ 0 }; row < N; ++row)
		{
			for (int col{ 0 }; col < N; ++col)
			{
				auto rowCursor = row;
				auto colCursor = col;

				maxValue = max(maxValue, _table[row][col]);

				while (colCursor > 0)
				{
					if (_table[rowCursor][colCursor] != 0 && _table[rowCursor][colCursor] == _table[rowCursor][colCursor - 1] && merged[rowCursor][colCursor - 1] == false)
					{
						_table[rowCursor][colCursor - 1] = _table[rowCursor][colCursor] * 2;
						_table[rowCursor][colCursor] = 0;
						merged[rowCursor][colCursor - 1] = true;

						maxValue = max(maxValue, _table[rowCursor][colCursor - 1]);

						break;
					}
					else
					{
						if (_table[rowCursor][colCursor - 1] == 0)
						{
							_table[rowCursor][colCursor - 1] = _table[rowCursor][colCursor];
							_table[rowCursor][colCursor] = 0;
						}
						else
						{
							break;
						}
					}
					--colCursor;
				}
			}
		}
		break;
	case RIGHT:
		for (int row{ 0 }; row < N; ++row)
		{
			for (int col{ N - 2 }; col >= 0; --col)
			{
				auto rowCursor = row;
				auto colCursor = col;

				maxValue = max(maxValue, _table[row][col]);

				while (colCursor < N - 1)
				{
					if (_table[rowCursor][colCursor] != 0 && _table[rowCursor][colCursor] == _table[rowCursor][colCursor + 1] && merged[rowCursor][colCursor + 1] == false)
					{
						_table[rowCursor][colCursor + 1] = _table[rowCursor][colCursor] * 2;
						_table[rowCursor][colCursor] = 0;
						merged[rowCursor][colCursor + 1] = true;

						maxValue = max(maxValue, _table[rowCursor][colCursor + 1]);

						break;
					}
					else
					{
						if (_table[rowCursor][colCursor + 1] == 0)
						{
							_table[rowCursor][colCursor + 1] = _table[rowCursor][colCursor];
							_table[rowCursor][colCursor] = 0;
						}
						else
						{
							break;
						}
					}
					++colCursor;
				}
			}
		}
		break;
	}

	return maxValue;
}

void func(int pushCount, vector<vector<int>>& _table)
{
	if (pushCount > 4)
		return;

	for (int i{ 0 }; i < 4; ++i)
	{
		vector<vector<int>> tempTable = _table;
		result = max(result, pushing((DIR)i, tempTable));
		func(pushCount + 1, tempTable);
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> table[i][j];
		}
	}

	func(0, table);

	cout << result;

	return 0;
}