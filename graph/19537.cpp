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
#include <string.h>

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

struct AI
{
	int mp{ 0 };
	int team{ 0 };
	int row{ 0 };
	int col{ 0 };
};

struct ORDER
{
	int num{ 0 };
	int row{ 0 };
	int col{ 0 };
};

using vertex = tuple<int, int, int>;

#define MAX 501
int N, H, W, M, K;
int occupied[MAX][MAX][2];
int occupied_range[MAX][MAX][2];
int table[MAX][MAX];
int dist[MAX][MAX];
int types[10];
AI units[MAX * MAX / 4];

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

bool isValid(int r, int c)
{
	if (r >= H || r < 0 || c >= W || c < 0)
		return false;
	else
		return true;
}

void dijkstra(int num, int row, int col, int curTeam)
{
	//memset(dist, 0x3f3f3f3f, sizeof(dist));

	for (int i = units[num].row - 20; i <= units[num].row + 20; ++i)
	{
		for (int j = units[num].col - 20; j <= units[num].col + 20; ++j)
		{
			if (isValid(i, j))
				dist[i][j] = INF;
		}
	}

	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;

	pq.push({ 0,units[num].row,units[num].col });
	dist[units[num].row][units[num].col] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto curDist{ get<0>(cur) };
		auto curRow{ get<1>(cur) };
		auto curCol{ get<2>(cur) };

		if (dist[curRow][curCol] < curDist)
			continue;

		if (curRow == row && curCol == col)
		{
			for (int i{ 0 }; i < 4; ++i)
			{
				auto newRow{ units[num].row + dir_row[i] };
				auto newCol{ units[num].col + dir_col[i] };

				if (isValid(newRow, newCol))
					--occupied_range[newRow][newCol][curTeam];
			}

			--occupied[units[num].row][units[num].col][curTeam];

			++occupied[row][col][curTeam];
			units[num].row = row;
			units[num].col = col;

			for (int i{ 0 }; i < 4; ++i)
			{
				auto newRow{ row + dir_row[i] };
				auto newCol{ col + dir_col[i] };

				if (isValid(newRow, newCol))
					++occupied_range[newRow][newCol][curTeam];
			}

			break;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto newRow{ curRow + dir_row[i] };
			auto newCol{ curCol + dir_col[i] };

			if (isValid(newRow, newCol) == false || types[table[newRow][newCol]] == -1)
				continue;

			if (occupied_range[newRow][newCol][1 - curTeam] != -1)
			{
				if (newRow != row || newCol != col)
				{
					continue;
				}
			}

			if (occupied[newRow][newCol][1 - curTeam] != -1)
			{
				continue;
			}

			auto newDist{ curDist + types[table[newRow][newCol]] };

			if (newDist > units[num].mp)
				continue;

			if (dist[newRow][newCol] > newDist)
			{
				dist[newRow][newCol] = newDist;
				pq.push({ newDist,newRow,newCol });
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(table, -1, sizeof(table));
	memset(occupied, -1, sizeof(occupied));
	memset(occupied_range, -1, sizeof(occupied_range));

	cin >> N >> H >> W;

	for (int i{ 0 }; i < H; ++i)
	{
		for (int j{ 0 }; j < W; ++j)
		{
			cin >> table[i][j];
			--table[i][j];
		}
	}

	for (int i{ 0 }; i < N; ++i)
	{
		int input;
		cin >> input;

		types[i] = input;
	}

	cin >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		AI temp;
		cin >> temp.mp >> temp.team >> temp.row >> temp.col;

		++occupied[temp.row][temp.col][temp.team];

		for (int i{ 0 }; i < 4; ++i)
		{
			auto newRow{ temp.row + dir_row[i] };
			auto newCol{ temp.col + dir_col[i] };

			if (isValid(newRow, newCol))
				++occupied_range[newRow][newCol][temp.team];
		}

		units[i] = temp;
	}

	cin >> K;

	for (int i{ 0 }; i < K; ++i)
	{
		ORDER temp;
		cin >> temp.num >> temp.row >> temp.col;

		if (occupied[temp.row][temp.col][1] != -1 || occupied[temp.row][temp.col][0] != -1 || types[table[temp.row][temp.col]] == -1)
			continue;

		dijkstra(temp.num - 1, temp.row, temp.col, units[temp.num - 1].team);
	}

	for (int i{ 0 }; i < M; ++i)
	{
		cout << units[i].row << ' ' << units[i].col << endl;
	}

	return 0;
}