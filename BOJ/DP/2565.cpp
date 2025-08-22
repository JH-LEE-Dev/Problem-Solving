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
#define MAX 505
vector<int> line(MAX, -1);
vector<int> DP(MAX, 1);
int N{ 0 };
int result{ -1 };

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;

        line[src] = dst;
    }

    for (int i{ 1 }; i < MAX; ++i)
    {
        if (line[i] == -1)
            continue;

        for (int j{ 1 }; j < i; ++j)
        {
            if (line[i] > line[j])
            {
                if (line[j] == -1)
                    continue;

                DP[i] = max(DP[i], DP[j] + 1);
                result = max(DP[i], result);
            }
        }
    }

    cout << N - result;

    return 0;
}