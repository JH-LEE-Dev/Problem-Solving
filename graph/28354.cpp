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
using vertex = tuple<int, int, bool>;

#define MAX 200'001
#define endl '\n'
#define INF numeric_limits<int>::max()

int N{ 0 }, M{ 0 }, K{ 0 }, Q{ 0 };

//���� �丶�� �迭
vector<int> riped;

//���� ���� �迭
vector<vector<pair<int, int>>> changes(MAX, vector<pair<int, int>>());

//�Ÿ� �迭
vector<int> dist(MAX, INF);

//���� ������ �߻��ϴ� �ð��� �����ϴ� �迭
vector<int> ripedTime;

//BFS���� ������� �߻��� ���� ������ �ε���
int ripedTime_Idx{ -1 };

//�׷���
//unordered_set�� ����Ѵٸ�, �ؽ� �浹�� ���ؼ� rehashing�� O(N)������ ���� �߻��Ͽ� �ð� �ʰ��� ���� ������ ����.
vector<set<int>> edges(MAX, set<int>());

void input()
{
	cin >> N >> M >> K >> Q;

	for (int i{ 0 }; i < M; ++i)
	{
		int src{ 0 }, dst{ 0 };
		cin >> src >> dst;

		edges[src].insert(dst);
		edges[dst].insert(src);
	}

	for (int i{ 0 }; i < K; ++i)
	{
		int input{ 0 };
		cin >> input;

		riped.push_back(input);
	}

	for (int i{ 0 }; i < Q; ++i)
	{
		int t{ 0 }, src{ 0 }, dst{ 0 };
		cin >> t >> src >> dst;

		changes[t].push_back({ src,dst });

		if (i == 0)
			ripedTime.push_back(t);

		//�ߺ��� �����ϱ� ���ؼ� ���� ���� ������ �߻� �ð��� �ٸ� ���� push
		if (i != 0 && ripedTime.back() != t)
			ripedTime.push_back(t);
	}
}

//���� ������ �����ϴ� �Լ�
void ripedChange(int curDist, queue<vertex>& q)
{
	//������ ���� ���ױ��� �߻��ߴٸ� ����.
	if (ripedTime_Idx >= (int)ripedTime.size() - 1)
		return;

	//BFS���� ���� ó���ǰ� �ִ� �ð��� ���� ���� ���׿� �����ߴٸ�, ���� ���� ���� �ε����� ����.
	if (curDist >= ripedTime[ripedTime_Idx + 1])
	{
		++ripedTime_Idx;
	}
	else
		return;

	auto curTime{ curDist };

	//���� �ð� curTime�� ���ؼ� �߻��� ��� ���� ������ ����.
	for (int i{ 0 }; i < changes[curTime].size(); ++i)
	{
		//���� ������ ����.
		auto curState{ changes[curTime][i] };

		//���� ������ �������� �ʴ´ٸ�,
		if (edges[curState.first].find(curState.second) == edges[curState.first].end())
		{
			//������ ����
			edges[curState.first].insert(curState.second);
			edges[curState.second].insert(curState.first);

			//�� ���� ��� �Ÿ��� ������Ʈ���� �ʾҰų�, ��� �Ÿ��� ������ �����̸� ���� ���� �������� ����.(�� �丶�� ��� �;��ų�, �� �丶�� ��� ���� �ʾҰų�)
			if ((dist[curState.first] != INF && dist[curState.second] != INF) || (dist[curState.first] == INF && dist[curState.second] == INF))
			{
				continue;
			}
			else
			{
				//���� �丶��� �ٽ� ���ĵǾ�� �ϹǷ� q�� ����.
				if (dist[curState.first] != INF)
				{
					//���� �丶��� ��ϵ� �Ÿ��� ��� ���� Ž���� �� �־�� �ϹǷ� true�� ����.
					q.push({ curState.first,curTime,true });
				}
				else
				{
					q.push({ curState.second,curTime,true });
				}
			}
		}
		//���� ������ �����Ѵٸ�,
		else
		{
			//������ ����.
			edges[curState.second].erase(curState.first);
			edges[curState.first].erase(curState.second);
		}
	}
}

void bfs()
{
	queue<vertex> q;

	//���� �丶�並 deque�� ����.
	for (int i{ 0 }; i < riped.size(); ++i)
	{
		q.push({ riped[i],0,false });
		dist[riped[i]] = 0;
	}

	while (true)
	{
		//���� deque�� ����ٸ�,
		if (q.empty())
		{
			//���� ��� ���� ������ ����� ���¶�� ����.
			if (ripedTime_Idx >= (int)ripedTime.size() - 1)
				break;

			//���� ���� ���׿� �ش��ϴ� �ð����� �̵�.
			int curTime{ ripedTime[ripedTime_Idx + 1] };

			//���� ���� ����.
			ripedChange(curTime, q);

			continue;
		}

		auto cur{ q.front() };
		q.pop();

		auto src{ get<0>(cur) };
		auto curDist{ get<1>(cur) };
		auto changed{ get<2>(cur) };

		//changed�� ���� �丶�䰡 �ٽ� ���ĵǱ� ���ؼ� �ʿ�.
		//���� changed�� true��� ���� �丶��κ��� ���ο� ������ �����Ǿ����Ƿ� �ٽ� �湮�� �� �־�� ��.
		if (dist[src] < curDist && changed == false)
			continue;

		//���� �帥 �ð��� ���� ���� ������ ����.
		ripedChange(curDist, q);

		//���� ���� �湮.
		for (auto& dst : edges[src])
		{
			auto newDist{ curDist + 1 };

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				q.push({ dst,newDist,false });
			}

			//���ص� ��, ������ �ص� Ʋ������ ���� �� �� ������
			//edges[dst].erase(src);
		}

		//���� �ϳ��� ���� ������ 20�� ���� ��쿡, ���� ���� V�� ������ �����ϴ� ������ 20�� ���� �����Ѵٸ�
		//O(N^2)��.(N! == 20�� ���� ������ �ϳ��� �����ϴ� ���)
		//���� �̹� ���� ������ �� �̻� �ʿ䰡 ����( �� �丶�並 �մ� ������ ���Ǿ��ٸ� �� �丶��� ��� �;��� ������ ���ֵ� ��)
		edges[src].clear();
	}
}

void solve()
{
	bfs();

	for (int i{ 1 }; i <= N; ++i)
	{
		if (dist[i] == INF)
			cout << -1 << ' ';
		else
			cout << dist[i] << ' ';
	}
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