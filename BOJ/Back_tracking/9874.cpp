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
vector<P> w;                // 1-indexed 로 쓸 예정
int nextRight[13]{ 0 };          // i번 웜홀의 오른쪽 이웃(같은 y, x가 더 크고 가장 가까운)
int mate[13]{ 0 };               // 짝 정보
bool used[13]{ 0 };

bool hasCycle()
{
    // 모든 시작점에서 검사
    for (int start = 1; start <= N; ++start)
    {
        int pos = start;
        // 최대 N번 이동: N번을 넘도록 멈추지 않으면 cycle
        // N번을 다 돌 동안 break 없이 진행되면 루프
        // (즉, 위 for가 정상 종료했다면 루프)
        if (true)
        {
            bool stuck = true;
            for (int step = 0; step < N; ++step)
            {
                int m = mate[pos];
                int nr = nextRight[m];
                if (nr == 0) { stuck = false; break; }// 오른쪽 이웃이 없으면 종료
                pos = nr; // 다음 위치
            }

            if (stuck)
                return true;
        }
    }
    return false;
}

int dfs()
{
    // 첫 번째 미매칭 웜홀 찾기
    int i = 1;

    while (i <= N && mate[i] != 0)
        ++i;

    if (i > N)
    {
        // 모든 짝짓기 완료 → 루프 여부 판정
        return hasCycle() ? 1 : 0;
    }

    int cnt = 0;

    // i를 j와 짝짓기
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
