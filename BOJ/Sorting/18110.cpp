#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define endl '\n'
using namespace std;

vector<int> score(300005, 0);
double alpha = 0.15;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N{ 0 }, drop{ 0 }, total{ 0 };

    cin >> N;

    if (N == 0)
    {
        cout << 0;
        return 0;
    }


    for (int i{ 0 }; i < N; ++i)
    {
        cin >> score[i];
    }

    drop = (int)round((alpha * (double)N));

    sort(score.begin(), score.begin() + N, less<int>());

    for (int i{ drop }; i < N - drop; ++i)
    {
        total += score[i];
    }

    cout << (int)round((double)total / (double)(N - drop * 2));

    return 0;
}