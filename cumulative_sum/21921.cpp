#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

#define MAX 250'005

vector<int> DP(MAX, 0);
vector<int> visitors(MAX, 0);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, M{ 0 };
    cin >> N >> M;

    int maxVisitors{ 0 };
    int counting{ 1 };
    int sum{ 0 };
    int sumCount{ 0 };

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> visitors[i];

        if (sumCount < M)
        {
            sum += visitors[i];
            ++sumCount;
        }
    }
    maxVisitors = sum;

    for (int i{ M }; i < N; ++i)
    {
        int tempSum{ sum };

        tempSum -= visitors[i - M];

        tempSum += visitors[i];

        sum = tempSum;

        if (maxVisitors <= tempSum)
        {
            if (maxVisitors == tempSum)
            {
                ++counting;
            }
            else
            {
                maxVisitors = tempSum;
                counting = 1;
            }
        }
    }

    if (maxVisitors == 0)
        cout << "SAD";
    else
    {
        cout << maxVisitors << endl;
        cout << counting << endl;
    }

    return 0;
}