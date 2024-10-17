#include <iostream>
#include <vector>
#include <algorithm>

#define endl '\n'
using namespace std;

vector<string> table(1005);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, leftArm{ 0 }, rightArm{ 0 }, waist{ 0 }, leftLeg{ 0 }, rightLeg{ 0 };

	pair<int, int> headIndex;
	pair<int, int> heartIndex;

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> table[i];
	}

	//find head & heart
	for (int i{ 0 }; i < N; ++i)
	{
		auto iter = find(table[i].begin(), table[i].end(), '*');

		if (iter != table[i].end())
		{
			headIndex.first = i;
			headIndex.second = distance(table[i].begin(), iter);

			heartIndex.first = i + 1;
			heartIndex.second = headIndex.second;

			break;
		}
	}

	//left arm
	for (int i{ 0 }; i < N; ++i)
	{
		if (table[heartIndex.first][i] == '*')
		{
			leftArm = heartIndex.second - i;
			break;
		}
	}

	//right arm
	for (int i{ N - 1 }; i >= 0; --i)
	{
		if (table[heartIndex.first][i] == '*')
		{
			rightArm = i - heartIndex.second;
			break;
		}
	}

	//waist
	for (int i{ N - 1 }; i > heartIndex.first; --i)
	{
		if (table[i][heartIndex.second] == '*')
		{
			waist = i - heartIndex.first;
			break;
		}
	}

	//left leg
	for (int i{ N - 1 }; i > heartIndex.first; --i)
	{
		if (table[i][heartIndex.second - 1] == '*')
		{
			leftLeg = i - (heartIndex.first + waist);
			break;
		}
	}

	//right leg
	for (int i{ N - 1 }; i > heartIndex.first; --i)
	{
		if (table[i][heartIndex.second + 1] == '*')
		{
			rightLeg = i - (heartIndex.first + waist);
			break;
		}
	}

	cout << heartIndex.first + 1 << ' ' << heartIndex.second + 1 << endl;
	cout << leftArm << ' ' << rightArm << ' ' << waist << ' ' << leftLeg << ' ' << rightLeg;

	return 0;
}