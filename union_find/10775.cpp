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

int G, P;
vector<int> Arr;
vector<int> Parent(MAX, -1);
vector<int> Rank(MAX, 1);

int Find(int U)
{
	if (Parent[U] == U)
		return U;

	return Parent[U] = Find(Parent[U]);
}

bool Merge(int U, int V)
{
	int Par_U{ Find(U) };
	int Par_V{ Find(V) };

	if (Par_U == Par_V)
		return false;

	if (Par_U < Par_V)
		swap(Par_U, Par_V);

	Parent[Par_U] = Par_V;

	return true;
}

void Input()
{
	cin >> G >> P;

	for (int i{ 0 }; i <= G; ++i)
	{
		Parent[i] = i;
	}

	for (int i{ 0 }; i < P; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);
	}
}

void Solve()
{
	int Cnt{ 0 };

	for (int i{ 0 }; i < P; ++i)
	{
		int Idx{ Arr[i] };

		int Par_Idx{ Find(Idx) };

		if (Par_Idx == 0)
			break;

		Merge(Par_Idx, Par_Idx - 1);

		++Cnt;
	}

	cout << Cnt;
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