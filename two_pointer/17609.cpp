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

int T;
string Str;

void Input()
{
	cin >> T;
}

int TwoPointer(int Start, int End, int Cnt)
{
	//ȸ���� �� �� ���� ��� -> Ž�� ������ �����ų� Cnt (���ڰ� �ٸ� ����)�� 2�� �̻��� ���� 1�� ��ȯ
	//1�� ��ȯ�����ν� ȸ���� �ƴ� ���� Result�� 2�� ��.
	if (Start == End || Cnt >= 2)
		return 1;

	int Left{ Start };
	int Right{ End };
	int Result{ Cnt };

	while (Left < Right)
	{
		if (Str[Left] == Str[Right])
		{
			++Left;
			--Right;
		}
		else
		{
			++Cnt;

			Result += min(TwoPointer(Left + 1, Right, Cnt), TwoPointer(Left, Right - 1, Cnt));

			break;
		}
	}

	return Result;
}

void Solve()
{
	for (int i{ 0 }; i < T; ++i)
	{
		cin >> Str;

		int Result{ TwoPointer(0,Str.length() - 1,0) };

		cout << Result << endl;
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