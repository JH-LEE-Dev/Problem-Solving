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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;
#define MAX 1'005

int N{ 0 };
vector<int> arr(MAX, 0);
vector<int> DP(MAX, 1);
vector<int> parent(MAX, -1);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int result{ 0 };

    stack<int> path;

    cin >> N;
    for (int i{ 0 }; i < N; ++i)
    {
        cin >> arr[i];
    }

    int maxIdx{ 0 };

    for (int i{ 0 }; i < N; ++i)
    {
        for (int j{ 0 }; j < i; ++j)
        {
            if (arr[i] > arr[j])
            {
                if (DP[i] < DP[j] + 1)
                {
                    DP[i] = DP[j] + 1;
                    parent[i] = j;
                }
            }
        }

        if (result < DP[i])
        {
            result = DP[i];
            maxIdx = i;
        }
    }

    cout << result << endl;

    while (maxIdx != -1)
    {
        path.push(maxIdx);
        maxIdx = parent[maxIdx];
    }

    while (path.empty() == false)
    {
        cout << arr[path.top()] << " ";
        path.pop();
    }

    return 0;
}