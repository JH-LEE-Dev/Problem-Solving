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

int N, M, K, Size, TreeHeight;
vector<LL> SegTree;
vector<LL> Lazy;
vector<LL> Arr;

void Input()
{
	cin >> N >> M >> K;

	TreeHeight = (int)ceil(log2(N));
	int TreeSize{ 1 << (TreeHeight + 1) };
	SegTree.resize(TreeSize);
	Lazy.resize(TreeSize);
	Size = 1 << TreeHeight;
	Arr.resize(TreeSize);

	for (int i{ 0 }; i < N; ++i)
	{
		LL Temp;
		cin >> Temp;

		Arr[i] = Temp;
		SegTree[i + Size] = Temp;
	}
}

void InitTree()
{
	for (int i{ Size - 1 }; i > 0; --i)
	{
		SegTree[i] = SegTree[i << 1] + SegTree[i << 1 | 1];
	}
}

void Calc(int Node, int K)
{
	SegTree[Node] = SegTree[Node << 1] + SegTree[Node << 1 | 1] + Lazy[Node] * K;
}

//노드에 증가 연산을 적용하는 함수 + Lazy값을 저장.
void Apply(int Node, LL Val, int K)
{
	SegTree[Node] += Val * K;

	if (Node < Size)
		Lazy[Node] += Val;
}

//부모 노드로 바뀐 리프 노드의 영향을 적용하는 함수.
void Build(int Start, int End)
{
	int K{ 2 };

	for (Start += Size, End += Size - 1; Start > 1; K <<= 1)
	{
		Start >>= 1, End >>= 1;

		for (int i{ End }; i >= Start; --i)
			Calc(i, K);
	}
}

//Lazy를 자식 노드에 적용하는 함수.
void Push(int Start, int End)
{
	int H{ TreeHeight }, K{ 1 << (TreeHeight - 1) };

	for (Start += Size, End += Size - 1; H > 0; --H, K >>= 1)
	{
		for (int i{ Start >> H }; i <= End >> H; ++i)
		{
			if (Lazy[i] != 0)
			{
				Apply(i << 1, Lazy[i], K);
				Apply(i << 1 | 1, Lazy[i], K);
				Lazy[i] = 0;
			}
		}
	}
}

//구간 증가 함수.
void Update(int Start, int End, LL Val)
{
	//양쪽 경계에 대해서 부모의 Lazy를 자식으로 전파.
	//구간 증가일 때는 push를 안해도 됨, 왜냐? 계속 Lazy에 누적하면 되니까
	//하지만 구간 할당일 때는 이전의 변경 사항을 전부 적용하고 다시 바꿔야 하므로
	//Push로 한 번 싹 적용해주는 거임.

	//Push(Start, Start + 1);
	//Push(End - 1, End);

	int Start0{ Start }, End0{ End }, K{ 1 };

	for (Start += Size, End += Size; Start < End; Start >>= 1, End >>= 1, K <<= 1)
	{
		if (Start & 1)
		{
			Apply(Start, Val, K);
			++Start;
		}

		if (End & 1)
		{
			--End;
			Apply(End, Val, K);
		}
	}

	//양쪽 경계에 대해서 자식의 변화를 부모에 전파.
	Build(Start0, Start0 + 1);
	Build(End0 - 1, End0);
}

LL Query(int Start, int End)
{
	Push(Start, Start + 1);
	Push(End - 1, End);

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

	for (int i{ 0 }; i < M + K; ++i)
	{
		LL Type;

		cin >> Type;

		if (Type == 1)
		{
			LL Start, End, Val;
			cin >> Start >> End >> Val;

			Update(Start - 1, End, Val);
		}
		else
		{
			LL Start, End;
			cin >> Start >> End;

			cout << Query(Start - 1, End) << endl;
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