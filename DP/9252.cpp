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
#define MAX 1'005

int N{ 0 };
vector<vector<int>> DP(MAX, vector<int>(MAX, 0));

string reconstruct(string A, string B, int i, int j, string result)
{
    if (i == 0 || j == 0)
        return "";

    if (A[i - 1] == B[j - 1])
    {
        return reconstruct(A, B, i - 1, j - 1, result) + A[i - 1];
    }
    else if (DP[i][j - 1] > DP[i - 1][j])
    {
        return reconstruct(A, B, i, j - 1, result);
    }
    else
    {
        return reconstruct(A, B, i - 1, j, result);
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    string result{ 0 };

    stack<int> path;

    string A, B;
    cin >> A >> B;

    for (int i{ 1 }; i <= A.length(); ++i)
    {
        for (int j{ 1 }; j <= B.length(); ++j)
        {
            if (i == 0 || j == 0)
            {
                DP[i][j] = 0;
                continue;
            }

            if (A[i - 1] == B[j - 1])
            {
                DP[i][j] = DP[i - 1][j - 1] + 1;
                continue;
            }

            DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
        }
    }

    cout << DP[A.length()][B.length()] << endl;
    cout << reconstruct(A, B, A.length(), B.length(), result);
    return 0;
}