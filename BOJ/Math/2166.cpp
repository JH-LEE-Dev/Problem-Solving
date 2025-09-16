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

int N;
vector<double> XArr;
vector<double> YArr;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		double X, Y;
		cin >> X >> Y;

		XArr.push_back(X);
		YArr.push_back(Y);
	}
}

void Solve()
{
	double Result{ 0 };

	for (int i = 0; i < N; ++i)
	{
		int j = (i + 1) % N; // 다음 점, 마지막은 0번으로 wrap
		Result += XArr[i] * YArr[j] - XArr[j] * YArr[i];
	}

	cout << fixed << setprecision(1) << abs(Result) / 2;
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