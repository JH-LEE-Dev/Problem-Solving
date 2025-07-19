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
using Vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 5'001

int N, M;
vector<vector<int>> Edges(MAX, vector<int>());
vector<vector<int>> Dist(MAX, vector<int>(MAX, INF));
vector<pair<int, int>> Cost(MAX, { INF,INF });

int Result{ 0 };

void Input()
{
	cin >> N >> M;

	for (int i{ 1 }; i <= N; ++i)
	{
		cin >> Cost[i].first >> Cost[i].second;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int Src, Dst;
		cin >> Src >> Dst;

		Edges[Src].push_back(Dst);
		Edges[Dst].push_back(Src);
	}
}

void Dijkstra()
{
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> PQ;
	PQ.push({ 0,0,1 });
	Dist[1][0] = 0;

	while (!PQ.empty())
	{
		auto Cur{ PQ.top() };
		PQ.pop();

		auto Src{ get<2>(Cur) };
		auto CurDist{ get<0>(Cur) };
		auto CurCount{ get<1>(Cur) };

		// ��ǥ ���� ����
		if (Src == N)
		{
			Result = CurDist;
			return;
		}

		// 1) ���� �ý� �̵� Ƚ�� ���������� ���� �̵�
		if (CurCount != 0)
		{
			int NewCnt = CurCount - 1;
			int NewCost = CurDist;

			for (auto& Dst : Edges[Src])
			{
				if (Dist[Dst][NewCnt] > NewCost)
				{
					Dist[Dst][NewCnt] = NewCost;
					PQ.push({ NewCost, NewCnt, Dst });
				}
			}
		}

		// 2) ���� ��ġ���� �ýø� ���� ����Ÿ��
		int NewCnt = Cost[Src].second - 1;            // �� �ý��� �̵� ���� Ƚ��
		int NewCost = CurDist + Cost[Src].first;      // �� �ý� ��� �߰�

		for (auto& Dst : Edges[Src])
		{
			if (Dist[Dst][NewCnt] > NewCost)
			{
				Dist[Dst][NewCnt] = NewCost;
				PQ.push({ NewCost, NewCnt, Dst });
			}
		}
	}
}

void Solve()
{

	Dijkstra();

	cout << Result;
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