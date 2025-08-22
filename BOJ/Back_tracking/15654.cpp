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

vector<int> arr(10, 0);
vector<int> pre(10, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, K{ 0 };
    cin >> N >> K;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.begin() + N);

    do
    {
        bool flag = false;

        for (int i{ 0 }; i < K; ++i)
        {
            if (pre[i] == arr[i])
                continue;
            else
            {
                flag = true;
                break;
            }
        }

        if (flag == false)
            continue;

        for (int i{ 0 }; i < K; ++i)
        {
            cout << arr[i] << " ";
            pre[i] = arr[i];
        }
        cout << endl;
    } while (next_permutation(arr.begin(), arr.begin() + N));

    return 0;
}