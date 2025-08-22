#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define endl '\n'
using namespace std;

#define MAX 100'000
int N{ 0 }, K{ 0 };
queue<int> myQueue;
vector<bool> visited(MAX + 5, false);
int counting{ 0 };

vector<int> dist(MAX + 5, numeric_limits<int>::max());

void bfs()
{
    myQueue.push(N);

    while (!myQueue.empty())
    {
        int current_vertex{ myQueue.front() };
        myQueue.pop();

        visited[current_vertex] = true;

        if (current_vertex - 1 >= 0 && dist[current_vertex] + 1 < dist[current_vertex - 1])
        {
            myQueue.push(current_vertex - 1);
            dist[current_vertex - 1] = min(dist[current_vertex - 1], dist[current_vertex] + 1);
        }

        if (current_vertex + 1 <= MAX && dist[current_vertex] + 1 < dist[current_vertex + 1])
        {
            myQueue.push(current_vertex + 1);
            dist[current_vertex + 1] = min(dist[current_vertex + 1], dist[current_vertex] + 1);
        }

        if (current_vertex * 2 <= MAX && dist[current_vertex] + 1 < dist[current_vertex * 2])
        {
            myQueue.push(current_vertex * 2);
            dist[current_vertex * 2] = min(dist[current_vertex * 2], dist[current_vertex] + 1);
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> K;

    dist[N] = 0;
    bfs();

    cout << dist[K];

    return 0;
}