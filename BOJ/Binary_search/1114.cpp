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

int L, K, C;
vector<int> Points;
int Result{ INF };
int FirstPoint{ INF };


void Input()
{
	cin >> L >> K >> C;

	for (int i{ 0 }; i < K; ++i)
	{
		int Temp;
		cin >> Temp;

		Points.push_back(Temp);
	}
}

bool IsValid(int Len)
{
	int Cnt{ 0 };

	//���� �߶��� ����Ʈ
	int PrevPoint{ L };
	//������ �ڸ� ����Ʈ
	int NextPoint{ L };
	bool bValid{ true };

	//�ڿ��� �ִ� ���̷� �ڸ��� �����Ѵ�.

	for (int i{ (int)Points.size() - 1 }; i >= 0; --i)
	{
		NextPoint = (i == 0 ? 0 : Points[i - 1]);

		//�ڸ����� ������ ���̰� �ִ� ������ Len���� ũ�ٸ� false;
		if (PrevPoint - Points[i] > Len)
			return false;

		//���� ������ Len���� ������, ���� ����Ʈ�� �������� �� Len���� Ŀ���ٸ�
		//���� �������� �߶�� �ϹǷ� NextPoint�� ����Ͽ� ���Ѵ�.
		if (PrevPoint - NextPoint > Len)
		{
			//�߶�� ������ �̹� ���� Ƚ���� ��� ����ߴٸ� false
			if (Cnt == C)
				return false;

			PrevPoint = Points[i];
			++Cnt;
		}
	}

	//�ڸ��⸦ �Ϸ��� ���¿��� ���� ���̰� Len���� ũ�ٸ� false
	if (PrevPoint > Len)
		return false;

	FirstPoint = PrevPoint;
	Result = Len;

	//���� �ڸ��⸦ �Ϸ��� ���¿��� �ڸ� Ƚ���� ���Ҵٸ�( ���� ������ Len���� ���� ���� )
	//������ ù ��° ����Ʈ�� �ڸ� �� �ִ�.
	if (Cnt < C)
		FirstPoint = Points[0];

	return bValid;
}

void Bsearch()
{
	int Left{ 1 };
	int Right{ L };

	//�ִ� ���̿� ���� �̺� Ž���̴�.
	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };

		if (IsValid(Middle))
		{
			Right = Middle - 1;
		}
		else
		{
			Left = Middle + 1;
		}
	}
}

void Solve()
{
	sort(Points.begin(), Points.end());
	Points.erase(unique(Points.begin(), Points.end()), Points.end());

	Bsearch();

	cout << Result << ' ' << FirstPoint;
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