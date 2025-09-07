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
using State = tuple<int, string>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 20'001

int T;
vector<bool> Visited;
vector<int> Numbers;

void Input()
{
	cin >> T;

	for (int i{ 0 }; i < T; ++i)
	{
		int N;
		cin >> N;

		Numbers.push_back(N);
	}
}

string Bfs(int N)
{
	queue<State> Q;
	Q.push({ 1,"1" });

	while (Q.empty() == false)
	{
		auto Cur{ Q.front() };
		Q.pop();

		auto CurNum{ get<0>(Cur) };
		auto CurStr{ get<1>(Cur) };

		if (CurNum % N == 0)
		{
			return CurStr;
		}

		auto NewNum_0{ (CurNum * 10) % N };
		auto NewStr_0{ CurStr + '0' };

		auto NewNum_1{ (CurNum * 10 + 1) % N };
		auto NewStr_1{ CurStr + '1' };

		if (Visited[NewNum_0] == false)
		{
			Visited[NewNum_0] = true;
			Q.push({ NewNum_0,NewStr_0 });
		}

		if (Visited[NewNum_1] == false)
		{
			Visited[NewNum_1] = true;
			Q.push({ NewNum_1,NewStr_1 });
		}
	}

	return "BRAK";
}

void Solve()
{
	for (int i{ 0 }; i < T; ++i)
	{
		Visited = vector<bool>(MAX, false);
		cout << Bfs(Numbers[i]) << endl;
	}
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