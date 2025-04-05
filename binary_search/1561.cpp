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
* 1. 놀이기구를 타는 시간을 기준으로 이분 탐색을 실행한다.
*	- 주어진 인원을 모두 태울 수 있는 최소 시간을 결정한다.
*	- 최소 시간 - 1 동안 태울 수 있는 인원들 결정한다.
*   - M 개의 놀이 기구를 순회하며 ( 최소 시간 % 이용 시간 == 0 ) 에 만족한다면 1명씩 탑승시킨다.
*	- 주어진 인원에 도달하는 놀이 기구 번호를 출력한다.
*
*	이 문제의 아이디어 : 주어진 높이 제한까지 블록을 균등하게 쌓아 올린다.
		- 각 놀이 기구의 이용 시간은 블록의 길이가 되고, 블록의 개수가 사람의 개수가 된다.
		- 특정 높이 제한(최소 시간)을 두고 블록들 다 쌓을 수 있다면 모두 태울 수 있는 것이다.
		- 모두를 태울 수 있는 최소 시간 - 1은 못 태우는 인원들이 발생할 것이므로, 한 명씩 태워본다. 마지막에 탑승한 번호를 출력.
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