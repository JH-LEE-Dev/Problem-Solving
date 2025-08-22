#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    string input;
    string result;
    cin >> input;

    vector<bool>filter(input.size(), true);

    int one_count{ 0 };
    int two_count{ 0 };
    int one_deleteCount{ 0 };
    int two_deleteCount{ 0 };

    for (int i{ 0 }; i < input.size(); ++i)
    {
        if (input[i] == '1')
        {
            ++one_count;
        }
        else
        {
            ++two_count;
        }
    }

    for (int i{ 0 }; i < input.size(); ++i)
    {
        if (one_deleteCount == one_count / 2)
            break;

        if (input[i] == '1')
        {
            filter[i] = false;
            ++one_deleteCount;
        }
    }

    for (int i{ (int)input.size() - 1 }; i >= 0; --i)
    {
        if (two_deleteCount == two_count / 2)
            break;

        if (input[i] == '0')
        {
            filter[i] = false;
            ++two_deleteCount;
        }
    }

    for (int i{ 0 }; i < input.size(); ++i)
    {
        if (filter[i] == true)
        {
            if (input[i] == '1')
                result += '1';
            else
                result += '0';
        }
    }

    cout << result;

    return 0;
}