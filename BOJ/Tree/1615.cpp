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
using ll = long long;

#define endl '\n'
#define INF numeric_limits<int>::max()

int n, m, s;
vector<ll> segTree;
vector<pair<int, int>> arr;

void Input()
{
	cin >> n >> m;

	for (int i{ 0 }; i < m; ++i)
	{
		int src, dst;
		cin >> src >> dst;

		arr.push_back({ src,dst });
	}

	sort(arr.begin(), arr.end());
}

void Update(int Idx)
{
	for (segTree[Idx += s] += 1; Idx > 1; Idx >>= 1)
	{
		segTree[Idx >> 1] = segTree[Idx] + segTree[Idx ^ 1];
	}
}

ll Query(int start, int end)
{
	ll ret{ 0 };

	for (start += s, end += s; start < end; start >>= 1, end >>= 1)
	{
		if (start & 1)
		{
			ret += segTree[start];
			++start;
		}

		if (end & 1)
		{
			--end;
			ret += segTree[end];
		}
	}

	return ret;
}

void Solve()
{
	int height{ (int)ceil(log2(n)) };
	int treeSize{ 1 << (height + 1) };
	segTree.resize(treeSize, 0);
	s = (1 << height);

	ll result{ 0 };

	for (int i{ 0 }; i < m; ++i)
	{
		int num{ arr[i].second };

		ll cnt{ Query(num,n) };

		Update(num - 1);

		result += cnt;
	}

	cout << result;
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