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

int N;
vector<string> Arr;
vector<pair<int, char>> Alphabets(26, { 0,0 });

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

void Solve()
{
	for (int i{ 0 }; i < 26; ++i)
	{
		Alphabets[i].second = (char)(i + 'A');
	}

	for (int i{ 0 }; i < N; ++i)
	{
		auto Str{ Arr[i] };

		for (int j{ 0 }; j < Str.length(); ++j)
		{
			Alphabets[Str[j] - 'A'].first += pow(10, Str.length() - j - 1);
		}
	}

	int Num{ 9 };
	map<char, int> Alphabet;

	sort(Alphabets.begin(), Alphabets.end(), greater<pair<int, char>>());

	for (int i{ 0 }; i < Alphabets.size(); ++i)
	{
		if (Alphabets[i].first != 0)
		{
			Alphabet[Alphabets[i].second] = Num;
			--Num;
		}
	}

	int Result{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		string Str = Arr[i];

		for (int j{ 0 }; j < Arr[i].length(); ++j)
		{
			Str[j] = (char)(Alphabet[Arr[i][j]] + '0');
		}

		Result += stoi(Str);
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