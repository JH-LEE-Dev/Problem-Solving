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
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 201

int N, M;
pair<int, int> start;
pair<int, int> goal;
vector<vector<char>> table(MAX, vector<char>(MAX));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(MAX, INF)));

vector<set<tuple<int, int, int>>> row_object(MAX, set<tuple<int, int, int>>());
vector<set<tuple<int, int, int>>> col_object(MAX, set<tuple<int, int, int>>());

//��,��,��,��
vector<int> dir_row{ 0,-1,0,1 };
vector<int> dir_col{ 1,0,-1,0 };

int result{ -1 };

void input()
{
	cin >> N >> M;

	cin >> start.first >> start.second;
	cin >> goal.first >> goal.second;

	start.first -= 1;
	start.second -= 1;
	goal.first -= 1;
	goal.second -= 1;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];

			if (table[i][j] != '.')
			{
				//���� ������ ��� object set�� �����Ѵ�.
				if (table[i][j] == '#')
				{
					row_object[i].insert({ j,table[i][j],false });
					col_object[j].insert({ i,table[i][j],false });
				}
				else
				{
					row_object[i].insert({ j,table[i][j] - '0',true });
					col_object[j].insert({ i,table[i][j] - '0',true });
				}
			}
		}
	}
}

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0 || table[r][c] != '.')
		return false;
	else
		return true;
}

//������ ��ǥ�� ���ɿ� ���� ���õǰ� �ִ��� Ȯ���ϴ� �Լ�,
bool checkSafe(int nR, int nC, int newDist)
{
	bool valid{ true };

	//���� ���� row�� ���̳� ���ɰ� ���� ������Ʈ�� �����Ѵٸ�,
	if (row_object[nR].size() != 0)
	{
		//���� ��ǥ���� ���� ����� ������Ʈ�� col ��ǥ�� Ž���Ѵ�.
		auto object_row_right{ lower_bound(row_object[nR].begin(),row_object[nR].end(),make_tuple(nC,0,false)) };
		auto object_row_left{ object_row_right };
		//object�� ���� ��ǥ���� ���ʿ� ������ false, �����ʿ� ������ true
		bool objectDir{ true };

		//���� ��ǥ���� ���ʿ��� ������Ʈ�� ������ ��,
		if (object_row_right == row_object[nR].end())
		{
			--object_row_right;
			objectDir = false;
		}

		auto type_right{ get<2>(*object_row_right) };
		auto initDir_right{ get<1>(*object_row_right) };

		//���� �˻��� ������Ʈ�� ���� �ƴ϶��
		if (type_right != false)
		{
			auto dir{ newDist + initDir_right };
			dir %= 4;

			//���� ��ǥ���� ������ ���ʿ� ���� ��,
			if (objectDir == false)
			{
				if (dir == 0)
				{
					valid = false;
				}
			}
			else //���� ��ǥ���� ������ �����ʿ� ���� ��,
			{
				if (dir == 2)
				{
					valid = false;
				}
			}
		}

		//���� ��ǥ�� �� ���� ��� ������Ʈ�� ������ ���,
		if (object_row_left != row_object[nR].begin() && object_row_left != row_object[nR].end())
		{
			--object_row_left;

			auto type_left{ get<2>(*object_row_left) };
			auto initDir_left{ get<1>(*object_row_left) };

			if (type_left != false)
			{
				auto dir{ newDist + initDir_left };
				dir %= 4;

				if (dir == 0)
				{
					valid = false;
				}
			}
		}
	}

	//col�� row�� ������ ����.
	if (col_object[nC].size() != 0)
	{
		auto object_col_right{ lower_bound(col_object[nC].begin(),col_object[nC].end(),make_tuple(nR,0,false)) };
		auto object_col_left{ object_col_right };
		bool objectDir{ true };

		if (object_col_right == col_object[nC].end())
		{
			--object_col_right;
			objectDir = false;
		}

		auto type_right{ get<2>(*object_col_right) };
		auto initDir_right{ get<1>(*object_col_right) };

		if (type_right != false)
		{
			auto dir{ newDist + initDir_right };
			dir %= 4;

			if (objectDir == false)
			{
				if (dir == 1)
				{
					valid = false;
				}
			}
			else
			{
				if (dir == 3)
				{
					valid = false;
				}
			}
		}

		if (object_col_left != col_object[nC].begin() && object_col_left != col_object[nC].end())
		{
			--object_col_left;

			auto type_left{ get<2>(*object_col_left) };
			auto initDir_left{ get<1>(*object_col_left) };

			if (type_left != false)
			{
				auto dir{ newDist + initDir_left };
				dir %= 4;

				if (dir == 1)
				{
					valid = false;
				}
			}
		}
	}

	return valid;
}

void bfs()
{
	queue<vertex> q;
	q.push({ 0,start.first,start.second });
	dist[start.first][start.second][0] = 0;

	while (q.empty() == false)
	{
		auto cur{ q.front() };
		q.pop();

		auto r{ get<1>(cur) };
		auto c{ get<2>(cur) };
		auto curDist{ get<0>(cur) };

		if (checkSafe(r, c, curDist) == false)
			continue;

		if (r == goal.first && c == goal.second)
		{
			result = curDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };
			auto newDist{ curDist + 1 };

			if (isValid(nR, nC) == false)
				continue;

			bool valid{ checkSafe(nR,nC,newDist) };

			if (valid)
			{
				if (dist[nR][nC][newDist % 4] > newDist)
				{
					dist[nR][nC][newDist % 4] = newDist;
					q.push({ newDist,nR,nC });
				}
			}
		}

		//���� ��ǥ���� 1�� ��ٸ� �� �ִ�.
		if (dist[r][c][(curDist + 1) % 4] > curDist + 1)
		{
			dist[r][c][(curDist + 1) % 4] = curDist + 1;
			q.push({ curDist + 1,r,c });
		}
	}
}

void solve()
{
	bfs();

	if (result == -1)
		cout << "GG";
	else
		cout << result;
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