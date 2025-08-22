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

multiset<int> tree;

void deleteMax()
{
    tree.erase(prev(tree.end()));
}

void deleteMin()
{
    tree.erase(tree.begin());
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int T{ 0 };
    cin >> T;

    while (T != 0)
    {
        tree.clear();

        int N{ 0 };
        cin >> N;

        for (int i{ 0 }; i < N; ++i)
        {
            char order;
            int input;

            cin >> order >> input;

            if (order == 'I')
            {
                tree.insert(input);
            }

            if (order == 'D')
            {
                if (tree.empty())
                    continue;

                if (input == 1)
                {
                    deleteMax();
                }
                else
                {
                    deleteMin();
                }
            }
        }

        if (tree.empty())
        {
            cout << "EMPTY" << endl;
        }
        else
        {
            cout << *(prev(tree.end())) << " " << *tree.begin() << endl;
        }

        --T;
    }

    return 0;
}