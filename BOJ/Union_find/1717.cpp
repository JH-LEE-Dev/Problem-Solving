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
*  문제 분석
*	1. 0~N 까지의 원소가 주어지고, 각각이 집합이다.
*	2. 0 a b 는 a와 b가 속한 집합을 합하는 연산, 1 a b 는 a와 b가 같은 집합에 속해있는지 확인하는 연산.
*
*  문제 해결 전략
*	1. Union Find를 활용해서 푼다.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'000'001

int N, M;
vector<tuple<int, int, int>> orders;
vector<int> parent(MAX, 0);
vector<int> ran(MAX, 0);

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		int type, a, b;

		cin >> type >> a >> b;

		orders.push_back({ type,a,b });
	}
}

int find(int elem)
{
	if (parent[elem] == elem)
		return elem;

	return parent[elem] = find(parent[elem]);
}

void merge(int elem_1, int elem_2)
{
	int parent_elem_1{ find(elem_1) };
	int parent_elem_2{ find(elem_2) };

	if (parent_elem_1 == parent_elem_2)
		return;

	if (ran[parent_elem_1] > ran[parent_elem_2])
		swap(parent_elem_1, parent_elem_2);

	parent[parent_elem_1] = parent_elem_2;

	if (ran[parent_elem_1] == ran[parent_elem_2])
		++ran[parent_elem_2];
}

void solve()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		parent[i] = i;
		ran[i] = 1;
	}

	for (int i{ 0 }; i < M; ++i)
	{
		int type{ get<0>(orders[i]) };
		int a{ get<1>(orders[i]) };
		int b{ get<2>(orders[i]) };

		if (type == 0)
		{
			merge(a, b);
		}
		else
		{
			int par_a{ find(a) };
			int par_b{ find(b) };

			if (par_a == par_b)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
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