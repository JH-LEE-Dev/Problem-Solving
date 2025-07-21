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
using LL = long long;

#define endl '\n'
#define INF numeric_limits<int>::max()

int N, M, Size;
vector<LL> SegTree;
vector<tuple<int, int>> Query_1;
vector<tuple<int, int, int, int>> Query_2;

void Input()
{
	cin >> N;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> SegTree[i + Size];
	}

	cin >> M;

	int Idx_2{ 0 };

	for (int i{ 0 }; i < M; ++i)
	{
		int Type;

		cin >> Type;

		if (Type == 1)
		{
			int Idx, Val;
			cin >> Idx >> Val;

			Query_1.push_back({ Idx,Val });
		}
		else
		{
			int K, Start, End;
			cin >> K >> Start >> End;

			Query_2.push_back({ K,Idx_2,Start,End });

			++Idx_2;
		}
	}
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i] = SegTree[i << 1] + SegTree[i << 1 | 1];
	}
}

void Update(int Idx, LL Val)
{
	for (SegTree[Idx += Size] = Val; Idx > 1; Idx >>= 1)
	{
		SegTree[Idx >> 1] = SegTree[Idx] + SegTree[Idx ^ 1];
	}
}

LL Query(int Start, int End)
{
	LL Ret{ 0 };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1)
	{
		if (Start & 1)
		{
			Ret += SegTree[Start];
			++Start;
		}

		if (End & 1)
		{
			--End;
			Ret += SegTree[End];
		}
	}

	return Ret;
}

void Solve()
{
	InitTree();

	sort(Query_2.begin(), Query_2.end());

	vector<tuple<int, LL>> Query_2_Result;

	int PrevK{ 0 };

	for (int i{ 0 }; i < Query_2.size(); ++i)
	{
		int Idx{ get<1>(Query_2[i]) };
		int K{ get<0>(Query_2[i]) };
		int Start{ get<2>(Query_2[i]) };
		int End{ get<3>(Query_2[i]) };

		if (PrevK != K)
		{
			for (int j{ PrevK }; j < K; ++j)
			{
				int Update_Idx{ get<0>(Query_1[j]) };
				int Update_Val{ get<1>(Query_1[j]) };

				Update(Update_Idx - 1, Update_Val);
			}
		}

		PrevK = K;

		Query_2_Result.push_back({ Idx,Query(Start - 1,End) });
	}

	sort(Query_2_Result.begin(), Query_2_Result.end());

	for (int i{ 0 }; i < Query_2_Result.size(); ++i)
	{
		cout << get<1>(Query_2_Result[i]) << endl;
	}
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