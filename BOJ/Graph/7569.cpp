#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

#define endl '\n'
using namespace std;

#define MAX 105
#define DIR_COUNT 6

vector<vector<vector<int>>> tomato(MAX, vector<vector<int>>(MAX, vector<int>(MAX, 0)));
vector<vector<vector<int>>> dist(MAX, vector<vector<int>>(MAX, vector<int>(MAX, 0)));

int M{ 0 }, N{ 0 }, H{ 0 }, result{ -1 };

vector<int> x_dir{ 0,0,1,-1,0,0 };
vector<int> y_dir{ 1,-1,0,0,0,0 };
vector<int> z_dir{ 0,0,0,0,1,-1 };

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> M >> N >> H;
	swap(M, N);

	queue<tuple<int, int, int>> myQ;

	for (int i{ 0 }; i < H; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			for (int k{ 0 }; k < N; ++k)
			{
				cin >> tomato[i][j][k];

				if (tomato[i][j][k] == 1)
				{
					myQ.push(make_tuple(i, j, k));
				}

				if (tomato[i][j][k] == 0)
				{
					dist[i][j][k] = -1;
				}
			}
		}
	}

	while (!myQ.empty())
	{
		auto cur = myQ.front();
		myQ.pop();

		int x{ get<1>(cur) };
		int y{ get<2>(cur) };
		int z{ get<0>(cur) };

		for (int i{ 0 }; i < DIR_COUNT; ++i)
		{
			int new_x{ x + x_dir[i] };
			int new_y{ y + y_dir[i] };
			int new_z{ z + z_dir[i] };

			if (new_x >= 0 && new_x < M && new_y >= 0 && new_y < N && new_z >= 0 && new_z < H)
			{
				if (dist[new_z][new_x][new_y] >= 0)
				{
					continue;
				}
				else
				{
					dist[new_z][new_x][new_y] = dist[z][x][y] + 1;
					myQ.push(make_tuple(new_z, new_x, new_y));
				}
			}
		}
	}

	for (int i{ 0 }; i < H; ++i)
	{
		for (int j{ 0 }; j < M; ++j)
		{
			for (int k{ 0 }; k < N; ++k)
			{
				result = max(dist[i][j][k], result);

				if (dist[i][j][k] == -1)
				{
					cout << -1;
					return 0;
				}
			}
		}
	}

	if (result == 0)
	{
		cout << 0;
		return 0;
	}

	cout << result;

	return 0;
}