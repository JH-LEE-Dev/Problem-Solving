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
#define MAX 15

int N, K;
vector<vector<int>> Table(MAX, vector<int>(MAX, 0));
vector<vector<string>> StrTable(MAX, vector<string>(MAX, ""));
vector<int> HorseDir;
map<int, pair<int, int>> MyMap;

vector<int> Dir_Row{ 0,0,-1,1 };
vector<int> Dir_Col{ 1,-1,0,0 };

void Input()
{
	cin >> N >> K;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> Table[i][j];
		}
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int R, C, Dir;
		cin >> R >> C >> Dir;
		R -= 1;
		C -= 1;
		Dir -= 1;

		HorseDir.push_back(Dir);
		MyMap[i] = { R,C };
		StrTable[R][C] = to_string(i);
	}
}

int SwitchDir(int Dir)
{
	if (Dir == 0)
		Dir = 1;
	else if (Dir == 1)
		Dir = 0;
	else if (Dir == 2)
		Dir = 3;
	else
		Dir = 2;

	return Dir;
}

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= N || C < 0)
		return false;
	else
		return true;
}

void Solve()
{
	int Cnt{ 1 };

	while (true)
	{
		if (Cnt >= 1'000)
		{
			cout << -1;
			return;
		}

		for (const auto& H : MyMap)
		{
			auto FirstChar{ H.first };
			auto [R, C] {H.second};

			//�߰��� �ִ� ���̶�� ��������.
			if (R == -1 && C == -1)
				continue;

			auto CurStr{ StrTable[R][C] };
			auto Dir{ HorseDir[FirstChar] };

			auto NewR{ R + Dir_Row[Dir] };
			auto NewC{ C + Dir_Col[Dir] };

			//�Ķ��� Ÿ�� ���
			if (IsValid(NewR, NewC) == false)
			{
				Dir = SwitchDir(Dir);

				NewR = R + Dir_Row[Dir];
				NewC = C + Dir_Col[Dir];

				//���� �Ķ��� Ÿ���̸� ��������.
				if (IsValid(NewR, NewC) == false || Table[NewR][NewC] == 2)
					continue;
			}

			//������ Ÿ���̸� ���� ���ڿ� ������.
			if (Table[NewR][NewC] == 1)
			{
				reverse(CurStr.begin(), CurStr.end());
			}
			else if (Table[NewR][NewC] == 2) //�Ķ��� Ÿ��.
			{
				Dir = SwitchDir(Dir);

				NewR = R + Dir_Row[Dir];
				NewC = C + Dir_Col[Dir];

				//���� �Ķ��� Ÿ�� ��������.
				if (IsValid(NewR, NewC) == false || Table[NewR][NewC] == 2)
					continue;

				//�̵� ���� �ٲ� �� �̵��� Ÿ���� ������ Ÿ���� ��,
				if (Table[NewR][NewC] == 1)
					reverse(CurStr.begin(), CurStr.end());
			}

			//�ٲ� ���� ����.
			HorseDir[FirstChar] = Dir;
			//�̵��� ĭ�� ���ڿ�
			auto TargetStr{ StrTable[NewR][NewC] };

			//�̵��� ĭ�� ���ڿ��� �̹� �����Ѵٸ�, ���� ���ڴ� �߰��� ���� ��.
			if (TargetStr != "")
				MyMap[FirstChar] = { -1,-1 };
			else
			{
				//�̵��� ĭ�� ���ڿ��� ������, ���� ������ ��ǥ�� ������Ʈ.
				MyMap[FirstChar] = { -1,-1 };
				MyMap[CurStr[0] - '0'] = { NewR,NewC };
			}

			TargetStr += CurStr;
			StrTable[NewR][NewC] = TargetStr;
			StrTable[R][C] = "";

			if (TargetStr.length() >= 4)
			{
				cout << Cnt;
				return;
			}
		}

		++Cnt;
	}
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