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
using vertex = tuple<int, int, int>;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 1'001

struct state
{
	int r;
	int c;
	int dir;
	bool smell;

	state(int _r, int _c, int _dir, bool _smell) :
		r(_r), c(_c), dir(_dir), smell(_smell)
	{
	}

	int pack() const
	{
		return (smell ? 1 : 0)
			+ 2 * (dir)
			+10 * c
			+ 10000 * r;
	}

	static state unpack(int x)
	{
		bool smell = x % 2;
		int dir = ((x / 2) % 5);
		int c = (x / 10) % 1000;
		int r = (x / 10000) % 1000;

		return state(r, c, dir, smell);
	}
};

int N, M;
vector<vector<int>> table(MAX, vector<int>(MAX, 0));
vector<int> dist(10'000'000, INF);

vector<int> dir_row{ 0,0,1,-1 };
vector<int> dir_col{ 1,-1,0,0 };

int result{ INF };

bool isValid(int r, int c)
{
	if (r >= N || r < 0 || c >= M || c < 0)
		return false;
	else
		return true;
}

void input()
{
	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			cin >> table[i][j];
		}
	}
}

void dijkstra()
{
	priority_queue<vertex, vector<vertex>, greater<vertex>> pq;
	state initialState{ 0,0,table[0][0],false };

	pq.push({ 0,initialState.pack(),table[0][0] });
	dist[initialState.pack()] = 0;

	while (pq.empty() == false)
	{
		auto cur{ pq.top() };
		pq.pop();

		auto curPacked{ get<1>(cur) };
		auto curDist{ get<0>(cur) };
		auto curColor{ get<2>(cur) };
		state curState{ state::unpack(curPacked) };

		auto r{ curState.r };
		auto c{ curState.c };
		auto curDir{ curState.dir };
		auto curSmell{ curState.smell };

		if (dist[curPacked] < curDist)
			continue;

		if (curColor == 4 && table[r][c] != 4)
			curColor = table[r][c];

		if (r == N - 1 && c == M - 1)
		{
			result = curDist;
			return;
		}

		for (int i{ 0 }; i < 4; ++i)
		{
			auto nR{ r + dir_row[i] };
			auto nC{ c + dir_col[i] };
			auto newDist{ curDist + 1 };
			auto newSmell{ curSmell };

			//table[r][c]를 사용하지 않고 curColor를 pq에 넣어 사용하는 이유는
			//미끄러지다 멈춘 경우 table[r][c]는 4이지만, 현재 미끄러지는 경우는 아니므로 4번 타일로 취급해서는 안된다.
			//따라서 따로 색을 저장하여 사용한다. (미끄러지다 멈춘 경우는 색깔을 1로 설정하여 더 이상 미끄러지지 않도록 함)
			if (curColor != 4)
			{
				if (isValid(nR, nC) == false || table[nR][nC] == 0)
					continue;
			}
			else
			{
				if (i == curDir)
				{
					if (isValid(nR, nC) == false || table[nR][nC] == 0 || (curSmell == false && table[nR][nC] == 3))
					{
						state newState{ r,c,i,curSmell };

						//미끄러지다 멈춘 경우는 color를 1로 설정한다. (크게 의미 없음)
						//또한 dist pruning을 제거하여 현재 타일에서 다시 경로가 뻗어나갈 수 있게 한다.
						//dist pruning이 존재한다면 dist[newState] > newDist가 통과할 수 없으므로 제한된다.
						dist[newState.pack()] = curDist;
						pq.push({ curDist,newState.pack(),1 });
					}
					else
					{
						if (table[nR][nC] == 2)
							curSmell = true;

						state newState{ nR,nC,i,curSmell };

						if (dist[newState.pack()] > newDist)
						{
							dist[newState.pack()] = newDist;
							pq.push({ newDist,newState.pack(),4 });
						}
					}
					break;
				}

				continue;
			}

			//3번 타일은 orange smell이 true일 때만 통과 가능.
			if (table[nR][nC] == 3 && curSmell == false)
				continue;

			//2번 타일에서 orange smell = true로 설정.
			if (table[nR][nC] == 2)
				newSmell = true;

			//4번 타일은 orange smell이 false로 바뀜
			if (table[nR][nC] == 4)
				newSmell = false;

			state newState{ nR,nC,i,newSmell };

			if (dist[newState.pack()] > newDist)
			{
				dist[newState.pack()] = newDist;
				pq.push({ newDist,newState.pack(),table[nR][nC] });
			}
		}
	}
}

void solve()
{
	dijkstra();

	if (result == INF)
		cout << -1;
	else
		cout << result;
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