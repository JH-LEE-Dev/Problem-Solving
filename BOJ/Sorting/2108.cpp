#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <queue>

#define endl '\n'
using namespace std;

vector<int> arr(500'005, 0);
unordered_map<int, int> count_map;
priority_queue<int, std::vector<int>, std::greater<int>> counting_queue;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    bool duplicate{ false };
    int modeCount{ 0 };
    int mode{ 0 }, median{ 0 }, ave{ 0 }, range{ 0 };

    int N{ 0 };
    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> arr[i];
        ave += arr[i];

        ++count_map[arr[i]];

        if (i == 0)
        {
            counting_queue.push(arr[i]);

            modeCount = count_map[arr[i]];
            mode = arr[i];

            duplicate = false;

            continue;
        }

        if (modeCount <= count_map[arr[i]])
        {
            if (modeCount == count_map[arr[i]])
            {
                counting_queue.push(arr[i]);

                duplicate = true;
            }
            else
            {
                modeCount = count_map[arr[i]];
                mode = arr[i];

                duplicate = false;

                counting_queue = priority_queue<int, std::vector<int>, std::greater<int>>();
                counting_queue.push(arr[i]);
            }
        }
    }

    sort(arr.begin(), arr.begin() + N, less<int>());

    range = arr[N - 1] - arr[0];
    median = arr[(N - 1) / 2];
    ave = (int)round((double)ave / (double)N);

    cout << ave << endl;
    cout << median << endl;

    if (!duplicate)
        cout << mode << endl;
    else
    {
        counting_queue.pop();
        cout << counting_queue.top() << endl;
    }

    cout << range << endl;

    return 0;
}