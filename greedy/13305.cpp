#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

#define MAX 100'005

vector<long long> cost(MAX, 0);
vector<long long> dist(MAX, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    long long N{ 0 }, totalCost{ 0 };
    cin >> N;

    for (long long i{ 0 }; i < N - 1; ++i)
    {
        cin >> dist[i];
    }

    for (long long i{ 0 }; i < N; ++i)
    {
        cin >> cost[i];
    }

    long long minCost{ cost[0] };
    for (long long i{ 1 }; i < N; ++i)
    {
        totalCost += minCost * dist[i - 1];

        if (minCost > cost[i])
        {
            minCost = cost[i];
        }
    }

    cout << totalCost;

    return 0;
}