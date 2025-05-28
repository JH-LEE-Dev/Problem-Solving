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
using vertex = tuple<int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'000'001

int K, N;

void input()
{
    cin >> K >> N;
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp{ a % b };

        a = b;
        b = temp;
    }

    return a;
}

void solve()
{
    int result{ 0 };

    for (int i{ 1 }; i <= N; ++i)
    {
        if (i == K)
            continue;

        if (gcd(i, K) == 1 || gcd(i, K) == 2)
            ++result;
    }

    cout << result;
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