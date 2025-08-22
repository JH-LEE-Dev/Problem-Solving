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

#define MAX 25
vector<int> arr(MAX, 0);
int N{ 0 }, S{ 0 }, counting{ 0 };

void func(int idx, int sum)
{
    if (idx == N)
        return;

    sum += arr[idx];

    if (sum == S)
        ++counting;

    func(idx + 1, sum);
    sum -= arr[idx];
    func(idx + 1, sum);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> S;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> arr[i];
    }

    func(0, 0);

    cout << counting;

    return 0;
}