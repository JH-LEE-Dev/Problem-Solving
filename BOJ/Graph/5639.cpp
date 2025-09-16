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
#define MAX 10'001

vector<int> Arr;

void Input()
{
	int Num;

	while (cin >> Num)
	{
		Arr.push_back(Num);
	}
}

void Post(int Start, int End)
{
	if (Start >= End)
		return;

	int Index{ 0 };

	for (Index = Start + 1; Index < End; ++Index)
	{
		if (Arr[Start] < Arr[Index])
			break;
	}

	Post(Start + 1, Index);
	Post(Index, End);

	cout << Arr[Start] << endl;

	return;
}

void Solve()
{
	Post(0, Arr.size());
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