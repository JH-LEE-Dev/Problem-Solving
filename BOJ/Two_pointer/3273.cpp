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

#define MAX 100'005

vector<int> arr(MAX, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, counting{ 0 };
    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> arr[i];
    }

    int target{ 0 };
    cin >> target;

    sort(arr.begin(), arr.begin() + N);

    int left{ 0 }, right{ N - 1 };

    if (N == 1)
    {
        cout << 0;
        return 0;
    }

    while (left < right)
    {
        if (arr[left] + arr[right] == target)
        {
            ++counting;
            ++left;
            --right;
        }
        else
        {
            if (arr[left] + arr[right] > target)
            {
                --right;
            }
            else
            {
                ++left;
            }
        }
    }

    cout << counting;

    return 0;
}