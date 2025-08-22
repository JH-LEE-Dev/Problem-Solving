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

int N{ 0 };
vector<int> primeFactor;

void primeFactorFunc()
{
    int dividing{ 2 };
    int Num{ N };

    while (true)
    {
        if (dividing > N)
            break;

        if (Num % dividing == 0)
        {
            Num /= dividing;
            primeFactor.push_back(dividing);
        }
        else
        {
            ++dividing;
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    primeFactorFunc();

    for (auto& factor : primeFactor)
    {
        cout << factor << endl;
    }

    return 0;
}