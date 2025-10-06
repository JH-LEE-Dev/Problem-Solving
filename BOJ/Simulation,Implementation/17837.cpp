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
vector<tuple<int, int, int>> Horses;
vector<vector<vector<int>>> Stack(MAX, vector<vector<int>>(MAX, vector<int>()));

vector<int> Dir_Row{ 0,0,-1,1 };
vector<int> Dir_Col{ 1,-1,0,0 };

bool IsValid(int R, int C)
{
	if (R >= N || R < 0 || C >= N || C < 0)
		return false;
	else
		return true;
}

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
		int Dir, R, C;
		cin >> R >> C >> Dir;

		Dir -= 1;
		R -= 1;
		C -= 1;

		Horses.push_back({ Dir,R,C });
		Stack[R][C].push_back(i);
	}
}

int SwitchDir(int Dir)
{
	switch (Dir)
	{
	case 0:
		return 1;
		break;
	case 1:
		return 0;
		break;
	case 2:
		return 3;
		break;
	case 3:
		return 2;
		break;
	}

	return -1;
}

bool Move(int Idx)
{
	auto CurHorse{ Horses[Idx] };
	auto [Dir, R, C] {CurHorse};

	auto NewR{ R + Dir_Row[Dir] };
	auto NewC{ C + Dir_Col[Dir] };

	//End of Table
	if (IsValid(NewR, NewC) == false)
	{
		Dir = SwitchDir(Dir);
		NewR = R + Dir_Row[Dir];
		NewC = C + Dir_Col[Dir];
		Horses[Idx] = { Dir,R,C };

		if (IsValid(NewR, NewC) == false || Table[NewR][NewC] == 2)
			return false;
	}

	//White
	if (Table[NewR][NewC] == 0)
	{
		auto Pos{ distance(Stack[R][C].begin(),find(Stack[R][C].begin(),Stack[R][C].end(),Idx)) };

		deque<int> Temp;
		for (int i{ (int)Stack[R][C].size() - 1 }; i >= Pos; --i)
		{
			Temp.push_front(Stack[R][C][i]);
			Horses[Stack[R][C][i]] = { get<0>(Horses[Stack[R][C][i]]),NewR,NewC };
			Stack[R][C].pop_back();
		}

		for (const auto& Num : Temp)
		{
			Stack[NewR][NewC].push_back(Num);
		}
	}
	else if (Table[NewR][NewC] == 1) //Red
	{
		auto Pos{ distance(Stack[R][C].begin(),find(Stack[R][C].begin(),Stack[R][C].end(),Idx)) };

		deque<int> Temp;
		for (int i{ (int)Stack[R][C].size() - 1 }; i >= Pos; --i)
		{
			Temp.push_front(Stack[R][C][i]);
			Horses[Stack[R][C][i]] = { get<0>(Horses[Stack[R][C][i]]),NewR,NewC };
			Stack[R][C].pop_back();
		}

		reverse(Temp.begin(), Temp.end());
		for (const auto& Num : Temp)
		{
			Stack[NewR][NewC].push_back(Num);
		}
	}
	else
	{
		Dir = SwitchDir(Dir);
		NewR = R + Dir_Row[Dir];
		NewC = C + Dir_Col[Dir];
		Horses[Idx] = { Dir,R,C };

		if (IsValid(NewR, NewC) == false || Table[NewR][NewC] == 2)
			return false;

		auto Pos{ distance(Stack[R][C].begin(),find(Stack[R][C].begin(),Stack[R][C].end(),Idx)) };

		deque<int> Temp;
		for (int i{ (int)Stack[R][C].size() - 1 }; i >= Pos; --i)
		{
			Temp.push_front(Stack[R][C][i]);
			Horses[Stack[R][C][i]] = { get<0>(Horses[Stack[R][C][i]]),NewR,NewC };
			Stack[R][C].pop_back();
		}

		//White
		if (Table[NewR][NewC] == 0)
		{
			for (const auto& Num : Temp)
			{
				Stack[NewR][NewC].push_back(Num);
			}
		}
		else if (Table[NewR][NewC] == 1) //Red
		{
			reverse(Temp.begin(), Temp.end());
			for (const auto& Num : Temp)
			{
				Stack[NewR][NewC].push_back(Num);
			}
		}
	}

	if (Stack[NewR][NewC].size() >= 4)
		return true;

	return false;
}

void Solve()
{
	int Cnt{ 1 };

	while (true)
	{
		if (Cnt > 1'000)
		{
			cout << -1;
			return;
		}

		for (int i{ 0 }; i < K; ++i)
		{
			if (Move(i))
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