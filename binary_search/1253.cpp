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
		//같은 인덱스라면 continue
		if (idx == i)
			continue;

		//arr[idx]에서 arr[i]를 뺀 수를 arr에서 찾는다.(두 수의 합은 arr[idx])
		auto delta{ arr[idx] - arr[i] };

		auto delta_idx{ distance(arr.begin(),lower_bound(arr.begin(),arr.end(),delta)) };

		while (delta_idx < N && arr[delta_idx] == delta)
		{
			if (delta_idx == idx || delta_idx == i)
			{
				++delta_idx;
				continue;
			}

			//while문의 조건과 if문의 조건을 뚫었다면, arr[delta_idx]는 delta와 같고, arr[idx],arr[i]와 중복되지도 않는다.
			//이렇게 되면 arr[idx]를 두 수로 만드는 경우를 찾은 것이므로 바로 return
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
		//현재 i번째 인덱스의 수를 만들 수 있는 경우를 찾는다.
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