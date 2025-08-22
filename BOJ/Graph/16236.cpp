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
#define MAX 21
int N{ 0 };
vector<vector<int>> table(MAX, vector<int>(MAX, 0));

vector<int> dir_x{ 0,0,1,-1 };
vector<int> dir_y{ 1,-1,0,0 };
int curSize{ 2 };
int eatCnt{ 0 };
int total{ 0 };
pair<int, int> curCoord;

bool bfs()
{
	int x = curCoord.first;
	int y = curCoord.second;

	vector<vector<int>> dist(MAX, vector<int>(MAX, INF));
	dist[curCoord.first][curCoord.second] = 0;

	queue<pair<int, int>> myQ;
	myQ.push({ x,y });

	vector<pair<int, pair<int, int>>> toEat;

	while (myQ.empty() == false)
	{
		auto cur = myQ.front();
		myQ.pop();

		auto curX = cur.first;
		auto curY = cur.second;

		for (int i{ 0 }; i < 4; ++i)
		{
			auto new_x = curX + dir_x[i];
			auto new_y = curY + dir_y[i];

			if (new_x >= N || new_x < 0 || new_y >= N || new_y < 0)
				continue;

			if (dist[new_x][new_y] > dist[curX][curY] + 1 && table[new_x][new_y] <= curSize)
			{
				dist[new_x][new_y] = dist[curX][curY] + 1;

				if (table[new_x][new_y] < curSize && table[new_x][new_y] != 0)
				{
					toEat.push_back({ dist[new_x][new_y],{ new_x,new_y } });
				}

				myQ.push({ new_x,new_y });
			}
		}
	}

	if (toEat.empty())
		return false;

	sort(toEat.begin(), toEat.end());

	auto toEatCoord = toEat[0];

	total += dist[toEatCoord.second.first][toEatCoord.second.second];

	table[curCoord.first][curCoord.second] = 0;
	curCoord = toEatCoord.second;

	table[toEatCoord.second.first][toEatCoord.second.second] = 0;

	++eatCnt;

	if (eatCnt == curSize)
	{
		eatCnt = 0;
		++curSize;
	}

	return true;
}

void func()
{
	while (true)
	{
		if (bfs() == false)
			return;
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

			if (table[i][j] == 9)
				curCoord = { i,j };
		}
	}

	func();

	cout << total;

	return 0;
}