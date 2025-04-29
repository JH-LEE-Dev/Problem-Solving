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

int T, N;
unordered_map<string, string> parent;
unordered_map<string, int> ran;
unordered_map<string, int> friends;

string find(string v)
{
	auto p{ parent.find(v) };

	if (p == parent.end())
		return "";
	else
	{
		if (p->second == v)
			return v;
	}

	return parent[v] = find(parent[v]);
}

int merge(string u, string v)
{
	string p_u{ find(u) };
	string p_v{ find(v) };

	if (p_u == p_v)
	{
		return friends[p_u];
	}

	if (ran[p_u] > ran[p_v])
		swap(p_u, p_v);

	parent[p_u] = p_v;

	if (ran[p_u] == ran[p_v])
		++ran[p_v];

	friends[p_v] += friends[p_u];

	return friends[p_v];
}

void input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		string A, B;

		cin >> A >> B;

		if (parent.find(A) == parent.end())
		{
			parent[A] = A;
			++ran[A];
			++friends[A];
		}

		if (parent.find(B) == parent.end())
		{
			parent[B] = B;
			++ran[B];
			++friends[B];
		}

		cout << merge(A, B) << endl;
	}
}

void solve()
{
	cin >> T;

	while (T != 0)
	{
		input();

		parent.clear();
		ran.clear();
		friends.clear();

		--T;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	solve();

	return 0;
}