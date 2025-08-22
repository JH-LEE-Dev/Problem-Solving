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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

vector<int> arr(100'005, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, target{ 0 };
	cin >> N >> target;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> arr[i];
	}

	int left{ 0 }, right{ 1 }, total{ arr[left] }, length{ INF };

	while (left <= right)
	{
		if (total >= target)
		{
			total -= arr[left];
			++left;

			length = min(length, right - left);
		}
		else
		{
			if (right >= N)
				break;
			total += arr[right];
			++right;
		}
	}

	if (length == INF)
		cout << 0;
	else
		cout << length + 1;

	return 0;
}