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
using namespace std;

#define MAX 20'005
#define INF numeric_limits<int>::max()

int V{ 0 }, E{ 0 };
int must_src{ 0 }, must_dst{ 0 };
bool must_passed_1{ false };
bool must_passed_2{ false };

vector<vector<pair<int, int>>> edges(MAX, vector<pair<int, int>>());
vector<int> dist(MAX, INF);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> V >> E;

    for (int i{ 0 }; i < E; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 };
        cin >> src >> dst >> w;

        edges[src].push_back({ dst,w });
        edges[dst].push_back({ src,w });
    }

    cin >> must_src >> must_dst;

    priority_queue<pair<int, int>> pQ;
    pQ.push({ 0,1 });
    dist[1] = 0;

    while (!pQ.empty())
    {
        auto cur = pQ.top();
        pQ.pop();

        for (auto& it : edges[cur.second])
        {
            int weight = it.second;

            if (cur.second == must_src)
            {
                if (must_passed_1 == false)
                {
                    must_passed_1 = true;
                }
            }

            if (cur.second == must_dst)
            {
                if (must_passed_2 == false)
                {
                    must_passed_2 = true;
                }
            }

            if (dist[cur.second] + weight < dist[it.first])
            {
                dist[it.first] = dist[cur.second] + weight;
                pQ.push({ -dist[it.first],it.first });
            }
        }
    }

    if (must_passed_1 == false || must_passed_2 == false || dist[V] == INF)
    {
        cout << -1;

        return 0;
    }

    int src_dist = dist[must_src];
    int dst_dist = dist[must_dst];
    must_passed_1 = false;
    must_passed_2 = false;

    dist = vector<int>(MAX, INF);
    dist[must_src] = src_dist;
    pQ.push({ -dist[must_src],must_src });

    while (!pQ.empty())
    {
        auto cur = pQ.top();
        pQ.pop();

        for (auto& it : edges[cur.second])
        {
            int weight = it.second;

            if (cur.second == must_dst && must_passed_1 == false)
            {
                int new_dist = dist[must_dst];
                dist = vector<int>(MAX, INF);
                dist[must_dst] = new_dist;
                must_passed_1 = true;

                pQ = priority_queue<pair<int, int>>();
            }

            if (dist[cur.second] + weight < dist[it.first])
            {
                dist[it.first] = dist[cur.second] + weight;
                pQ.push({ -dist[it.first],it.first });
            }
        }
    }

    int src_result{ INF };
    src_result = min(dist[V], src_result);

    dist = vector<int>(MAX, INF);
    dist[must_dst] = dst_dist;
    pQ.push({ -dist[must_dst],must_dst });

    while (!pQ.empty())
    {
        auto cur = pQ.top();
        pQ.pop();

        for (auto& it : edges[cur.second])
        {
            int weight = it.second;

            if (cur.second == must_src && must_passed_2 == false)
            {
                int new_dist = dist[must_src];
                dist = vector<int>(MAX, INF);
                dist[must_src] = new_dist;
                must_passed_2 = true;

                pQ = priority_queue<pair<int, int>>();
            }

            if (dist[cur.second] + weight < dist[it.first])
            {
                dist[it.first] = dist[cur.second] + weight;
                pQ.push({ -dist[it.first],it.first });
            }
        }
    }

    int dst_result{ INF };
    dst_result = min(dist[V], dst_result);

    if (must_passed_1 == false)
    {
        cout << dst_result;

        return 0;
    }

    if (must_passed_2 == false)
    {
        cout << src_result;

        return 0;
    }

    cout << min(dst_result, src_result);

    return 0;
}