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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 27
int N{ 0 };
vector<vector<int>> edges(MAX, vector<int>());
vector<int> indegree(MAX, -1);
vector<string> input;
enum RESULT { VALID, DUPLICATE, INVALID, DEFAULT };
vector<int> output;

bool isValid{ true };
bool isDuplicated{ false };
bitset<26> checking;
int counting{ 0 };

void topoSort()
{
	queue<int> myQ;

	for (int i{ 0 }; i < 26; ++i)
	{
		if (indegree[i] == 0 && checking[i] == true)
		{
			myQ.push(i);
		}
	}

	while (true)
	{
		if (myQ.empty())
		{
			break;
		}

		if (myQ.size() > 1)
		{
			isDuplicated = true;
		}

		auto cur = myQ.front();
		output.push_back(cur);
		myQ.pop();

		for (auto dst : edges[cur])
		{
			--indegree[dst];

			if (indegree[dst] == 0)
				myQ.push(dst);
		}
	}

	if (output.size() != counting)
	{
		isValid = false;
	}

	return;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		string str;
		cin >> str;

		input.push_back(str);

		for (int j{ 0 }; j < str.length(); ++j)
		{
			if (checking[str[j] - 'a'] == false)
			{
				checking[str[j] - 'a'] = true;
				++counting;
				indegree[str[j] - 'a'] = 0;
			}
		}
	}

	for (int i{ 0 }; i < N - 1; ++i)
	{
		auto left{ input[i] };
		auto right{ input[i + 1] };

		for (int j{ 0 }; j < left.length(); ++j)
		{
			if (j < right.length())
			{
				int src{ left[j] - 'a' };
				int dst{ right[j] - 'a' };

				if (src != dst)
				{
					edges[src].push_back(dst);
					++indegree[dst];

					break;
				}
			}
			else
			{
				isValid = false;
				break;
			}
		}
	}

	topoSort();

	if (isValid == false)
	{
		cout << "!";
	}
	else if (isDuplicated == true)
	{
		cout << "?";
	}
	else
	{
		for (auto& num : output)
		{
			cout << char(num + 'a');
		}
	}

	return 0;
}