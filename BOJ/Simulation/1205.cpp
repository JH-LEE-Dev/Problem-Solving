#include <iostream>
#include <vector>
#include <algorithm>

#define endl '\n'
using namespace std;

vector<int> score(55, 0);
vector<int> order(55, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, newScore{ 0 }, P{ 0 }, newOrder{ 1 };

	cin >> N >> newScore >> P;

	if (N != 0)
	{
		for (int i{ 0 }; i < N; ++i)
		{
			cin >> score[i];
		}

		sort(score.begin(), score.begin() + N, greater<int>());

		order[0] = 1;

		if (newScore > score[0])
		{
			cout << 1;
			return 0;
		}

		for (int i{ 0 }; i < N; ++i)
		{
			if (score[i] > newScore)
			{
				++newOrder;
			}
		}

		if (score[N - 1] >= newScore && N == P)
		{
			cout << -1;
		}
		else
		{
			cout << newOrder;
		}
	}
	else
	{
		cout << 1;
	}

	return 0;
}