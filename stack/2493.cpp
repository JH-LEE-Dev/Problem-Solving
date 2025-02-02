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
#define MAX 500'001

int N{ 0 };
stack<pair<int, int>> st;
vector<int> result(MAX, 0);

void input()
{
    cin >> N;
}

void solve()
{
    for (int i = 1; i <= N; i++)
    {
        int num{ 0 };

        cin >> num;

        if (st.empty())
        {
            st.push({ i,num });

            cout << "0" << ' ';
        }
        else
        {
            while (st.empty() == false)
            {
                if (st.top().second > num)
                {
                    cout << st.top().first << " ";
                    break;
                }
                else
                {
                    st.pop();
                }
            }

            if (st.empty())
                cout << "0" << ' ';

            st.push({ i,num });
        }

    }
}

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}