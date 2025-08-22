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
#define INF numeric_limits<long long>::max()
using namespace std;

#define MAX 10'001
#define MAX_ERASE 21
vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<vector<long long>> dist(MAX_ERASE, vector<long long>(MAX, INF));
int N{ 0 }, M{ 0 }, K{ 0 };
long long result{ INF };

void dijkstra()
{
    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long,
        pair<int, int>>>, greater<pair<long long, pair<int, int>>>> myPQ;

    dist[0][1] = 0;
    myPQ.push({ 0,{1,0} });

    while (myPQ.empty() == false)
    {
        auto cur = myPQ.top();
        myPQ.pop();
        auto curVertex = cur.second.first;
        auto curDist = cur.first;
        auto curErase = cur.second.second;

        if (curVertex == N)
        {
            result = curDist;
            break;
        }

        if (dist[curErase][curVertex] < curDist)
        {
            continue;
        }

        for (auto& edge : edges[curVertex])
        {
            auto dst = edge.first;
            auto weight = edge.second;
            auto newDist = curDist + weight;
            auto newEraseDist = curDist;

            if (dist[curErase][dst] > newDist)
            {
                dist[curErase][dst] = newDist;
                myPQ.push({ newDist,{dst,curErase} });
            }

            if (curErase < K)
            {
                if (dist[curErase + 1][dst] > newEraseDist)
                {
                    dist[curErase + 1][dst] = newEraseDist;
                    myPQ.push({ newEraseDist,{dst,curErase + 1} });
                }
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M >> K;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
        edges[dst].push_back({ src,w });
    }

    dijkstra();

    cout << result;

    return 0;
}