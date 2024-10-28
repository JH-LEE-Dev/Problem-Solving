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

#define MAX 105

vector<int> dist(MAX, numeric_limits<int>::max());
vector<int> ladder(MAX, 0);
vector<int> snake(MAX, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, M{ 0 };

    cin >> N >> M;

    for (int i{ 0 }; i < N; ++i)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;

        ladder[src] = dst;
    }

    for (int i{ 0 }; i < M; ++i)
    {
        int src{ 0 }, dst{ 0 };
        cin >> src >> dst;

        snake[src] = dst;
    }

    queue<int> myQ;
    myQ.push(1);

    dist[1] = 0;

    while (!myQ.empty())
    {
        int cur = myQ.front();
        myQ.pop();

        for (int i{ 1 }; i <= 6; ++i)
        {
            if (cur + i > 100)
                continue;

            int new_dist = dist[cur] + 1;

            if (new_dist < dist[cur + i])
            {
                if (snake[cur + i] != 0)
                {
                    if (dist[snake[cur + i]] > new_dist)
                    {
                        dist[snake[cur + i]] = new_dist;
                        myQ.push(snake[cur + i]);
                    }

                    continue;
                }

                if (ladder[cur + i] != 0)
                {
                    if (dist[ladder[cur + i]] > new_dist)
                    {
                        dist[ladder[cur + i]] = new_dist;
                        myQ.push(ladder[cur + i]);
                    }
                    continue;
                }

                dist[cur + i] = new_dist;
                myQ.push(cur + i);
            }
        }
    }

    cout << dist[100];

    return 0;
}