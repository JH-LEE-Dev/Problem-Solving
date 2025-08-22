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

int N{ 0 };

//min heap
priority_queue<int, vector<int>, greater<int>> minHeap;

//max heap
priority_queue<int> maxHeap;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    int median{ 0 };

    for (int i{ 0 }; i < N; ++i)
    {
        int input;
        cin >> input;

        if (i == 0)
        {
            minHeap.push(input);
            cout << minHeap.top() << endl;
            median = minHeap.top();
            continue;
        }

        if (maxHeap.size() > minHeap.size())
        {
            if (input < median)
            {
                int maxVal = maxHeap.top();
                maxHeap.pop();

                maxHeap.push(input);
                minHeap.push(maxVal);
            }
            else
            {
                minHeap.push(input);
            }
        }
        else if (maxHeap.size() < minHeap.size())
        {
            if (input > median)
            {
                int minVal = minHeap.top();
                minHeap.pop();

                minHeap.push(input);
                maxHeap.push(minVal);
            }
            else
            {
                maxHeap.push(input);
            }
        }
        else
        {
            if (input > median)
            {
                minHeap.push(input);
            }
            else
            {
                maxHeap.push(input);
            }
        }

        if (maxHeap.size() == minHeap.size())
        {
            median = maxHeap.top();

            cout << median << endl;

            continue;
        }

        if (maxHeap.size() > minHeap.size())
        {
            median = maxHeap.top();
        }
        else
        {
            median = minHeap.top();
        }

        cout << median << endl;
    }

    return 0;
}