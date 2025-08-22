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
#include <cmath>
#include <bitset>
#include <iomanip>

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()

int N{ 0 }, K{ 0 };
vector<pair<int, int>> jewels;
vector<int> bags;

void input()
{
    cin >> N >> K;

    for (int i{ 0 }; i < N; ++i)
    {
        pair<int, int> jewel;
        cin >> jewel.first >> jewel.second;

        jewels.push_back(jewel);
    }

    for (int i{ 0 }; i < K; ++i)
    {
        int input;
        cin >> input;

        bags.push_back(input);
    }
}

void solve()
{
    sort(jewels.begin(), jewels.end());
    sort(bags.begin(), bags.end());

    priority_queue<int> pq;

    int idx{ 0 };
    int jewel_idx{ 0 };
    long long result{ 0 };

    while (true)
    {
        if (idx == K)
            break;

        for (; jewel_idx < N; ++jewel_idx)
        {
            if (bags[idx] >= jewels[jewel_idx].first)
            {
                pq.push({ jewels[jewel_idx].second });
            }
            else
                break;
        }

        if (pq.empty() == false)
        {
            auto maxVal{ pq.top() };
            result += maxVal;
            pq.pop();
        }

        ++idx;
    }

    cout << result;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}