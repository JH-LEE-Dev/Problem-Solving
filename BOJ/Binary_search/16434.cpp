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

/*
*  문제 분석
*	1. 방에 입장할 때 다음 순서를 갖는다.
*		- 용사가 몬스터를 공격
*		- 몬스터가 죽으면 다음 방으로 이동.
*		- 몬스터가 용사를 공격
*		- 죽으면 실패
*		- 죽지 않았으면 다시 용사 공격 턴.
*
*	문제 해결 전략
*	1. HP에 대한 매개 변수 탐색을 활용해서, 특정 HP에서 모든 몬스터를 잡을 수 있다면, 좀 더 작은 HP는 가능한지 살펴보고, 불가능하다면
	   더 큰 HP에 대해서 탐색.
*/

using namespace std;
using ll = long long;

#define endl '\n'
#define INF numeric_limits<ll>::max()

ll N, Att;
vector<tuple<int, int, int>> room;

ll minHP{ INF };

void input()
{
	cin >> N >> Att;

	for (int i{ 0 }; i < N; ++i)
	{
		int type;

		cin >> type;

		if (type == 1)
		{
			int monAtt, monHP;

			cin >> monAtt >> monHP;

			room.push_back({ type,monAtt,monHP });
		}
		else
		{
			int incAtt, incHP;

			cin >> incAtt >> incHP;

			room.push_back({ type,incAtt,incHP });
		}
	}
}

void bSearch()
{
	ll left{ 1 };
	ll right{ INF };

	while (left <= right)
	{
		ll middle{ (left + right) / 2 };

		bool result{ true };

		ll curHP{ middle };
		ll curAtt{ Att };

		for (int i{ 0 }; i < N; ++i)
		{
			int curType{ get<0>(room[i]) };

			if (curType == 1)
			{
				ll monAtt{ get<1>(room[i]) };
				ll monHP{ get<2>(room[i]) };

				ll toKillMonsterTurn{ (monHP / curAtt) };

				if (monHP % curAtt != 0)
					++toKillMonsterTurn;

				ll toKillHeroDamage{ monAtt * (toKillMonsterTurn - 1) };

				if (toKillHeroDamage >= curHP)
				{
					result = false;
					break;
				}
				else
				{
					curHP -= toKillHeroDamage;
				}
			}
			else
			{
				int incAtt{ get<1>(room[i]) };
				int incHP{ get<2>(room[i]) };

				curHP += incHP;

				if (curHP >= middle)
					curHP = middle;

				curAtt += incAtt;
			}
		}

		if (result == false)
			left = middle + 1;
		else
			right = middle - 1;
	}

	minHP = left;
}

void solve()
{
	bSearch();

	cout << minHP;
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