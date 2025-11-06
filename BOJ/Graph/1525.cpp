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

vector<vector<int>> table(3, vector<int>(3, 0));
set<int> visited;

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

bool IsValid(int r, int c)
{
	if (r >= 3 || r < 0 || c >= 3 || c < 0)
		return false;
	else
		return true;
}

int ToInt(vector<vector<int>>& _table)
{
	int ret{ 0 };

	for (int i{ 0 }; i < 3; ++i)
	{
		for (int j{ 0 }; j < 3; ++j)
		{
			ret += (_table[i][j] * pow(10, i * 3 + j));
		}
	}

	return ret;
}

pair<int, int> FindEmpty(int state)
{
	int div{ 10 };
	int r{ 0 };
	int c{ 0 };

	for (int i{ 0 }; i < 9; ++i)
	{
		int cur{ state % div };

		r = i / 3;
		c = i % 3;

		if (cur == 0)
		{
			return { r,c };
		}

		state /= div;
	}

	return { -1,-1 };
}

int Swap(int state, pair<int, int> src, pair<int, int> dst)
{
	auto srcDigit{ src.first * 3 + src.second };
	auto dstDigit{ dst.first * 3 + dst.second };

	string str_state{ to_string(state) };

	if (str_state.length() < 9)
	{
		string newStr = "0";
		str_state = newStr + str_state;
	}

	swap(*(--str_state.end() - srcDigit), *(--str_state.end() - dstDigit));

	return stoi(str_state);
}

void Input()
{
	for (int i{ 0 }; i < 3; ++i)
	{
		for (int j{ 0 }; j < 3; ++j)
		{
			cin >> table[i][j];
		}
	}
}

void Bfs()
{
	visited.insert(ToInt(table));
	queue<pair<int, int>> q;
	q.push({ 0,ToInt(table) });

	while (q.empty() == false)
	{
		auto [dist, state] {q.front()};
		q.pop();

		if (state == 87654321)
		{
			cout << dist;
			return;
		}

		pair<int, int> emptyCoord{ FindEmpty(state) };

		for (int i{ 0 }; i < 4; ++i)
		{
			auto r{ emptyCoord.first + dir_row[i] };
			auto c{ emptyCoord.second + dir_col[i] };

			if (IsValid(r, c) == false)
				continue;

			int newState{ Swap(state,emptyCoord,{r,c}) };

			if (visited.find(newState) == visited.end())
			{
				q.push({ dist + 1,newState });
				visited.insert(newState);
			}
		}
	}

	cout << -1;
}

void Solve()
{
	Bfs();
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}