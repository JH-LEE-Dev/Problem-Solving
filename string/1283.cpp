#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <limits>
#include <algorithm>

#define endl '\n'
using namespace std;

vector<string> words(35);
vector<char> spelling(100'005);
vector<vector<bool>> idx(35, vector<bool>(100'005, false));

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 };
	cin >> N;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	for (int i{ 0 }; i < N; ++i)
	{
		getline(cin, words[i]);
	}

	unordered_set<char> hash;

	for (int i{ 0 }; i < N; ++i)
	{
		bool complete{ false };

		for (int j{ 0 }; j < words[i].size(); ++j)
		{
			if (j == 0 || (words[i][j - 1] == ' '))
			{
				char temp{ words[i][j] };

				if (temp == ' ')
					continue;

				if ((int)temp > 90)
				{
					temp = temp - 32;
				}

				if (hash.find(temp) == hash.end())
				{
					idx[i][j] = true;
					hash.insert(temp);

					words[i].insert(j, "[");
					words[i].insert(j + 2, "]");
					complete = true;
					break;
				}
				else
				{
					continue;
				}
			}
		}

		if (complete == false)
		{
			for (int j{ 0 }; j < words[i].size(); ++j)
			{
				char temp{ words[i][j] };

				if (temp == ' ')
					continue;

				if ((int)temp > 90)
				{
					temp = temp - 32;
				}

				if (hash.find(temp) == hash.end())
				{
					idx[i][j] = true;
					hash.insert(temp);

					words[i].insert(j, "[");
					words[i].insert(j + 2, "]");
					break;
				}
			}
		}
	}

	for (int i{ 0 }; i < N; ++i)
	{
		cout << words[i] << endl;
	}

	return 0;
}