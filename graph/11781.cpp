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

#define endl '\n'
#define INF numeric_limits<long long>::max()
using namespace std;

#define MAX 5'001
vector<vector<tuple<int, long long, bool>>> edges(MAX, vector<tuple<int, long long, bool>>());
int N{ 0 }, M{ 0 };
long long S{ 0 }, E{ 0 };
vector<long long> dist(MAX, INF);

long long result{ -1 };

void dijkstra()
{
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> myPQ;
    myPQ.push({ 0,1 });
    dist[1] = 0;

    while (myPQ.empty() == false)
    {
        auto cur{ myPQ.top() };
        myPQ.pop();

        auto src{ cur.second };
        auto curDist{ cur.first };

        if (dist[src] < curDist)
            continue;

        result = max(result, curDist);

        for (auto& edge : edges[src])
        {
            auto dst{ get<0>(edge) };
            auto w{ get<1>(edge) };
            auto isJammed{ get<2>(edge) };

            if (isJammed == true)
            {
                if (curDist + w - S <= 0)
                {
                    if (dist[dst] > curDist + w)
                    {
                        dist[dst] = curDist + w;
                        myPQ.push({ dist[dst],dst });
                    }
                }
                else
                {
                    if (curDist >= S)
                    {
                        if (curDist >= E)
                        {
                            if (dist[dst] > curDist + w)
                            {
                                dist[dst] = curDist + w;
                                myPQ.push({ dist[dst],dst });
                            }
                        }
                        else
                        {
                            auto newDist{ curDist };

                            if (curDist + w * 2 <= E)
                            {
                                newDist += w * 2;

                                if (dist[dst] > newDist)
                                {
                                    dist[dst] = newDist;
                                    myPQ.push({ newDist,dst });
                                }
                            }
                            else
                            {
                                auto deltaTime{ E - curDist };
                                w -= (deltaTime / 2);

                                newDist += deltaTime;
                                newDist += w;

                                if (dist[dst] > newDist)
                                {
                                    dist[dst] = newDist;
                                    myPQ.push({ newDist,dst });
                                }
                            }
                        }
                    }
                    else
                    {
                        auto distDelta{ S - curDist };
                        w -= distDelta;
                        auto newDist{ curDist + distDelta };

                        if (curDist + w * 2 <= E)
                        {
                            newDist += w * 2;

                            if (dist[dst] > newDist)
                            {
                                dist[dst] = newDist;
                                myPQ.push({ newDist,dst });
                            }
                        }
                        else
                        {
                            auto deltaTime{ E - S };
                            w -= (deltaTime / 2);

                            newDist += deltaTime;
                            newDist += w;

                            if (dist[dst] > newDist)
                            {
                                dist[dst] = newDist;
                                myPQ.push({ newDist,dst });
                            }
                        }
                    }
                }
            }
            else
            {
                if (dist[dst] > curDist + w)
                {
                    dist[dst] = curDist + w;
                    myPQ.push({ dist[dst],dst });
                }
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M >> S >> E;
    S *= 2;
    E *= 2;

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 }, w{ 0 }, t1{ 0 }, t2{ 0 };
        cin >> src >> dst >> w >> t1 >> t2;
        w *= 2;
        if (t1 == 0)
        {
            edges[src].push_back({ dst,w,false });
        }
        else
        {
            edges[src].push_back({ dst,w,true });
        }

        if (t2 == 0)
        {
            edges[dst].push_back({ src,w,false });
        }
        else
        {
            edges[dst].push_back({ src,w,true });
        }
    }

    dijkstra();

    cout << result / 2;

    if (result % 2 == 1)
        cout << ".5";
    return 0;
}