#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<long long> DP(505, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, count{ 0 };
    cin >> N;

    for (int i = 5; i <= N; ++i)
    {
        if (i % 5 == 0)
            ++count;

        if (i % 25 == 0)
            ++count;

        if (i % 125 == 0)
            ++count;
    }

    cout << count;
    return 0;
}