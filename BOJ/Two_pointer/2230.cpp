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
#define MAX 100'001

int N, M;
vector<int> Arr;

void Input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);
	}
}

void Solve()
{
	sort(Arr.begin(), Arr.end());

	int Left{ 0 };
	int Right{ 0 };
	int Min{ INF };

	while (Left < N && Right < N)
	{
		int Diff{ Arr[Right] - Arr[Left] };

		if (Diff >= M)
		{
			Min = min(Min, Diff);
			++Left; // 더 작은 차이를 찾아야 하므로 Left 증가
		}
		else {
			++Right; // 차이를 키워야 하므로 Right 증가
		}
	}

	cout << Min;
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