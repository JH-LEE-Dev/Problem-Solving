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

int N{ 0 }, M{ 0 };

vector<bool> visited(10, false);
vector<int> arr(0);

void func(int num, int m)
{
    if (m == M)
    {
        arr.push_back(num);

        for (auto& it : arr)
        {
            cout << it << " ";
        }
        cout << endl;
        arr.pop_back();

        return;
    }

    visited[num] = true;
    arr.push_back(num);

    for (int i{ 1 }; i <= N; ++i)
    {
        if (i == num || visited[i] == true)
            continue;

        func(i, m + 1);
    }

    visited[num] = false;
    arr.pop_back();
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    vector<int> arr;
    for (int i{ 1 }; i <= N; ++i)
    {
        func(i, 1);
    }

    return 0;
}