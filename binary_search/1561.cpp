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
* 1. ���̱ⱸ�� Ÿ�� �ð��� �������� �̺� Ž���� �����Ѵ�.
*	- �־��� �ο��� ��� �¿� �� �ִ� �ּ� �ð��� �����Ѵ�.
*	- �ּ� �ð� - 1 ���� �¿� �� �ִ� �ο��� �����Ѵ�.
*   - M ���� ���� �ⱸ�� ��ȸ�ϸ� ( �ּ� �ð� % �̿� �ð� == 0 ) �� �����Ѵٸ� 1�� ž�½�Ų��.
*	- �־��� �ο��� �����ϴ� ���� �ⱸ ��ȣ�� ����Ѵ�.
*
*	�� ������ ���̵�� : �־��� ���� ���ѱ��� ����� �յ��ϰ� �׾� �ø���.
		- �� ���� �ⱸ�� �̿� �ð��� ����� ���̰� �ǰ�, ����� ������ ����� ������ �ȴ�.
		- Ư�� ���� ����(�ּ� �ð�)�� �ΰ� ��ϵ� �� ���� �� �ִٸ� ��� �¿� �� �ִ� ���̴�.
		- ��θ� �¿� �� �ִ� �ּ� �ð� - 1�� �� �¿�� �ο����� �߻��� ���̹Ƿ�, �� �� �¿�����. �������� ž���� ��ȣ�� ���.
*/

using namespace std;
using ll = long long;
#define endl '\n'
#define INF numeric_limits<int>::max()

ll maxVal{ -1 };

ll N, M;
vector<ll> arr;

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		ll temp;
		cin >> temp;

		arr.push_back(temp);

		maxVal = max(maxVal, temp);
	}
}

void solve()
{
	if (N <= M)
	{
		cout << N;
		return;
	}

	ll left{ 1 };
	ll right{ maxVal * N };

	while (left <= right)
	{
		ll middle{ (left + right) / 2 };

		ll cnt{ M };

		for (int i{ 0 }; i < M; ++i)
		{
			cnt += middle / arr[i];
		}

		if (cnt < N)
			left = middle + 1;
		else
			right = middle - 1;
	}

	left = left - 1;

	ll cnt{ M };

	for (int i{ 0 }; i < M; ++i)
	{
		cnt += left / arr[i];
	}

	for (int i{ 0 }; i < M; ++i)
	{
		if ((left + 1) % arr[i] == 0)
			++cnt;

		if (cnt == N)
		{
			cout << i + 1;
			return;
		}
	}
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