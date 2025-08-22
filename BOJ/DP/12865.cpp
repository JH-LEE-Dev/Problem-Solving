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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 101
#define MAX_W 100'001
int N{ 0 }, K{ 0 };
vector<vector<int>> DP(MAX, vector<int>(MAX_W, 0));
vector<pair<int, int>> arr;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> K;

    for (int i{ 0 }; i < N; ++i)
    {
        int weight{ 0 }, cost{ 0 };
        cin >> weight >> cost;
        arr.push_back({ weight,cost });
    }

    for (int i{ 1 }; i <= N; ++i)
    {
        for (int j{ 1 }; j <= K; ++j)
        {
            int curWeight = arr[i - 1].first;
            int curCost = arr[i - 1].second;

            if (curWeight > j)
                DP[i][j] = DP[i - 1][j];
            else
                DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - curWeight] + curCost);
        }
    }

    cout << DP[N][K];

    return 0;
}