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
#define ROOT 0

struct Node
{
	int Num{ -1 };
	int Cnt{ 0 };
	vector<pair<char, int>> Nxt;
};

int N;
int Unused_A;
int Unused_B;
vector<Node> Trie_A;
vector<Node> Trie_B;

void Input()
{
	cin >> N;
}

void Insert_A(const string& Str)
{
	int Cur{ ROOT };

	for (const auto& C : Str)
	{
		int Num{ -1 };

		for (const auto& P : Trie_A[Cur].Nxt)
		{
			auto [Char, Id] {P};

			if (Char == C)
			{
				Num = Id;
				break;
			}
		}

		if (Num == -1)
		{
			Num = ++Unused_A;
			Trie_A.push_back({ Num });
			Trie_A[Cur].Nxt.push_back({ C, Num });
		}

		Cur = Num;
		++Trie_A[Num].Cnt;
	}
}

void Insert_B(const string& Str)
{
	int Cur{ ROOT };

	for (const auto& C : Str)
	{
		int Num{ -1 };

		for (const auto& P : Trie_B[Cur].Nxt)
		{
			auto [Char, Id] {P};

			if (Char == C)
			{
				Num = Id;
				break;
			}
		}

		if (Num == -1)
		{
			Num = ++Unused_B;
			Trie_B.push_back({ Num });
			Trie_B[Cur].Nxt.push_back({ C, Num });
		}

		Cur = Num;
		++Trie_B[Num].Cnt;
	}
}

void Find_B(const string& Str, vector<int>& Cnt)
{
	int Cur{ ROOT };

	for (int i{ (int)Str.length() - 1 }; i >= 0; --i)
	{
		char C{ Str[i] };
		int Num{ -1 };

		for (const auto& P : Trie_B[Cur].Nxt)
		{
			auto [Char, Id] {P};

			if (Char == C)
			{
				Num = Id;
				break;
			}
		}

		if (Num == -1)
			return;

		Cnt[Str.length() - i - 1] = Trie_B[Num].Cnt;

		Cur = Num;
	}

	return;
}

void Find_A(const string& Str, vector<int>& Cnt)
{
	int Result{ 0 };

	int Cur{ ROOT };
	int Idx{ 0 };

	for (const auto& C : Str)
	{
		int Num{ -1 };

		for (const auto& P : Trie_A[Cur].Nxt)
		{
			auto [Char, Id] {P};

			if (Char == C)
			{
				Num = Id;
				break;
			}
		}

		if (Num == -1)
			return;

		Cnt[Idx] = Trie_A[Num].Cnt;

		Cur = Num;
		++Idx;
	}
}

void Delete_B(const string& Str)
{
	int Cur{ ROOT };

	for (const auto& C : Str)
	{
		int Num{ -1 };

		for (const auto& P : Trie_B[Cur].Nxt)
		{
			auto [Char, Id] {P};

			if (Char == C)
			{
				Num = Id;
				break;
			}
		}

		Cur = Num;
		--Trie_B[Num].Cnt;
	}
}

void Delete_A(const string& Str)
{
	int Cur{ ROOT };

	for (const auto& C : Str)
	{
		int Num{ -1 };

		for (const auto& P : Trie_A[Cur].Nxt)
		{
			auto [Char, Id] {P};

			if (Char == C)
			{
				Num = Id;
				break;
			}
		}

		Cur = Num;
		--Trie_A[Num].Cnt;
	}
}

void Solve()
{
	Trie_A.push_back({ 0 });
	Trie_B.push_back({ 0 });

	for (int i{ 0 }; i < N; ++i)
	{
		string Order;

		cin >> Order;

		if (Order == "add")
		{
			char Type;
			cin >> Type;

			string Str;
			cin >> Str;

			if (Type == 'A')
				Insert_A(Str);
			else
			{
				reverse(Str.begin(), Str.end());

				Insert_B(Str);
			}
		}
		else if (Order == "find")
		{
			string Str;
			cin >> Str;

			vector<int> CntA(Str.length() + 1, 0);
			vector<int> CntB(Str.length() + 1, 0);

			int Result{ 0 };

			Find_A(Str, CntA);
			Find_B(Str, CntB);

			for (int i{ 0 }; i < Str.length() - 1; ++i)
			{
				Result += CntA[i] * CntB[Str.length() - i - 2];
			}

			cout << Result << endl;
		}
		else
		{
			char Type;
			cin >> Type;

			string Str;
			cin >> Str;

			if (Type == 'A')
				Delete_A(Str);
			else
			{
				reverse(Str.begin(), Str.end());

				Delete_B(Str);
			}
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