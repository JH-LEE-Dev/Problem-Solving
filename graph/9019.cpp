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
#define MAX 10'000

vector<bool> visited(MAX + 5, false);

string bfs(int _A, int _B)
{
    queue<pair<string, int>> q;
    q.push({ "", _A });

    visited[_A] = true;

    while (q.empty() == false)
    {
        auto cur = q.front();
        q.pop();

        if (cur.second == _B)
        {
            return cur.first;
        }

        auto num = cur.second;
        //D
        auto num_D = (num * 2) % MAX;

        if (visited[num_D] == false)
        {
            visited[num_D] = true;
            q.push({ cur.first + 'D',num_D });
        }

        //S
        auto num_S = num - 1;

        if (num_S < 0)
            num_S = 9999;

        if (visited[num_S] == false)
        {
            visited[num_S] = true;
            q.push({ cur.first + 'S',num_S });
        }

        //L
        auto num_L = (num % 1000) * 10 + (num / 1000);

        if (visited[num_L] == false)
        {
            visited[num_L] = true;
            q.push({ cur.first + 'L',num_L });
        }

        //R
        auto num_R = (num % 10) * 1000 + (num / 10);

        if (visited[num_R] == false)
        {
            visited[num_R] = true;
            q.push({ cur.first + 'R',num_R });
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int T{ 0 };
    cin >> T;

    for (int i{ 0 }; i < T; ++i)
    {
        visited = vector<bool>(MAX + 5, false);
        int A, B;
        cin >> A >> B;

        cout << bfs(A, B) << endl;
    }

    return 0;
}