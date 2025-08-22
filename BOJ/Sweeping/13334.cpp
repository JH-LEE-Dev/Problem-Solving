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
using State = pair<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()

int N, D;
int Result;
vector<pair<int, int>> Arr;

bool Compare(const pair<int, int>& Lhs, const pair<int, int>& Rhs)
{
	if (Lhs.second == Rhs.second)
		return Lhs.first < Rhs.first;

	return Lhs.second < Rhs.second;
}


void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int Src, Dst;
		cin >> Src >> Dst;

		if (Src > Dst)
			swap(Src, Dst);

		Arr.push_back({ Src,Dst });
	}

	cin >> D;
}

void Solve()
{
	sort(Arr.begin(), Arr.end(), Compare);
	priority_queue<int, vector<int>, greater<int>> PQ;

	int Start{ 0 }, End{ 0 }, Cnt{ 0 };

	for (int i = 0; i < N; ++i)
	{
		End = Arr[i].second;
		Start = End - D;

		while (PQ.empty() == false && PQ.top() < Start)
		{
			--Cnt;
			PQ.pop();
		}

		if (Arr[i].first >= Start)
		{
			++Cnt;
			PQ.push(Arr[i].first);

			Result = max(Result, Cnt);
		}

	}

	cout << Result;
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