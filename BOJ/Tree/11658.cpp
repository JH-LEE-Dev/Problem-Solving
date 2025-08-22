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
#define MAX 1'024

int N, M, Size;
vector<vector<LL>> SegTree;

void Input()
{
	cin >> N >> M;

	int TreeHeight{ (int)ceil(log2(N)) };
	int TreeSize{ 1 << (TreeHeight + 1) };
	Size = 1 << TreeHeight;
	SegTree.resize(TreeSize);

	for (int i{ 0 }; i < TreeSize; ++i)
	{
		SegTree[i].resize(TreeSize);
	}

	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ 0 }; j < N; ++j)
		{
			cin >> SegTree[i + Size][j + Size];
		}
	}
}

void InitTree()
{
	for (int i{ 0 }; i < N; ++i)
	{
		for (int j{ Size - 1 }; j > 0; --j)
		{
			SegTree[i + Size][j] = SegTree[i + Size][j << 1] + SegTree[i + Size][j << 1 | 1];
		}
	}

	for (int i{ Size - 1 }; i > 0; --i)
	{
		for (int j{ 1 }; j < SegTree[i].size(); ++j)
		{
			SegTree[i][j] = SegTree[i << 1][j] + SegTree[i << 1 | 1][j];
		}
	}
}

void Update(int R, int C, LL Val)
{
	int TempR{ R };
	int TempC{ C };

	for (SegTree[R + Size][C += Size] = Val; C > 1; C >>= 1)
	{
		SegTree[R + Size][C >> 1] = SegTree[R + Size][C] + SegTree[R + Size][C ^ 1];
	}

	for (R += Size; R > 1; R >>= 1)
	{
		C = TempC;

		//이 부분 헷갈릴 수 있음! 행에 대해서 Update할 때는 C == 1인 경우도 포함해야 함.
		for (C += Size; C >= 1; C >>= 1)
		{
			SegTree[R >> 1][C] = SegTree[R][C] + SegTree[R ^ 1][C];
		}
	}
}

// 특정 행의 구간 합
LL QueryRow(int Row, int Y1, int Y2)
{
	LL Ret{ 0 };

	// 행 범위
	for (Y1 += Size, Y2 += Size; Y1 < Y2; Y1 >>= 1, Y2 >>= 1)
	{
		if (Y1 & 1)
		{
			Ret += SegTree[Row][Y1];
			++Y1;
		}

		if (Y2 & 1)
		{
			--Y2;
			Ret += SegTree[Row][Y2];
		}
	}

	return Ret;
}

// 구간 합 쿼리: (x1, y1) ~ (x2, y2)
LL Query(int X1, int Y1, int X2, int Y2)
{
	LL Ret{ 0 };

	// 행 범위
	for (X1 += Size, X2 += Size; X1 < X2; X1 >>= 1, X2 >>= 1)
	{
		if (X1 & 1)
		{
			Ret += QueryRow(X1, Y1, Y2);
			++X1;
		}

		if (X2 & 1)
		{
			--X2;
			Ret += QueryRow(X2, Y1, Y2);
		}
	}

	return Ret;
}

void Solve()
{
	InitTree();

	for (int i{ 0 }; i < M; ++i)
	{
		int Type;

		cin >> Type;

		if (Type == 0)
		{
			int R, C, Val;
			cin >> R >> C >> Val;

			Update(R - 1, C - 1, Val);
		}
		else
		{
			int R_Src, C_Src, R_Dst, C_Dst;
			cin >> R_Src >> C_Src >> R_Dst >> C_Dst;

			cout << Query(R_Src - 1, C_Src - 1, R_Dst, C_Dst) << endl;
		}
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