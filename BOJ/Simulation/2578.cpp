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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

vector<vector<int>> arr(6, vector<int>(6, 0));
vector<vector<bool>> check(6, vector<bool>(6, false));

vector<bool> vertical(6, false);
vector<bool> parellel(6, false);
vector<bool> diagonal(2, false);
int counting{ 0 };

void bingo(int row, int col)
{
	bool rowCheck{ true };
	bool colCheck{ true };
	bool diagonalCheckLeft{ true };
	bool diagonalCheckRight{ true };

	for (int i{ 0 }; i < 5; ++i)
	{
		if (check[row][i] != true)
		{
			rowCheck = false;
			break;
		}
	}

	for (int i{ 0 }; i < 5; ++i)
	{
		if (check[i][col] != true)
		{
			colCheck = false;
			break;
		}
	}

	if (rowCheck == true)
	{
		if (parellel[row] == false)
		{
			++counting;
			parellel[row] = true;
		}
	}

	if (colCheck == true)
	{
		if (vertical[col] == false)
		{
			++counting;
			vertical[col] = true;
		}
	}

	if (diagonal[0] == false)
	{
		for (int i{ 0 }; i < 5; ++i)
		{
			if (check[i][i] != true)
			{
				diagonalCheckRight = false;
				break;
			}
		}

		if (diagonalCheckRight == true)
		{
			if (diagonal[0] == false)
			{
				++counting;
				diagonal[0] = true;
			}
		}
	}

	if (diagonal[1] == false)
	{
		for (int i{ 0 }; i < 5; ++i)
		{
			if (check[i][4 - i] != true)
			{
				diagonalCheckLeft = false;
				break;
			}
		}

		if (diagonalCheckLeft == true)
		{
			if (diagonal[1] == false)
			{
				++counting;
				diagonal[1] = true;
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int result{ 0 }, calling{ 0 };

	for (int i{ 0 }; i < 5; ++i)
	{
		for (int j{ 0 }; j < 5; ++j)
		{
			cin >> arr[i][j];
		}
	}

	for (int i{ 0 }; i < 5; ++i)
	{
		for (int j{ 0 }; j < 5; ++j)
		{
			int input{ 0 };
			cin >> input;
			++calling;
			for (int row{ 0 }; row < 5; ++row)
			{
				for (int col{ 0 }; col < 5; ++col)
				{
					if (input == arr[row][col])
					{
						check[row][col] = true;

						bingo(row, col);

						if (counting >= 3)
						{
							if (result == 0)
							{
								result = calling;
							}
						}

						break;
					}
				}
			}
		}
	}

	cout << result;

	return 0;
}