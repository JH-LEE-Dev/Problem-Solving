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

#define MAX 45
#define STICKER_COUNT 105
#define STICKER_SIZE 10

int N{ 0 }, M{ 0 }, K{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<vector<vector<int>>> stickers;

void rotation(vector<vector<int>>& sticker, int& newRow, int& newCol)
{
	int row = sticker.size();
	int col = sticker[0].size();

	newRow = col;
	newCol = row;

	vector<vector<int>> rotated(newRow, vector<int>(newCol, 0));

	for (int i{ 0 }; i < row; ++i)
	{
		for (int j{ 0 }; j < col; ++j)
		{
			rotated[j][row - 1 - i] = sticker[i][j];
		}
	}

	sticker = rotated;
}

bool fit(vector<vector<int>>& _table, vector<vector<int>>& _sticker, int row, int col)
{
	if (row + _sticker.size() > N || col + _sticker[0].size() > M)
	{
		return false;
	}

	for (int i{ row }; i < row + _sticker.size(); ++i)
	{
		for (int j{ col }; j < col + _sticker[0].size(); ++j)
		{
			if (_table[i][j] == 1 && _sticker[i - row][j - col] == 1)
				return false;
		}
	}

	return true;
}

void apply(vector<vector<int>>& _table, vector<vector<int>>& _sticker, int row, int col)
{
	for (int i{ row }; i < row + _sticker.size(); ++i)
	{
		for (int j{ col }; j < col + _sticker[0].size(); ++j)
		{
			if (_sticker[i - row][j - col] == 1)
				_table[i][j] = 1;
		}
	}
}

void func()
{
	vector<vector<int>> tempTable = table;

	for (int i{ 0 }; i < stickers.size(); ++i)
	{
		vector<vector<int>> sticker{ stickers[i] };
		int row = sticker.size();
		int col = sticker[0].size();
		bool applied{ false };

		if (row > N || col > M)
			rotation(sticker, row, col);

		int sizeRow{ row };
		int sizeCol{ col };

		int rowCursor{ 0 };
		int colCursor{ 0 };

		vector<vector<int>> tempSticker = sticker;
		int rotationCount{ 0 };

		while (rotationCount <= 3)
		{
			while (rowCursor < N)
			{
				colCursor = 0;
				while (colCursor < M)
				{
					if (fit(tempTable, tempSticker, rowCursor, colCursor))
					{
						apply(tempTable, tempSticker, rowCursor, colCursor);
						applied = true;
						break;
					}
					else
					{
						++colCursor;
					}
				}

				if (applied)
					break;

				++rowCursor;
			}

			if (applied)
				break;

			rowCursor = 0;
			colCursor = 0;

			++rotationCount;
			rotation(tempSticker, row, col);

			if (rowCursor + row > N || colCursor + col > M)
				rotation(tempSticker, row, col);
		}
	}

	int result{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (tempTable[i][j] == 1)
				++result;
		}
	}

	cout << result;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M >> K;

	int R{ 0 }, C{ 0 };
	for (int i{ 0 }; i < K; ++i)
	{
		cin >> R >> C;

		vector<vector<int>> temp(R, vector<int>(C, 0));
		for (int j{ 0 }; j < R; ++j)
		{
			for (int k{ 0 }; k < C; ++k)
			{
				cin >> temp[j][k];
			}
		}

		stickers.push_back(temp);
	}

	func();

	return 0;
}