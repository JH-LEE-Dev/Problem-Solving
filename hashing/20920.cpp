#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define endl '\n'
using namespace std;

#define MAX 100'005

vector<pair<string, int>> note(MAX);
unordered_map<string, int> tempNote;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, M{ 0 };

	cin >> N >> M;

	for (int i{ 0 }; i < N; ++i)
	{
		string input;
		cin >> input;

		if (input.size() >= M)
		{
			if (tempNote.find(input) != tempNote.end())
			{
				++tempNote[input];
			}
			else
			{
				tempNote.insert({ input,1 });
			}
		}
	}

	int idx{ 0 };
	while (!tempNote.empty())
	{
		note[idx] = *tempNote.begin();
		tempNote.erase(tempNote.begin());
		++idx;
	}

	int mapSize{ idx };
	sort(note.begin(), note.begin() + N, [](const pair<string, int>& lhs, const pair<string, int>& rhs) {
		if (lhs.second != rhs.second)
		{
			return lhs.second > rhs.second;
		}
		else
		{
			if (lhs.first.size() != rhs.first.size())
			{
				return lhs.first.size() > rhs.first.size();
			}
			else
			{
				return lhs.first < rhs.first;
			}
		}
		});

	for (int i{ 0 }; i < mapSize; ++i)
	{
		cout << note[i].first << endl;
	}

	return 0;
}