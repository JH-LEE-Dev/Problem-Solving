#include <iostream>
#include <vector>
#include <cmath>

#define endl '\n'
using namespace std;


int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int H{ 0 }, W{ 0 }, N{ 0 }, M{ 0 };

    cin >> H >> W >> N >> M;

    int row = ceil((double)H / (N + 1.0));
    int col = ceil((double)W / (M + 1.0));

    cout << row * col;

    return 0;
}