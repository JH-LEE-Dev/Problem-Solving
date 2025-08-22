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

int W, T;
vector<string> Words;
vector<vector<char>> Table;
vector<vector<bool>> Visited;

vector<int> Dir_Row{ 0,0,1,-1,1,-1,1,-1 };
vector<int> Dir_Col{ 1,-1,0,0,1,1,-1,-1 };

map<int, int> Score;

bool IsValid(int R, int C)
{
	if (R >= 4 || R < 0 || C >= 4 || C < 0)
		return false;
	else
		return true;
}

void Input()
{
	Score[1] = 0;
	Score[2] = 0;
	Score[3] = 1;
	Score[4] = 1;
	Score[5] = 2;
	Score[6] = 3;
	Score[7] = 5;
	Score[8] = 11;

	cin >> W;

	for (int i{ 0 }; i < W; ++i)
	{
		string Str;
		cin >> Str;

		Words.push_back(Str);
	}

	cin >> T;
}

bool Dfs(string Str, int Idx, int R, int C)
{
	if (Idx == Str.length() - 1)
		return true;

	Visited[R][C] = true;

	for (int i{ 0 }; i < 8; ++i)
	{
		auto NewR{ R + Dir_Row[i] };
		auto NewC{ C + Dir_Col[i] };

		if (IsValid(NewR, NewC) == false)
			continue;

		if (Table[NewR][NewC] != Str[Idx + 1])
			continue;

		if (Visited[NewR][NewC] == false)
		{
			if (Dfs(Str, Idx + 1, NewR, NewC))
			{
				Visited[R][C] = false;
				return true;
			}
		}
	}

	Visited[R][C] = false;

	return false;
}

void Solve()
{
	while (T != 0)
	{
		vector<string> MaxWords;
		int Cnt{ 0 };
		int Result{ 0 };
		int MaxLength{ 0 };

		Table = vector<vector<char>>(4, vector<char>(4));

		for (int i{ 0 }; i < 4; ++i)
		{
			for (int j{ 0 }; j < 4; ++j)
			{
				cin >> Table[i][j];
			}
		}

		Visited = vector<vector<bool>>(4, vector<bool>(4, false));

		for (int i{ 0 }; i < W; ++i)
		{
			bool bFound{ false };

			for (int R{ 0 }; R < 4; ++R)
			{
				for (int C{ 0 }; C < 4; ++C)
				{
					if (Table[R][C] == Words[i][0])
					{
						if (Dfs(Words[i], 0, R, C))
						{
							++Cnt;
							Result += Score[Words[i].length()];

							if (MaxLength < Words[i].length())
							{
								MaxLength = Words[i].length();
								MaxWords.clear();
								MaxWords.push_back(Words[i]);
							}
							else if (MaxLength == Words[i].length())
							{
								MaxWords.push_back(Words[i]);
							}

							bFound = true;
						}
					}

					if (bFound)
						break;
				}

				if (bFound)
					break;
			}
		}

		sort(MaxWords.begin(), MaxWords.end());

		cout << Result << ' ' << MaxWords[0] << ' ' << Cnt << endl;

		--T;
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