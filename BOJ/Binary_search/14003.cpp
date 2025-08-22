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

#define MAX 1'000'005

vector<int> arr(MAX, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 };
    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> arr[i];
    }

    vector<int> LIS;
    vector<int> LIS_Idx;

    for (int i{ 0 }; i < N; ++i)
    {
        auto it = lower_bound(LIS.begin(), LIS.end(), arr[i]);
        auto dist = distance(LIS.begin(), it);

        if (it != LIS.end())
        {
            *it = arr[i];
            LIS_Idx.push_back(dist);
        }
        else
        {
            LIS.push_back(arr[i]);
            LIS_Idx.push_back(dist);
        }
    }

    cout << LIS.size() << endl;

    auto cur = LIS.size() - 1;
    for (int i{ (int)LIS_Idx.size() - 1 }; i >= 0; --i)
    {
        if (LIS_Idx[i] == cur)
        {
            LIS[cur] = arr[i];
            cur -= 1;
        }
    }

    for (auto& num : LIS)
    {
        cout << num << " ";
    }

    return 0;
}