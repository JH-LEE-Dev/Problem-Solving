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
#define MAX 500'005

vector<int> line(MAX, -1);
int N{ 0 };
vector<bool> erased(MAX, false);
vector<int> idx(MAX, -1);

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

    vector<int> LIS;

    for (int i{ 1 }; i < MAX; ++i)
    {
        if (line[i] == -1)
            continue;

        auto iter = lower_bound(LIS.begin(), LIS.end(), line[i]);

        if (iter == LIS.end())
        {
            LIS.push_back(line[i]);
            idx[i] = LIS.size() - 1;
        }
        else
        {
            *iter = line[i];
            idx[i] = distance(LIS.begin(), iter);
        }
    }

    auto cursor = LIS.size() - 1;

    for (int i{ MAX - 1 }; i >= 0; --i)
    {
        if (line[i] == -1)
            continue;

        if (idx[i] != cursor)
        {
            erased[i] = true;
            continue;
        }

        cursor -= 1;
    }

    int result{ N - (int)LIS.size() };

    cout << result << endl;

    int counting{ 0 };
    for (int i{ 1 }; i < MAX; ++i)
    {
        if (counting >= result)
            break;

        if (line[i] == -1)
            continue;

        if (erased[i] == true)
        {
            cout << i << " ";

            ++counting;
        }
    }

    return 0;
}