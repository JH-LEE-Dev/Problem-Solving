#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 };

    cin >> N;

    if (N % 2 == 0)
    {
        cout << "CY";
    }
    else
    {
        cout << "SK";
    }

    return 0;
}