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

long long POW(long long A, long long B, long long C)
{
	if (B == 0)
		return 1;

	if (B == 1)
	{
		return A % C;
	}

	long long Val = POW(A, (long long)(B * 0.5), C);

	Val = Val * Val % C;

	if (B % 2 == 0)
		return Val;
	else
		return Val * A % C;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	long long A{ 0 }, B{ 0 }, C{ 0 };
	cin >> A >> B >> C;

	cout << POW(A, B, C);
	return 0;
}