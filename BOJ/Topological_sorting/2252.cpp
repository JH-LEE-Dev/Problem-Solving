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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 32'001
int N{ 0 }, M{ 0 };
vector<vector<int>> edges(MAX, vector<int>());
vector<int> degree(MAX, 0);
queue<int> myQ;
vector<int> result;

void topoSorting()
{
    for (int i{ 1 }; i <= N; ++i)
    {
        if (degree[i] == 0)
        {
            myQ.push(i);
        }
    }

    while (myQ.empty() == false)
    {
        auto src = myQ.front();
        myQ.pop();
        result.push_back(src);

        for (auto& dst : edges[src])
        {
            --degree[dst];

            if (degree[dst] == 0)
            {
                myQ.push(dst);
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;

        edges[src].push_back(dst);
        ++degree[dst];
    }

    topoSorting();

    for (auto& num : result)
    {
        cout << num << " ";
    }

    return 0;
}