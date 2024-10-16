#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define endl '\n'
using namespace std;

vector<pair<int, char>> counting(30);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    string  input;
    cin >> input;

    int length = input.length();

    for (int i = 0; i < 26; ++i)
    {
        counting[i].second = char(i + 65);
    }

    for (int i{ 0 }; i < length; ++i)
    {
        int ascii_code = (int)input[i];

        if (ascii_code >= 65 && ascii_code <= 90)
        {
            ++counting[ascii_code - 65].first;
        }
        else
        {
            ++counting[ascii_code - 97].first;
        }
    }

    sort(counting.begin(), counting.end(), [](const pair<int, char>& a, const pair<int, char>& b) {
        return a.first > b.first;
        });

    if (counting[0].first == counting[1].first)
    {
        cout << '?' << endl;
    }
    else
    {
        cout << counting[0].second << endl;
    }

    return 0;
}