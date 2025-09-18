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
	int Num{ 0 };
	vector<pair<char, int>> Nxt;
};

int Unused;
int N;
vector<string> Arr;
vector<Node> Trie;
map<string, int> Cnt;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		string Str;
		cin >> Str;

		Arr.push_back(Str);
	}
}

int C2i(char C)
{
	return C - 'a';
}

void Insert(const string& Str)
{
	int Cur{ ROOT };

	for (const auto& C : Str)
	{
		int Num{ -1 };

		for (const auto& P : Trie[Cur].Nxt)
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
			Num = ++Unused;
			Trie[Cur].Nxt.push_back({ C,Num });
			Trie.push_back({ Unused });
		}

		Cur = Num;
	}

	++Cnt[Str];
}

string Find(const string& Str)
{
	int Cur{ ROOT };

	string Ret;

	for (const auto& C : Str)
	{
		int Num{ -1 };

		for (const auto& P : Trie[Cur].Nxt)
		{
			auto [Char, Id] {P};

			if (Char == C)
			{
				Num = Id;
				break;
			}
		}

		Ret += C;

		if (Num == -1)
			break;

		Cur = Num;
	}

	if (Ret == Str)
	{
		if (Cnt[Str] >= 1)
			return Ret += to_string(Cnt[Str] + 1);
		else
			return Ret;
	}

	return Ret;
}

void Solve()
{
	Trie.push_back(Node());

	for (int i{ 0 }; i < N; ++i)
	{
		cout << Find(Arr[i]) << endl;
		Insert(Arr[i]);
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