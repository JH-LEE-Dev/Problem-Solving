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

int N{ 0 }, result{ 0 };
vector<int> arr;

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;

		arr.push_back(input);
	}
}

void func(int idx)
{
	for (int i{ 0 }; i < N; ++i)
	{
		//���� �ε������ continue
		if (idx == i)
			continue;

		//arr[idx]���� arr[i]�� �� ���� arr���� ã�´�.(�� ���� ���� arr[idx])
		auto delta{ arr[idx] - arr[i] };

		auto delta_idx{ distance(arr.begin(),lower_bound(arr.begin(),arr.end(),delta)) };

		while (delta_idx < N && arr[delta_idx] == delta)
		{
			if (delta_idx == idx || delta_idx == i)
			{
				++delta_idx;
				continue;
			}

			//while���� ���ǰ� if���� ������ �վ��ٸ�, arr[delta_idx]�� delta�� ����, arr[idx],arr[i]�� �ߺ������� �ʴ´�.
			//�̷��� �Ǹ� arr[idx]�� �� ���� ����� ��츦 ã�� ���̹Ƿ� �ٷ� return
			++result;
			return;
		}
	}
}

void solve()
{
	sort(arr.begin(), arr.end());

	for (int i{ 0 }; i < N; ++i)
	{
		//���� i��° �ε����� ���� ���� �� �ִ� ��츦 ã�´�.
		func(i);
	}

	cout << result;
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