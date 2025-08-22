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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

int T{ 0 }, M{ 0 }, N{ 0 }, X{ 0 }, Y{ 0 };
int GCD{ 0 }, LCM{ 0 };

void GCD_LCM()
{
	int a = M;
	int b = N;

	if (a < b)
		swap(a, b);

	while (true)
	{
		GCD = a % b;

		if (GCD == 0)
		{
			GCD = b;
			break;
		}

		a = b;
		b = GCD;
	}

	LCM = M * N / GCD;
}

void func()
{
	if (M == X)
		X = 0;

	if (N == Y)
		Y = 0;

	GCD_LCM();

	for (int i{ X }; i <= LCM; i += M)
	{
		if (i == 0)
			continue;

		if (i % N == Y)
		{
			cout << i << endl;
			return;
		}
	}

	cout << -1 << endl;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> T;

	while (T != 0)
	{
		cin >> M >> N >> X >> Y;

		func();

		--T;
	}

	return 0;
}