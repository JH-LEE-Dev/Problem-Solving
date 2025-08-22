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

int N{ 0 };
#define MAX 1'000'001
#define LIMIT 1'000'000
vector<int> arr(MAX, 0);
vector<int> counting(MAX * 2, 0);
vector<int> result;

void countingSort()
{
    for (int i{ -LIMIT }; i <= LIMIT; ++i)
    {
        if (counting[LIMIT + i] == 0)
        {
            continue;
        }

        auto idx{ counting[LIMIT + i] };
        while (idx != 0)
        {
            result.push_back(i);
            --idx;
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> arr[i];

        ++counting[arr[i] + LIMIT];
    }

    countingSort();

    for (auto& num : result)
    {
        cout << num << " ";
    }

    return 0;
}