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

vector<bool> parellel(15, false);
int N{ 0 }, counting{ 0 };
vector<bool> diagonal_1(35, false);
vector<bool> diagonal_2(35, false);

void func(int col)
{
    if (col == N + 1)
    {
        ++counting;
        return;
    }

    for (int row = 1; row <= N; ++row)
    {
        if (parellel[row] || diagonal_1[row + col] || diagonal_2[col - row + N])
            continue;

        parellel[row] = true;
        diagonal_1[row + col] = true;
        diagonal_2[col - row + N] = true;

        func(col + 1);

        parellel[row] = false;
        diagonal_1[row + col] = false;
        diagonal_2[col - row + N] = false;
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    func(1);

    cout << counting;

    return 0;
}