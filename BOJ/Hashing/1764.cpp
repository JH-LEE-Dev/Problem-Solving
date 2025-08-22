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

int N{ 0 }, M{ 0 };
unordered_set<string> names_1;
unordered_set<string> names_2;
vector<string> result;

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		string input;
		cin >> input;

		names_1.insert(input);
	}

	for (int i{ 0 }; i < M; ++i)
	{
		string input;
		cin >> input;

		names_2.insert(input);
	}
}

void solve()
{
	for (auto& name : names_1)
	{
		if (names_2.find(name) != names_2.end())
		{
			result.push_back(name);
		}
	}

	sort(result.begin(), result.end());
	cout << result.size() << endl;

	for (auto& name : result)
	{
		cout << name << endl;
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