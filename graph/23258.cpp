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

#define endl '\n'
#define INF numeric_limits<int>::max()/2
using namespace std;
#define MAX 301

vector<vector<int>> weight(MAX, vector<int>(MAX, INF));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(MAX, INF)));

int N{ 0 }, T{ 0 };

void floydWarshall()
{
	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			dist[i][j][0] = weight[i][j];
		}

		dist[i][i][0] = 0;
	}

	//�� ������, C ������ �����鸸 �湮�ؾ� �Ѵ�.
	//dist[left][right][middle]�� �ǹ̴� left���� right�� �� ���� middle���� ������� �� �ִ� �Ÿ��̴�.
	//for loop���� middle�� 1���� N���� ���������� ����ϹǷ� middle-1 ���� �������� ���� ���Ѵ�. 

	//�Ϲ����� Floyd - Warshall �˰���� ���ϴ� ���� ���̴� ����. dist[left][right][N]�� ��찡 left���� right�� ���� ������ �ִ� �Ÿ��̴�.
	//������ C������ �����鸸 �湮���� ���� �Ÿ��� �˾ƾ� �ϹǷ�(left,right�� C �̻��� ���� ���ܵȴ�. �� �߰� ��θ� C �����̸� �ȴ�.)
	//3���� DP�� ����Ѵ�.
	for (int middle{ 1 }; middle <= N; ++middle)
	{
		for (int left{ 1 }; left <= N; ++left)
		{
			for (int right{ 1 }; right <= N; ++right)
			{
				dist[left][right][middle] = min(dist[left][right][middle - 1], dist[left][middle][middle - 1] + dist[middle][right][middle - 1]);
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> T;

	for (int i{ 1 }; i <= N; ++i)
	{
		for (int j{ 1 }; j <= N; ++j)
		{
			cin >> weight[i][j];

			if (weight[i][j] == 0)
				weight[i][j] = INF;
		}
	}

	floydWarshall();

	while (T != 0)
	{
		int C{ 0 }, start{ 0 }, goal{ 0 };
		cin >> C >> start >> goal;

		if (dist[start][goal][C - 1] != INF)
			cout << dist[start][goal][C - 1] << endl;
		else
			cout << -1 << endl;

		--T;
	}

	return 0;
}