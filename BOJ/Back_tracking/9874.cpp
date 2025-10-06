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

struct P { int x, y; };

int N;
vector<P> w;                // 1-indexed �� �� ����
int nextRight[13]{ 0 };          // i�� ��Ȧ�� ������ �̿�(���� y, x�� �� ũ�� ���� �����)
int mate[13]{ 0 };               // ¦ ����
bool used[13]{ 0 };

bool hasCycle()
{
    // ��� ���������� �˻�
    for (int start = 1; start <= N; ++start)
    {
        int pos = start;
        // �ִ� N�� �̵�: N���� �ѵ��� ������ ������ cycle
        // N���� �� �� ���� break ���� ����Ǹ� ����
        // (��, �� for�� ���� �����ߴٸ� ����)
        if (true)
        {
            bool stuck = true;
            for (int step = 0; step < N; ++step)
            {
                int m = mate[pos];
                int nr = nextRight[m];
                if (nr == 0) { stuck = false; break; }// ������ �̿��� ������ ����
                pos = nr; // ���� ��ġ
            }

            if (stuck)
                return true;
        }
    }
    return false;
}

int dfs()
{
    // ù ��° �̸�Ī ��Ȧ ã��
    int i = 1;

    while (i <= N && mate[i] != 0)
        ++i;

    if (i > N)
    {
        // ��� ¦���� �Ϸ� �� ���� ���� ����
        return hasCycle() ? 1 : 0;
    }

    int cnt = 0;

    // i�� j�� ¦����
    for (int j = i + 1; j <= N; ++j)
    {
        if (mate[j] == 0)
        {
            mate[i] = j; mate[j] = i;
            cnt += dfs();
            mate[i] = mate[j] = 0;
        }
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    w.resize(N + 1);
    for (int i = 1; i <= N; ++i) cin >> w[i].x >> w[i].y;

    for (int i = 1; i <= N; ++i)
    {
        int best = 0;
        for (int j = 1; j <= N; ++j)
        {
            if (w[i].y == w[j].y && w[j].x > w[i].x)
            {
                if (best == 0 || w[j].x < w[best].x) best = j;
            }
        }

        nextRight[i] = best;
    }

    cout << dfs() << "\n";

    return 0;
}
