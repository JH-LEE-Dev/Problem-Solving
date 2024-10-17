#include <iostream>
#include <queue>
#include <vector>


#define endl '\n'
using namespace std;

queue<int> q;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, K{ 0 };
    cin >> N >> K;

    for (int i{ 1 }; i <= N; ++i)
    {
        q.push(i);
    }
    cout << '<';

    while (!q.empty())
    {
        for (int i{ 0 }; i < K - 1; ++i)
        {
            q.push(q.front());
            q.pop();
        }

        cout << q.front();

        if (q.size() != 1)
        {
            cout << ", ";
        }

        q.pop();
    }

    cout << '>';

    return 0;
}