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

#define MAX 55

int N{ 0 }, M{ 0 }, total{ INF };
vector<vector<int>> distances(MAX, vector<int>(MAX, INF));
vector<pair<int, int>> chickens;
vector<pair<int, int>> house;

void func(int idx, int counting, vector<vector<int>>& _distances)
{
    if (idx >= chickens.size() || counting >= M)
        return;

    vector<vector<int>> tempDistance = _distances;
    auto chicken = chickens[idx];

    func(idx + 1, counting, tempDistance);

    int result{ 0 };

    for (int i{ 0 }; i < house.size(); ++i)
    {
        int dist = abs(house[i].first - chicken.first) + abs(house[i].second - chicken.second);

        if (dist < tempDistance[house[i].first][house[i].second])
        {
            tempDistance[house[i].first][house[i].second] = dist;
        }

        result += tempDistance[house[i].first][house[i].second];
    }

    total = min(total, result);

    func(idx + 1, counting + 1, tempDistance);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    for (int i{ 0 }; i < N; ++i)
    {
        for (int j{ 0 }; j < N; ++j)
        {
            int input{ 0 };
            cin >> input;

            if (input == 2)
                chickens.push_back({ i,j });
            else if (input == 1)
                house.push_back({ i,j });
        }
    }

    func(0, 0, distances);

    cout << total;

    return 0;
}