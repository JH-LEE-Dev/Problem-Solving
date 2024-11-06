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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;
#define MAX 1'005

vector<vector<int>> DP(MAX, vector<int>(MAX, -1));
vector<pair<int, int>> job(MAX);
int N{ 0 }, W{ 0 };

int getDist(int curRow, int curCol, int row, int col)
{
    return abs(row - curRow) + abs(col - curCol);
}

int func(int car_1, int car_2)
{
    if (car_1 == W || car_2 == W)
        return 0;

    if (DP[car_1][car_2] != -1)
        return DP[car_1][car_2];

    int nextJob = max(car_1, car_2) + 1;

    int dist_1{ 0 };
    int dist_2{ 0 };

    if (car_1 == 0)
        dist_1 = getDist(1, 1, job[nextJob].first, job[nextJob].second);
    else
        dist_1 = getDist(job[car_1].first, job[car_1].second, job[nextJob].first, job[nextJob].second);

    if (car_2 == 0)
        dist_2 = getDist(N, N, job[nextJob].first, job[nextJob].second);
    else
        dist_2 = getDist(job[car_2].first, job[car_2].second, job[nextJob].first, job[nextJob].second);

    int Result_1 = dist_1 + func(nextJob, car_2);
    int Result_2 = dist_2 + func(car_1, nextJob);

    DP[car_1][car_2] = min(Result_1, Result_2);

    return DP[car_1][car_2];
}

void tracePath(int car_1, int car_2)
{
    if (car_1 == W || car_2 == W)
        return;

    int nextJob = max(car_1, car_2) + 1;

    int dist_1{ 0 };
    int dist_2{ 0 };

    if (car_1 == 0)
        dist_1 = getDist(1, 1, job[nextJob].first, job[nextJob].second);
    else
        dist_1 = getDist(job[car_1].first, job[car_1].second, job[nextJob].first, job[nextJob].second);

    if (car_2 == 0)
        dist_2 = getDist(N, N, job[nextJob].first, job[nextJob].second);
    else
        dist_2 = getDist(job[car_2].first, job[car_2].second, job[nextJob].first, job[nextJob].second);

    int Result_1 = dist_1 + DP[nextJob][car_2];
    int Result_2 = dist_2 + DP[car_1][nextJob];

    if (Result_1 < Result_2)
    {
        cout << 1 << endl;
        tracePath(nextJob, car_2);
    }
    else
    {
        cout << 2 << endl;
        tracePath(car_1, nextJob);
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> W;

    for (int i{ 1 }; i <= W; ++i)
    {
        int row{ 0 }, col{ 0 };
        cin >> row >> col;
        job[i] = { row,col };
    }

    cout << func(0, 0) << endl;
    tracePath(0, 0);

    return 0;
}