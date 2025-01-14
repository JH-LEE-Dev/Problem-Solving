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

int N{ 0 }, K{ 0 };
vector<int> DP(MAX, 0);
vector<int> coin;

void input()
{
    cin >> N >> K;

    for (int i{ 0 }; i < N; ++i)
    {
        int input{ 0 };
        cin >> input;

        coin.push_back(input);
    }
}

void solve()
{
    DP[0] = 1;

    for (int i{ 0 }; i < N; ++i)
    {
        for (int j{ coin[i] }; j <= K; ++j)
        {
            DP[j] += DP[j - coin[i]];
        }
    }

    for (int i{ 1 }; i <= K; ++i)
    {
        for (int j{ 0 }; j < N; ++j)
        {
            if (i >= coin[j])
                DP[i] += DP[i - coin[j]];
        }
    }

    cout << DP[K];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}