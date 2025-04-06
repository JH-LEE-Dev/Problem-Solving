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

long long N;

void input()
{
    cin >> N;
}

void solve()
{
    if (N % 7 == 0 || N % 7 == 2)
    {
        cout << "CY";
    }
    else
    {
        cout << "SK";
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