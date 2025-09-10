#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define endl '\n'
using namespace std;

#define MAX 100'005

vector<int> lamppost_pos(MAX + 5, 0);
vector<int> dist(MAX + 5, 0);
int N{ 0 }, M{ 0 };

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;

	for (int i{ 0 }; i < M; ++i)
	{
		cin >> lamppost_pos[i];
	}

	for (int i{ 0 }; i < M; ++i)
	{
		if (i == 0)
		{
			if (M == 1)
				dist[i] = max(lamppost_pos[i] - 0, N - lamppost_pos[i]);
			else
				dist[i] = lamppost_pos[i] - 0;

			continue;
		}

		if (i == M - 1)
		{
			dist[i] = max(N - lamppost_pos[i], lamppost_pos[i] - (lamppost_pos[i - 1] + dist[i - 1]));

			continue;
		}

		dist[i] = max(lamppost_pos[i] - (lamppost_pos[i - 1] + dist[i - 1]), (int)ceil((double)(lamppost_pos[i + 1] - lamppost_pos[i]) / (double)2));
	}

	sort(dist.begin(), dist.begin() + M, greater<int>());

	cout << dist[0];

	return 0;
}