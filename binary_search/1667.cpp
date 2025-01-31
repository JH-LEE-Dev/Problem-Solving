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
#include <bitset>
#include <iomanip>

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()

int N{ 0 }, S{ 0 }, A{ 0 }, B{ 0 }, X{ 0 }, Y{ 0 };
set<pair<int, int>> fenc_coord;

void solve()
{
    fenc_coord.insert({ S, 0 });

    for (int i = 1; i <= N; ++i)
    {
        cin >> A >> B;
        X = INF, Y = INF;

        auto it = fenc_coord.lower_bound({ A, 0 });

        //begin이나 end가 아니라면, set에서 앞 뒤 원소 둘 다 비교해서 가장 짧은 경로를 채택한다.
        if (it != fenc_coord.end())
            X = min(X, it->second + abs(it->first - A));

        if (it != fenc_coord.begin())
        {
            --it;
            X = min(X, it->second + abs(it->first - A));
        }

        it = fenc_coord.lower_bound({ B, 0 });

        if (it != fenc_coord.end())
            Y = min(Y, it->second + abs(it->first - B));

        if (it != fenc_coord.begin())
        {
            --it;
            Y = min(Y, it->second + abs(it->first - B));
        }

        //A B 사이에 있는 모든 원소들을 다 삭제한다.
        //즉, 이전 펜스들에서 현재 펜스로 낙하하여 A와 B로 각각 이동한 상태이다. 그러면 떨어지기 이전의 좌표들은 필요가 없다.
        //왜냐하면 A와 B사이에 있는 좌표들은 반드시 현재 펜스로 떨어지기 때문에, 현재 펜스의 A,B 경우로 바꾸면 된다.
        //만약 A,B 사이에 있지 않은 좌표들은 현재 펜스를 지나치고 낙하할 수 있기 때문에 지우면 안된다.
        //즉 A와 B 사이의 모든 경우를 지워버린다.
        fenc_coord.erase(fenc_coord.lower_bound({ A, -INF }), fenc_coord.lower_bound({ B, INF }));
        fenc_coord.insert({ A, X });
        fenc_coord.insert({ B, Y });
    }

    //마지막 펜스까지 평가했으면, 0에 가장 가까이 간 경우를 찾는다.
    auto it = fenc_coord.lower_bound({ 0, 0 });

    X = INF;

    //위 로직과 마찬가지로 앞 뒤 경우와 비교하여 가장 가까운 경우를 찾는다.
    //예를 들어 st의 상태가 {-2,3}, {1,5} 이렇게 되어 있으면, 0에 가장 가까운 두 경우가 생기는데,
    //두 경우 중에서 가장 거리가 짧은 놈을 고를 수 있어야 하기 때문이다.
    if (it != fenc_coord.end())
        X = min(X, it->second + abs(it->first));

    if (it != fenc_coord.begin())
    {
        --it;
        X = min(X, it->second + abs(it->first));
    }

    cout << X;
}

void input()
{
    cin >> N >> S;
}

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}