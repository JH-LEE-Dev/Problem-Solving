#include <iostream>
#include <vector>
#include <limits>
#define endl '\n'
using namespace std;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int a;
    cin >> a;
    int cnt = 0;

    while (a >= 0)
    {
        if (a % 5 == 0)
        {
            cnt += a / 5;
            cout << cnt;
            return 0;
        }

        a -= 3;
        cnt++;
    }

    cout << -1;

    return 0;
}