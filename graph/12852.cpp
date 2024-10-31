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
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 100'0005

vector<int> dist(MAX, INF);
vector<int> parent(MAX, 0);
queue<int> path;
int N{ 0 };

void bfs()
{
    queue<int> q;
    q.push(1);
    dist[1] = 0;

    while (q.empty() == false)
    {
        auto cur = q.front();
        q.pop();

        if (cur + 1 <= N && dist[cur] + 1 < dist[cur + 1])
        {
            dist[cur + 1] = dist[cur] + 1;
            parent[cur + 1] = cur;
            q.push(cur + 1);

            if (cur + 1 == N)
            {
                break;
            }
        }

        if (cur * 2 <= N && dist[cur] + 1 < dist[cur * 2])
        {
            dist[cur * 2] = dist[cur] + 1;
            parent[cur * 2] = cur;
            q.push(cur * 2);

            if (cur * 2 == N)
            {
                break;
            }
        }

        if (cur * 3 <= N && dist[cur] + 1 < dist[cur * 3])
        {
            dist[cur * 3] = dist[cur] + 1;
            parent[cur * 3] = cur;
            q.push(cur * 3);

            if (cur * 3 == N)
            {
                break;
            }
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    bfs();

    int cur = N;

    while (cur != 1)
    {
        path.push(cur);
        cur = parent[cur];
    }
    path.push(1);

    cout << path.size() - 1 << endl;
    while (path.empty() == false)
    {
        cout << path.front() << " ";
        path.pop();
    }

    return 0;
}