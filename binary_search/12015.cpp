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
#define MAX 1'000'005
using namespace std;

vector<int> arr;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 };
    cin >> N;

    arr.resize(N);

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> arr[i];
    }

    vector<int> LIS;

    for (auto& num : arr)
    {
        auto it = lower_bound(LIS.begin(), LIS.end(), num);

        if (it == LIS.end())
        {
            LIS.push_back(num);
        }
        else
        {
            *it = num;
        }
    }

    cout << LIS.size();

    return 0;
}