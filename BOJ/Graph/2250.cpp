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
#define MAX 10'001

int N;
vector<vector<int>> Child(MAX, vector<int>(2, -1));
int Result{ 1 };
int MaxLevel{ 1 };
vector<vector<int>> SubTreeCnt(MAX, vector<int>(2, 0));
vector<int> LevelMin(MAX, INF);
vector<int> LevelMax(MAX, -1);
vector<int> Indegree(MAX, 0);

int Root{ 1 };

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int Parent, Child1, Child2;

		cin >> Parent >> Child1 >> Child2;

		Child[Parent][0] = Child1;
		Child[Parent][1] = Child2;

		if (Child1 != -1)
			++Indegree[Child1];
		if (Child2 != -1)
			++Indegree[Child2];
	}
}

int Dfs(int V)
{
	int LeftCnt{ 0 };
	int RightCnt{ 0 };

	if (Child[V][0] == -1 && Child[V][1] == -1)
		return 1;

	if (V == 15)
		int a = 0;

	if (Child[V][0] != -1)
	{
		LeftCnt = Dfs(Child[V][0]);
	}

	if (Child[V][1] != -1)
	{
		RightCnt = Dfs(Child[V][1]);
	}

	SubTreeCnt[V][0] = LeftCnt;
	SubTreeCnt[V][1] = RightCnt;

	return LeftCnt + RightCnt + 1;
}

void Bfs()
{
	queue<tuple<int, int, int>> Q;

	if (Child[Root][0] != -1)
		Q.push({ N - SubTreeCnt[Root][1],Child[Root][0] ,2 });

	if (Child[Root][1] != -1)
		Q.push({ N + 1,Child[Root][1] ,2 });

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto Src{ get<1>(Cur) };
		auto ParentCoord{ get<0>(Cur) };
		auto CurLevel{ get<2>(Cur) };

		int CurCoord{ ParentCoord - SubTreeCnt[Src][1] - 1 };

		LevelMin[CurLevel] = min(LevelMin[CurLevel], CurCoord);
		LevelMax[CurLevel] = max(LevelMax[CurLevel], CurCoord);

		if (Child[Src][0] != -1)
		{
			Q.push({ CurCoord,Child[Src][0],CurLevel + 1 });
		}

		if (Child[Src][1] != -1)
		{
			Q.push({ ParentCoord ,Child[Src][1],CurLevel + 1 });
		}
	}
}

void Solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		if (Indegree[i] == 0)
		{
			Dfs(i);
			Root = i;
			break;
		}
	}

	Bfs();

	for (int i{ 1 }; i < MAX; ++i)
	{
		if (Result < LevelMax[i] - LevelMin[i] + 1)
		{
			Result = LevelMax[i] - LevelMin[i] + 1;
			MaxLevel = i;
		}
	}

	cout << MaxLevel << ' ' << Result;
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