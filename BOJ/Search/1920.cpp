#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define endl '\n'

vector<int> arr(100005, 0);
set<int> arr2;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, M{ 0 };

    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        int input{ 0 };
        cin >> input;

        arr2.insert(input);
    }

    cin >> M;

    for (int i = 0; i < M; ++i)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < M; ++i)
    {
        if (arr2.find(arr[i]) != arr2.end())
        {
            cout << '1' << endl;
        }
        else
        {
            cout << '0' << endl;
        }
    }

    return 0;
}