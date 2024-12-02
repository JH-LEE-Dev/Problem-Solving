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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

bitset<33554432> bSet;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1)
    {
        int input;

        cin >> input;

        if (input == 0)
            break;

        if (cin.eof())
            break;

        if (bSet[input] == false)
        {
            bSet[input] = true;

            cout << input << " ";
        }
    }

    return 0;
}