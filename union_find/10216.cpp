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
#define MAX 3'001

int T, N;
vector<tuple<int, int, int>> Spots;
vector<int> Parents;
vector<int> Rank;

void Input()
{
	cin >> N;

	Spots.clear();
	Rank = vector<int>(N + 1, 1);
	Parents = vector<int>(N + 1, -1);

	for (int i{ 0 }; i < N; ++i)
	{
		int R, C, Range;
		cin >> R >> C >> Range;

		Spots.push_back({ R,C,Range });

		Parents[i] = i;
	}
}

int Find(int U)
{
	if (Parents[U] == U)
		return U;

	return Parents[U] = Find(Parents[U]);
}

void Merge(int U, int V)
{
	int Par_U{ Find(U) };
	int Par_V{ Find(V) };

	if (Par_U == Par_V)
		return;

	if (Rank[Par_U] > Rank[Par_V])
		swap(Par_U, Par_V);

	Parents[Par_U] = Par_V;

	if (Rank[Par_U] == Rank[Par_V])
		++Rank[Par_V];
}

int GetDist(int R1, int C1, int R2, int C2)
{
	int R1MinusR2{ abs(R1 - R2) };
	int C1MinusC2{ abs(C1 - C2) };
	return (R1MinusR2 * R1MinusR2 + C1MinusC2 * C1MinusC2);
}

void Solve()
{
	cin >> T;

	while (T != 0)
	{
		Input();

		for (int i{ 0 }; i < Spots.size(); ++i)
		{
			for (int j{ i }; j < Spots.size(); ++j)
			{
				if (i == j)
					continue;

				int Src_Range{ get<2>(Spots[i]) };
				int Dst_Range{ get<2>(Spots[j]) };

				int Src_R{ get<0>(Spots[i]) };
				int Src_C{ get<1>(Spots[i]) };
				int Dst_R{ get<0>(Spots[j]) };
				int Dst_C{ get<1>(Spots[j]) };

				auto Dist{ GetDist(Src_R,Src_C,Dst_R,Dst_C) };

				if ((Src_Range + Dst_Range) * (Src_Range + Dst_Range) >= Dist)
				{
					Merge(i, j);
				}
			}
		}

		set<int> Parents;
		for (int i{ 0 }; i < Spots.size(); ++i)
		{
			int R{ get<0>(Spots[i]) };
			int C{ get<1>(Spots[i]) };

			Parents.insert(Find(i));
		}

		cout << Parents.size() << endl;

		--T;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}