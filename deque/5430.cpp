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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

int N{ 0 };
int T{ 0 };

void func(deque<int>& arr, string order)
{
    bool cursor{ false };

    for (int i{ 0 }; i < order.length(); ++i)
    {
        if (order[i] == 'R')
        {
            cursor = !cursor;
        }

        if (order[i] == 'D')
        {
            if (arr.empty())
            {
                cout << "error" << endl;
                return;
            }

            if (cursor == false)
            {
                arr.pop_front();
            }
            else
            {
                arr.pop_back();
            }
        }
    }

    if (arr.empty())
    {
        cout << "[]" << endl;
        return;
    }

    if (cursor == false)
    {
        cout << '[';
        for (int i{ 0 }; i < arr.size(); ++i)
        {
            if (i != arr.size() - 1)
                cout << arr[i] << ',';
            else
                cout << arr[i] << ']';
        }
    }
    else
    {
        cout << '[';
        for (int i{ (int)arr.size() - 1 }; i >= 0; --i)
        {
            if (i != 0)
                cout << arr[i] << ',';
            else
                cout << arr[i] << ']';
        }
    }

    cout << endl;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> T;

    while (T != 0)
    {
        deque<int> arr;

        string order;
        cin >> order;

        cin >> N;

        string input;
        cin >> input;

        string number = "";

        for (int i{ 0 }; i < input.length(); ++i)
        {
            if (input[i] != '[' && input[i] != ']' && input[i] != ',')
            {
                number += input[i];
            }
            else
            {
                if (number != "")
                {
                    arr.push_back(stoi(number));
                    number = "";
                }
            }
        }

        func(arr, order);

        --T;
    }

    return 0;
}