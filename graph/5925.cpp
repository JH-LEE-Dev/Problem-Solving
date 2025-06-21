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
#define MAX 51

int N, M;
vector<vector<char>> Table(MAX, vector<char>(MAX, '.'));
vector<vector<pair<int, int>>> Coords(3, vector<pair<int, int>>());
vector<vector<bool>> Visited(MAX, vector<bool>(MAX, false));

vector<int> Dir_Row{ 0,0,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0 };

vector<int> DistVec(3, INF);
vector<vector<pair<pair<int, int>, pair<int, int>>>> Route(3, vector<pair<pair<int, int>, pair<int, int>>>());

int Result{ INF };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= M || C < 0)
		return false;
	else
		return true;
}

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

int GetDist(int R, int C, int _R, int _C)
{
	return (abs(R - _R) + abs(C - _C)) - 1;
}

void Bfs(int Type, int _R, int _C)
{
	Visited[_R][_C] = true;

	queue<pair<int, int>> Q;
	Q.push({ _R,_C });
	Coords[Type].push_back({ _R,_C });

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto R{ Cur.first };
		auto C{ Cur.second };

		for (int i{ 0 }; i < 4; ++i)
		{
			int NewR{ R + Dir_Row[i] };
			int NewC{ C + Dir_Col[i] };

			if (IsValid(NewR, NewC) == false || Table[NewR][NewC] != 'X' || Visited[NewR][NewC] == true)
				continue;

			Visited[NewR][NewC] = true;
			Q.push({ NewR,NewC });

			Coords[Type].push_back({ NewR,NewC });
		}
	}
}

void CalcMinDist(vector<pair<int, int>>& Src, vector<pair<int, int>>& Dst, int Type)
{
	//�� ������ �մ� �ִ� �Ÿ��� ����ź �Ÿ��� ���Ѵ�.
	for (int i{ 0 }; i < Src.size(); ++i)
	{
		for (int j{ 0 }; j < Dst.size(); ++j)
		{
			int Src_R{ Src[i].first };
			int Src_C{ Src[i].second };
			int Dst_R{ Dst[j].first };
			int Dst_C{ Dst[j].second };

			int Dist{ GetDist(Src_R,Src_C,Dst_R,Dst_C) };

			if (DistVec[Type] > Dist)
			{
				DistVec[Type] = Dist;
				Route[Type].clear();
				Route[Type].push_back({ {Src_R,Src_C},{Dst_R,Dst_C} });
			}
			else if (DistVec[Type] == Dist)
			{
				Route[Type].push_back({ {Src_R,Src_C},{Dst_R,Dst_C} });
			}
		}
	}
}

void CalcRouteDist(int Src, int Dst)
{
	//������ �մ� �ִ� ��ο� �����ϴ� ��ǥ����, �ٸ� �ϳ��� �������� ���� ��찡 �� ª�� �� �ִ�.
	for (int i{ 0 }; i < Route[Src].size(); ++i)
	{
		int Src_R{ Route[Src][i].first.first };
		int Src_C{ Route[Src][i].first.second };
		int Dst_R{ Route[Src][i].second.first };
		int Dst_C{ Route[Src][i].second.second };

		int Start_R{ min(Src_R,Dst_R) };
		int Start_C{ min(Src_C,Dst_C) };
		int End_R{ max(Src_R,Dst_R) };
		int End_C{ max(Src_C,Dst_C) };

		for (int j{ Start_R }; j <= End_R; ++j)
		{
			for (int k{ Start_C }; k <= End_C; ++k)
			{
				for (int l{ 0 }; l < Coords[Dst].size(); ++l)
				{
					int Dist{ GetDist(j,k,Coords[Dst][l].first,Coords[Dst][l].second) };

					Result = min(Result, DistVec[Src] + Dist);
				}
			}
		}
	}
}

void Solve()
{
	int Cnt{ 0 };

	//�� ��ǥ�� ������ BFS�� ���ؼ� �����Ѵ�.
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			if (Table[i][j] == 'X' && Visited[i][j] == false)
			{
				switch (Cnt)
				{
				case 0:
					Bfs(0, i, j);
					break;
				case 1:
					Bfs(1, i, j);
					break;
				case 2:
					Bfs(2, i, j);
					break;
				}

				++Cnt;
			}
		}
	}

	//���� ����, ������ ����, ���� Ÿ��
	CalcMinDist(Coords[0], Coords[1], 0);
	CalcMinDist(Coords[0], Coords[2], 1);
	CalcMinDist(Coords[1], Coords[2], 2);

	vector<int> ResultDist;
	ResultDist.push_back(DistVec[0]);
	ResultDist.push_back(DistVec[1]);
	ResultDist.push_back(DistVec[2]);

	sort(ResultDist.begin(), ResultDist.end());

	//���� Ÿ�Ե� �߿��� ���� ���� �� ���� ���� ���ϸ� �ϴ� �ּڰ��̴�. 
	//�� ���� �� �������� ���ϴ� ��ο��� ����� ��δ� �������� �ʾҴ�.
	//���� ��� 0->1 �ִ� ��θ� �̷�� ��ǥ���� 2�� ���� ���� ���� �������� �ʾҴ�.
	//�� �� �������� �������� ���� ��츸�� ������ ��.
	Result = ResultDist[0] + ResultDist[1];

	//���� Ÿ��, ������ ����
	CalcRouteDist(0, 2);
	CalcRouteDist(1, 1);
	CalcRouteDist(2, 0);

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