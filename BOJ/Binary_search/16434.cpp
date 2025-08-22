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
*  ���� �м�
*	1. �濡 ������ �� ���� ������ ���´�.
*		- ��簡 ���͸� ����
*		- ���Ͱ� ������ ���� ������ �̵�.
*		- ���Ͱ� ��縦 ����
*		- ������ ����
*		- ���� �ʾ����� �ٽ� ��� ���� ��.
*
*	���� �ذ� ����
*	1. HP�� ���� �Ű� ���� Ž���� Ȱ���ؼ�, Ư�� HP���� ��� ���͸� ���� �� �ִٸ�, �� �� ���� HP�� �������� ���캸��, �Ұ����ϴٸ�
	   �� ū HP�� ���ؼ� Ž��.
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