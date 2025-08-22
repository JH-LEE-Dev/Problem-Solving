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

int func(int n, int row, int col)
{
    if (n == 0)
        return 0;

    int half = (1 << (n - 1));

    if (row < half && col < half)
        return func(n - 1, row, col);

    if (row < half && col >= half)
        return half * half + func(n - 1, row, col - half);

    if (row >= half && col < half)
        return half * half * 2 + func(n - 1, row - half, col);

    return half * half * 3 + func(n - 1, row - half, col - half);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, row{ 0 }, col{ 0 };
    cin >> N >> row >> col;

    cout << func(N, row, col);

    return 0;
}