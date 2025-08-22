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
*	문제 해결 전략
*	1. 구간의 (최댓값 - 최솟값)을 이분 탐색의 매개변수로 설정한다.
	2. 매개변수 a에 대해서, 배열을 순회하며 현재까지 평가한 구간의 점수라 a를 넘었을 경우, 구간의
	   개수를 증가시킨다. 그리고 최댓값과 최솟값을 현재 원소로 갱신한다.
	3. 만약 구간의 개수가 M을 넘는다면, 현재 매개변수 a보다는 커야 한다는 것이다.
	   구간의 개수가 M이하라면, 좀 더 작은 점수가 가능한지 확인한다.
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

	//구간의 수는 1부터 시작한다.
	//어떤 경우에도 구간은 1이상이기 때문이다.
	//숫자가 한 개만 존재해도 구간의 개수는 1이다.
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