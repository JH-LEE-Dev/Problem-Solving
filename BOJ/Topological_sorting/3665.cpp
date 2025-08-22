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

#define MAX 501
int N{ 0 }, M{ 0 }, T{ 0 };
vector<vector<bool>> edges(MAX, vector<bool>(MAX, false));
vector<int> order(MAX, 0);
vector<int> degree(MAX, -1);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> T;

    for (int i{ 0 }; i < T; ++i)
    {
        cin >> N;

        edges = vector<vector<bool>>(MAX, vector<bool>(MAX, false));
        order = vector<int>(MAX, 0);
        degree = vector<int>(MAX, -1);

        queue<int> myQ;

        for (int i{ 1 }; i <= N; ++i)
        {
            int input;
            cin >> input;

            order[input] = i;

            degree[input] = i - 1;

            for (int j{ 1 }; j <= N; ++j)
            {
                if (input == j)
                    continue;

                if (degree[j] != -1)
                    continue;

                edges[input][j] = true;
            }
        }

        cin >> M;

        for (int i{ 0 }; i < M; ++i)
        {
            int src{ 0 }, dst{ 0 };
            cin >> src >> dst;

            if (order[src] < order[dst])
            {
                edges[src][dst] = false;
                edges[dst][src] = true;

                ++degree[src];
                --degree[dst];
            }
            else
            {
                edges[dst][src] = false;
                edges[src][dst] = true;

                ++degree[dst];
                --degree[src];
            }
        }

        for (int i{ 1 }; i <= N; ++i)
        {
            if (degree[i] == 0)
            {
                myQ.push(i);
                --degree[i];
            }
        }

        bool isValid{ true };
        vector<int> result;

        while (true)
        {
            if (myQ.empty())
            {
                break;
            }

            auto cur = myQ.front();
            myQ.pop();

            if (myQ.size() > 0)
            {
                isValid = false;
                break;
            }

            result.push_back(cur);

            for (int i{ 1 }; i <= N; ++i)
            {
                if (edges[cur][i] == true)
                    --degree[i];

                if (degree[i] == 0)
                {
                    --degree[i];
                    myQ.push(i);
                }
            }
        }

        if (isValid == false)
        {
            cout << '?' << endl;
        }
        else if (result.size() != N)
        {
            cout << "IMPOSSIBLE" << endl;
        }
        else
        {
            for (auto& num : result)
            {
                cout << num << " ";
            }

            if (i != T - 1)
                cout << endl;
        }
    }

    return 0;
}