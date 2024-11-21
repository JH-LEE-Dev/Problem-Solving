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

int N{ 0 };
vector<int> line(MAX, -1);
vector<int> LIS;

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

        auto iter = lower_bound(LIS.begin(), LIS.end(), line[i]);

        if (iter == LIS.end())
        {
            LIS.push_back(line[i]);
        }
        else
        {
            *iter = line[i];
        }
    }

    cout << N - LIS.size();

    return 0;
}