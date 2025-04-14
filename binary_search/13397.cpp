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
*	���� �ذ� ����
*	1. ������ (�ִ� - �ּڰ�)�� �̺� Ž���� �Ű������� �����Ѵ�.
	2. �Ű����� a�� ���ؼ�, �迭�� ��ȸ�ϸ� ������� ���� ������ ������ a�� �Ѿ��� ���, ������
	   ������ ������Ų��. �׸��� �ִ񰪰� �ּڰ��� ���� ���ҷ� �����Ѵ�.
	3. ���� ������ ������ M�� �Ѵ´ٸ�, ���� �Ű����� a���ٴ� Ŀ�� �Ѵٴ� ���̴�.
	   ������ ������ M���϶��, �� �� ���� ������ �������� Ȯ���Ѵ�.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()

int N, M;
vector<int> arr;

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		int num;
		cin >> num;

		arr.push_back(num);
	}
}

bool divide(int a)
{
	int minVal{ arr[0] };
	int maxVal{ arr[0] };

	//������ ���� 1���� �����Ѵ�.
	//� ��쿡�� ������ 1�̻��̱� �����̴�.
	//���ڰ� �� ���� �����ص� ������ ������ 1�̴�.
	int cnt{ 1 };

	for (int i{ 0 }; i < N; ++i)
	{
		if (arr[i] > maxVal)
		{
			maxVal = arr[i];
		}

		if (arr[i] < minVal)
		{
			minVal = arr[i];
		}

		if (maxVal - minVal > a)
		{
			++cnt;

			maxVal = arr[i];
			minVal = arr[i];
		}
	}

	if (cnt > M)
		return false;
	else
		return true;
}

void solve()
{
	int left{ 0 };
	int right{ 10'000 };

	while (left <= right)
	{
		int middle{ (left + right) / 2 };

		bool divideResult{ divide(middle) };

		if (divideResult == true)
			right = middle - 1;
		else
			left = middle + 1;
	}

	cout << left;
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