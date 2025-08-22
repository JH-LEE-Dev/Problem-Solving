#include <iostream>
#include <vector>
#include <limits>

#define endl '\n'
using namespace std;

vector<vector<int>> table(10, vector<int>(10, 0));

int N{ 0 }, M{ 0 }, result{ numeric_limits<int>::max() };

enum DIR { LEFT = -1, DOWN = 0, RIGHT = 1, DEFAULT = 3 };

int function(int row, int column, int value, int dir)
{
	if (row >= N || column >= M)
		return value;

	int minValue{ numeric_limits<int>::max() };

	if (dir != LEFT && column - 1 >= 0)
	{
		value += table[row + 1][column - 1];
		minValue = min(function(row + 1, column - 1, value, LEFT), minValue);
		value -= table[row + 1][column - 1];
	}

	if (dir != DOWN)
	{
		value += table[row + 1][column];
		minValue = min(function(row + 1, column, value, DOWN), minValue);
		value -= table[row + 1][column];
	}

	if (dir != RIGHT && column + 1 < M)
	{
		value += table[row + 1][column + 1];
		minValue = min(function(row + 1, column + 1, value, RIGHT), minValue);
		value -= table[row + 1][column + 1];
	}

	return minValue;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];
		}
	}

	for (int i{ 0 }; i < M; ++i)
	{
		result = min(function(0, i, table[0][i], DEFAULT), result);
	}

	cout << result;

	return 0;
}