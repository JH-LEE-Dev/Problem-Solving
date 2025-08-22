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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 9

int N{ 0 }, M{ 0 };
vector<vector<char>> wall(MAX, vector<char>(MAX, '0'));
vector<pair<int, int>> virus;
vector<pair<int, int>> room;

vector<int> dir_x{ 0,0,1,-1 };
vector<int> dir_y{ 1,-1,0,0 };

int result{ -1 };


void copyTable(vector<vector<char>>& tempTable)
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			tempTable[i][j] = wall[i][j];
		}
	}
}

void bfs()
{
	vector<vector<char>> tempWall(MAX, vector<char>(MAX, '0'));
	copyTable(tempWall);

	queue<pair<int, int>> myQ;

	for (auto& coord : virus)
	{
		myQ.push(coord);
	}

	while (myQ.empty() == false)
	{
		auto cur = myQ.front();
		myQ.pop();

		for (int i{ 0 }; i < 4; ++i)
		{
			auto x_coord = cur.first + dir_x[i];
			auto y_coord = cur.second + dir_y[i];

			if (x_coord >= N || x_coord < 0 || y_coord >= M || y_coord < 0)
				continue;

			if (tempWall[x_coord][y_coord] == '0')
			{
				myQ.push({ x_coord,y_coord });
				tempWall[x_coord][y_coord] = '2';
			}
		}
	}

	int total{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (tempWall[i][j] == '0')
			{
				++total;
			}
		}
	}

	result = max(result, total);
}

void setWall()
{
	int roomSize{ (int)room.size() };

	for (int i = 0; i < roomSize; ++i)
	{
		for (int j = i + 1; j < roomSize; ++j)
		{
			for (int k = j + 1; k < roomSize; ++k)
			{
				auto coord_1 = room[i];
				auto coord_2 = room[j];
				auto coord_3 = room[k];

				wall[coord_1.first][coord_1.second] = '1';
				wall[coord_2.first][coord_2.second] = '1';
				wall[coord_3.first][coord_3.second] = '1';

				bfs();

				wall[coord_1.first][coord_1.second] = '0';
				wall[coord_2.first][coord_2.second] = '0';
				wall[coord_3.first][coord_3.second] = '0';
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
			cin >> wall[i][j];

			if (wall[i][j] == '2')
				virus.push_back({ i,j });

			if (wall[i][j] == '0')
				room.push_back({ i,j });
		}
	}

	setWall();

	cout << result;

	return 0;
}