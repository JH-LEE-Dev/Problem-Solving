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
#define ROOT 1
#define MAX 100'005

//FOR TRIE.
int Unused{ 1 };
vector<bool> Chk;
vector<vector<int>> Nxt;

int T, N;
vector<string> Numbers;

void Input()
{
	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		string Str;
		cin >> Str;

		Numbers.push_back(Str);
	}
}

int C2i(char C)
{
	return C - '0';
}

void Insert(string& Str)
{
	int Cur{ ROOT };

	for (auto& C : Str)
	{
		int Num{ C2i(C) };

		if (Nxt[Cur][Num] == -1)
			Nxt[Cur][Num] = ++Unused;

		Cur = Nxt[Cur][Num];
	}

	Chk[Cur] = true;
}

bool Find(string& Str)
{
	int Cur{ ROOT };

	for (auto& C : Str)
	{
		int Num{ C2i(C) };

		if (Nxt[Cur][Num] == -1 || Chk[Cur] == true)
			return false;

		Cur = Nxt[Cur][Num];
	}

	if (Chk[Cur] == true)
		return true;
	else
		return false;
}

void Erase(string& Str)
{
	int Cur{ ROOT };

	for (auto& C : Str)
	{
		int Num{ C2i(C) };

		if (Nxt[Cur][Num] == -1)
			return;

		Cur = Nxt[Cur][Num];
	}

	Chk[Cur] = false;
}

void Clear()
{
	Chk = vector<bool>(MAX, false);
	Nxt = vector<vector<int>>(MAX, vector<int>(10, -1));
	Unused = 1;

	Numbers.clear();
}

void Solve()
{
	cin >> T;

	while (T != 0)
	{
		Clear();
		Input();

		for (int i{ 0 }; i < N; ++i)
		{
			Insert(Numbers[i]);
		}

		bool bValid{ true };

		for (int i{ 0 }; i < N; ++i)
		{
			if (Find(Numbers[i]) == false)
			{
				bValid = false;
				break;
			}
		}

		if (bValid == true)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;

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