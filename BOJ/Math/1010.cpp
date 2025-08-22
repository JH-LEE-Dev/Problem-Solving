#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> DP(31, vector<int>(31, 0));

int binomialCoefficient(int n, int k)
{
    if (DP[n][k] != 0)
        return DP[n][k];

    for (int i = 0; i <= n; i++)
    {
        DP[i][0] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= min(i, k); j++)
        {
            DP[i][j] = DP[i - 1][j - 1] + DP[i - 1][j];
        }
    }

    return DP[n][k];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;

    for (int i{ 0 }; i < T; ++i)
    {
        int n, k;

        cin >> n >> k;

        cout << binomialCoefficient(k, n) << endl;
    }

    return 0;
}