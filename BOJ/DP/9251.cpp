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

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

string A;
string B;

vector<vector<int>> DP(MAX, vector<int>(MAX, 0));

void input()
{
    cin >> A >> B;
}

void solve()
{
    int len_A{ (int)A.length() };
    int len_B{ (int)B.length() };

    for (int i{ 1 }; i <= len_A; ++i)
    {
        for (int j{ 1 }; j <= len_B; ++j)
        {
            if (A[i - 1] == B[j - 1])
            {
                DP[i][j] = DP[i - 1][j - 1] + 1;
            }
            else
            {
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            }
        }
    }

    cout << DP[len_A][len_B];
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}