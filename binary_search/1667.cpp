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

        //begin�̳� end�� �ƴ϶��, set���� �� �� ���� �� �� ���ؼ� ���� ª�� ��θ� ä���Ѵ�.
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

        //A B ���̿� �ִ� ��� ���ҵ��� �� �����Ѵ�.
        //��, ���� �潺�鿡�� ���� �潺�� �����Ͽ� A�� B�� ���� �̵��� �����̴�. �׷��� �������� ������ ��ǥ���� �ʿ䰡 ����.
        //�ֳ��ϸ� A�� B���̿� �ִ� ��ǥ���� �ݵ�� ���� �潺�� �������� ������, ���� �潺�� A,B ���� �ٲٸ� �ȴ�.
        //���� A,B ���̿� ���� ���� ��ǥ���� ���� �潺�� ����ġ�� ������ �� �ֱ� ������ ����� �ȵȴ�.
        //�� A�� B ������ ��� ��츦 ����������.
        fenc_coord.erase(fenc_coord.lower_bound({ A, -INF }), fenc_coord.lower_bound({ B, INF }));
        fenc_coord.insert({ A, X });
        fenc_coord.insert({ B, Y });
    }

    //������ �潺���� ��������, 0�� ���� ������ �� ��츦 ã�´�.
    auto it = fenc_coord.lower_bound({ 0, 0 });

    X = INF;

    //�� ������ ���������� �� �� ���� ���Ͽ� ���� ����� ��츦 ã�´�.
    //���� ��� st�� ���°� {-2,3}, {1,5} �̷��� �Ǿ� ������, 0�� ���� ����� �� ��찡 ����µ�,
    //�� ��� �߿��� ���� �Ÿ��� ª�� ���� �� �� �־�� �ϱ� �����̴�.
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