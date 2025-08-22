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

//익은 토마토 배열
vector<int> riped;

//변경 사항 배열
vector<vector<pair<int, int>>> changes(MAX, vector<pair<int, int>>());

//거리 배열
vector<int> dist(MAX, INF);

//변경 사항이 발생하는 시간을 저장하는 배열
vector<int> ripedTime;

//BFS에서 현재까지 발생한 변경 사항의 인덱스
int ripedTime_Idx{ -1 };

//그래프
//unordered_set을 사용한다면, 해시 충돌로 인해서 rehashing과 O(N)연산이 자주 발생하여 시간 초과가 나는 것으로 보임.
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

		//중복을 제거하기 위해서 이전 변경 사항의 발생 시간과 다를 때만 push
		if (i != 0 && ripedTime.back() != t)
			ripedTime.push_back(t);
	}
}

//변경 사항을 적용하는 함수
void ripedChange(int curDist, queue<vertex>& q)
{
	//마지막 변경 사항까지 발생했다면 리턴.
	if (ripedTime_Idx >= (int)ripedTime.size() - 1)
		return;

	//BFS에서 현재 처리되고 있는 시간이 다음 변경 사항에 도달했다면, 현재 변경 사항 인덱스를 증가.
	if (curDist >= ripedTime[ripedTime_Idx + 1])
	{
		++ripedTime_Idx;
	}
	else
		return;

	auto curTime{ curDist };

	//현재 시간 curTime에 대해서 발생한 모든 변경 사항을 적용.
	for (int i{ 0 }; i < changes[curTime].size(); ++i)
	{
		//변경 사항의 정보.
		auto curState{ changes[curTime][i] };

		//만약 간선이 존재하지 않는다면,
		if (edges[curState.first].find(curState.second) == edges[curState.first].end())
		{
			//간선을 생성
			edges[curState.first].insert(curState.second);
			edges[curState.second].insert(curState.first);

			//두 정점 모두 거리가 업데이트되지 않았거나, 모두 거리가 설정된 상태이면 다음 변경 사항으로 진행.(두 토마토 모두 익었거나, 두 토마토 모두 익지 않았거나)
			if ((dist[curState.first] != INF && dist[curState.second] != INF) || (dist[curState.first] == INF && dist[curState.second] == INF))
			{
				continue;
			}
			else
			{
				//익은 토마토는 다시 전파되어야 하므로 q에 삽입.
				if (dist[curState.first] != INF)
				{
					//익은 토마토는 기록된 거리에 상관 없이 탐색할 수 있어야 하므로 true로 저장.
					q.push({ curState.first,curTime,true });
				}
				else
				{
					q.push({ curState.second,curTime,true });
				}
			}
		}
		//만약 간선이 존재한다면,
		else
		{
			//간선을 제거.
			edges[curState.second].erase(curState.first);
			edges[curState.first].erase(curState.second);
		}
	}
}

void bfs()
{
	queue<vertex> q;

	//익은 토마토를 deque에 삽입.
	for (int i{ 0 }; i < riped.size(); ++i)
	{
		q.push({ riped[i],0,false });
		dist[riped[i]] = 0;
	}

	while (true)
	{
		//만약 deque가 비었다면,
		if (q.empty())
		{
			//현재 모든 변경 사항이 적용된 상태라면 종료.
			if (ripedTime_Idx >= (int)ripedTime.size() - 1)
				break;

			//다음 변경 사항에 해당하는 시간으로 이동.
			int curTime{ ripedTime[ripedTime_Idx + 1] };

			//변경 사항 적용.
			ripedChange(curTime, q);

			continue;
		}

		auto cur{ q.front() };
		q.pop();

		auto src{ get<0>(cur) };
		auto curDist{ get<1>(cur) };
		auto changed{ get<2>(cur) };

		//changed는 익은 토마토가 다시 전파되기 위해서 필요.
		//만약 changed가 true라면 익은 토마토로부터 새로운 간선이 생성되었으므로 다시 방문할 수 있어야 함.
		if (dist[src] < curDist && changed == false)
			continue;

		//현재 흐른 시간에 따라서 변경 사항을 적용.
		ripedChange(curDist, q);

		//인접 정점 방문.
		for (auto& dst : edges[src])
		{
			auto newDist{ curDist + 1 };

			if (dist[dst] > newDist)
			{
				dist[dst] = newDist;
				q.push({ dst,newDist,false });
			}

			//안해도 됨, 하지만 해도 틀리지는 않음 좀 더 느려짐
			//edges[dst].erase(src);
		}

		//정점 하나가 가진 간선이 20만 개일 경우에, 만약 정점 V의 간선을 삭제하는 연산이 20만 번이 존재한다면
		//O(N^2)임.(N! == 20만 개의 간선을 하나씩 제거하는 경우)
		//따라서 이미 사용된 간선은 더 이상 필요가 없음( 두 토마토를 잇는 간선이 사용되었다면 두 토마토는 모두 익었기 때문에 없애도 됨)
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