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

double A, B, C;

void Input()
{
	cin >> A >> B >> C;
}

void Bsearch()
{
	double Left{ (C - B) / A };
	double Right{ (C + B) / A };
	double Middle{ 0 };

	//Á¤¹Ðµµ
	while ((Right - Left) >= 1e-9)
	{
		Middle = (Left + Right) / 2;

		double Result{ A * Middle + B * (sin(Middle)) };

		if (Result < C)
			Left = Middle;
		else
			Right = Middle;
	}

	cout << fixed << setprecision(10) << Middle;
}

void Solve()
{
	Bsearch();
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