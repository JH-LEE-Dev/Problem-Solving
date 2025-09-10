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
#define MAX 101

int N, L;
vector<vector<int>> Table(MAX, vector<int>(MAX, INF));

void Input()
{
	cin >> N >> L;

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> Table[i][j];
		}
	}
}

void Solve()
{
	int Result{ 2 * N };

	for (int i{ 0 }; i < N; ++i)
	{
		bool bValid{ true };
		int LastStructure{ -1 };

		for (int j{ 0 }; j < N - 1; ++j)
		{
			int Delta{ Table[i][j] - Table[i][j + 1] };

			//높이 차이가 2 이상이면 경사로 설치 불가.
			if (abs(Delta) > 1)
			{
				bValid = false;
				break;
			}

			//오르막
			if (Delta == -1)
			{
				//마지막으로 설치한 경사로와 새로 설치할 경사로가 겹치는지 확인.
				if (j - L + 1 <= LastStructure)
				{
					bValid = false;
					break;
				}

				LastStructure = j;
			}

			//내리막
			if (Delta == 1)
			{
				if (j + L > N - 1)
				{
					bValid = false;
					break;
				}

				for (int k{ 1 }; k < L; ++k)
				{
					if (Table[i][j + k] - Table[i][j + k + 1] != 0)
					{
						bValid = false;
						break;
					}
				}

				LastStructure = j + L;
				j += L - 1;

				if (bValid == false)
					break;
			}
		}

		if (bValid == false)
			--Result;
	}

	for (int i{ 0 }; i < N; ++i)
	{
		bool bValid{ true };
		int LastStructure{ -1 };

		for (int j{ 0 }; j < N - 1; ++j)
		{
			int Delta{ Table[j][i] - Table[j + 1][i] };

			if (abs(Delta) > 1)
			{
				bValid = false;
				break;
			}

			//오르막
			if (Delta == -1)
			{
				if (j - L + 1 <= LastStructure)
				{
					bValid = false;
					break;
				}

				LastStructure = j;
			}

			//내리막
			if (Delta == 1)
			{
				if (j + L > N - 1)
				{
					bValid = false;
					break;
				}

				for (int k{ 1 }; k < L; ++k)
				{
					if (Table[j + k][i] - Table[j + k + 1][i] != 0)
					{
						bValid = false;
						break;
					}
				}

				LastStructure = j + L;
				j += L - 1;

				if (bValid == false)
					break;
			}
		}

		if (bValid == false)
			--Result;
	}

	cout << Result;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}