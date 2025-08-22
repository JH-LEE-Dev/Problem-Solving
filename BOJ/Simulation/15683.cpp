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

int N{ 0 }, M{ 0 };
enum TYPE { ONE = 1, TWO, THREE, FOUR, FIVE, WALL };
enum DIR { UP, DOWN, LEFT, RIGHT };
vector<string> room(10, "          ");

vector<vector<pair<int, int>>> CCTV(6, vector<pair<int, int>>());
int totalResult{ INF };


void UDLRCover(int row, int col, DIR dir, vector<string>& _room)
{
	switch (dir)
	{
	case UP:
		--row;
		while (row >= 0)
		{
			if (_room[row][col] == '0')
				_room[row][col] = '#';

			if (_room[row][col] == '6')
				break;

			--row;
		}
		break;
	case DOWN:
		++row;
		while (row < N)
		{
			if (_room[row][col] == '0')
				_room[row][col] = '#';

			if (_room[row][col] == '6')
				break;

			++row;
		}
		break;
	case LEFT:
		--col;
		while (col >= 0)
		{
			if (_room[row][col] == '0')
				_room[row][col] = '#';

			if (_room[row][col] == '6')
				break;

			--col;
		}
		break;
	case RIGHT:
		++col;
		while (col < M)
		{
			if (_room[row][col] == '0')
				_room[row][col] = '#';

			if (_room[row][col] == '6')
				break;

			++col;
		}
		break;
	}
}

void fiveCheck()
{
	for (int i{ 0 }; i < CCTV[FIVE].size(); ++i)
	{
		auto type5 = CCTV[FIVE][i];
		auto row = type5.first;
		auto col = type5.second;

		UDLRCover(row, col, UP, room);
		UDLRCover(row, col, DOWN, room);
		UDLRCover(row, col, LEFT, room);
		UDLRCover(row, col, RIGHT, room);
	}
}

void counting(vector<string>& tempRoom)
{
	int result{ 0 };
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < tempRoom[i].size(); ++j)
		{
			if (tempRoom[i][j] == '0')
			{
				++result;
			}
		}
	}

	totalResult = min(totalResult, result);
}

void oneCheck(int idx, vector<string>& _room)
{
	if (idx >= CCTV[ONE].size())
		return;

	for (int i{ 0 }; i < 4; ++i)
	{
		vector<string> tempRoom = _room;

		auto cur = CCTV[ONE][idx];
		auto row = cur.first;
		auto col = cur.second;

		switch (i)
		{
		case 0:
			UDLRCover(row, col, UP, tempRoom);
			break;
		case 1:
			UDLRCover(row, col, DOWN, tempRoom);
			break;
		case 2:
			UDLRCover(row, col, LEFT, tempRoom);
			break;
		case 3:
			UDLRCover(row, col, RIGHT, tempRoom);
			break;
		}

		oneCheck(idx + 1, tempRoom);

		if (idx == CCTV[ONE].size() - 1)
		{
			counting(tempRoom);
		}
	}
}

void twoCheck(int idx, vector<string>& _room)
{
	if (idx >= CCTV[TWO].size())
		return;

	for (int i{ 0 }; i < 2; ++i)
	{

		vector<string> tempRoom = _room;

		auto cur = CCTV[TWO][idx];
		auto row = cur.first;
		auto col = cur.second;

		switch (i)
		{
		case 0:
			UDLRCover(row, col, UP, tempRoom);
			UDLRCover(row, col, DOWN, tempRoom);
			break;
		case 1:
			UDLRCover(row, col, LEFT, tempRoom);
			UDLRCover(row, col, RIGHT, tempRoom);
			break;
		}

		twoCheck(idx + 1, tempRoom);

		if (idx == CCTV[TWO].size() - 1)
		{
			if (CCTV[ONE].size() != 0)
				oneCheck(0, tempRoom);
			else
			{
				counting(tempRoom);
			}
		}
	}
}

void threeCheck(int idx, vector<string>& _room)
{
	if (idx >= CCTV[THREE].size())
		return;

	for (int i{ 0 }; i < 4; ++i)
	{
		vector<string> tempRoom = _room;

		auto cur = CCTV[THREE][idx];
		auto row = cur.first;
		auto col = cur.second;

		switch (i)
		{
		case 0:
			UDLRCover(row, col, UP, tempRoom);
			UDLRCover(row, col, RIGHT, tempRoom);
			break;
		case 1:
			UDLRCover(row, col, RIGHT, tempRoom);
			UDLRCover(row, col, DOWN, tempRoom);
			break;
		case 2:
			UDLRCover(row, col, DOWN, tempRoom);
			UDLRCover(row, col, LEFT, tempRoom);
			break;
		case 3:
			UDLRCover(row, col, LEFT, tempRoom);
			UDLRCover(row, col, UP, tempRoom);
			break;
		}

		threeCheck(idx + 1, tempRoom);

		if (idx == CCTV[THREE].size() - 1)
		{
			if (CCTV[TWO].size() != 0)
				twoCheck(0, tempRoom);
			else
			{
				if (CCTV[ONE].size() != 0)
					oneCheck(0, tempRoom);
				else
				{
					counting(tempRoom);
				}
			}
		}
	}
}

void fourCheck(int idx, vector<string>& _room)
{
	if (idx >= CCTV[FOUR].size())
		return;

	for (int i{ 0 }; i < 4; ++i)
	{
		vector<string> tempRoom = _room;

		auto cur = CCTV[FOUR][idx];
		auto row = cur.first;
		auto col = cur.second;

		switch (i)
		{
		case 0:
			UDLRCover(row, col, UP, tempRoom);
			UDLRCover(row, col, RIGHT, tempRoom);
			UDLRCover(row, col, LEFT, tempRoom);
			break;
		case 1:
			UDLRCover(row, col, RIGHT, tempRoom);
			UDLRCover(row, col, DOWN, tempRoom);
			UDLRCover(row, col, UP, tempRoom);
			break;
		case 2:
			UDLRCover(row, col, DOWN, tempRoom);
			UDLRCover(row, col, LEFT, tempRoom);
			UDLRCover(row, col, RIGHT, tempRoom);
			break;
		case 3:
			UDLRCover(row, col, LEFT, tempRoom);
			UDLRCover(row, col, UP, tempRoom);
			UDLRCover(row, col, DOWN, tempRoom);
			break;
		}

		fourCheck(idx + 1, tempRoom);

		if (idx == CCTV[FOUR].size() - 1)
		{
			if (CCTV[THREE].size() != 0)
				threeCheck(0, tempRoom);
			else
			{
				if (CCTV[TWO].size() != 0)
					twoCheck(0, tempRoom);
				else
				{
					if (CCTV[ONE].size() != 0)
						oneCheck(0, tempRoom);
					else
					{
						counting(tempRoom);
					}
				}
			}
		}
	}
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
			cin >> room[i][j];

			if (room[i][j] != '0' && room[i][j] != '6')
			{
				int idx = room[i][j] - '0';
				CCTV[idx].push_back({ i,j });
			}
		}
	}

	fiveCheck();

	if (CCTV[FOUR].size() != 0)
		fourCheck(0, room);
	else
	{
		if (CCTV[THREE].size() != 0)
			threeCheck(0, room);
		else
		{
			if (CCTV[TWO].size() != 0)
				twoCheck(0, room);
			else
			{
				if (CCTV[ONE].size() != 0)
					oneCheck(0, room);
				else
				{
					counting(room);
				}
			}
		}
	}

	cout << totalResult;

	return 0;
}