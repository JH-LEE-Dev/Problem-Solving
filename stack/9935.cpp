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

/*
*  ���� �м�
*	1. Ư�� ���ڿ��� �߰ߵǸ�, �ı��ϸ� �ȴ�.
*
*	���� �ذ� ����
*	1. ������ Ȱ���ؼ� ���ڿ��� �����ϴµ�, ���� �ı��ؾ� �� ���ڿ��� �߰ߵȴٸ�, ���ڿ� ���̸�ŭ ���� pop ������ �����Ѵ�.
*	-> ���� �߰�
*	12a12abb
*	12ab
*	���� ���� ������ Ǯ �� ����.
*
*	���� ����
*	1. ���ÿ� ���ڸ� ������Ű�ٰ�, ��ź ���ڿ� ���̺��� ���ų� Ŀ����, ��ź ���ڿ� ���̸�ŭ pop�ؼ� �ش� ���ڿ���
*	��ź ���ڿ����� Ȯ��, �ƴ϶�� �ٽ� ���ÿ� push
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()

stack<char> arr;
string bomb;
string inputString;

void input()
{
	cin >> inputString;
	cin >> bomb;
}

void solve()
{
	int cnt{ 0 };

	for (int i{ 0 }; i < inputString.length(); ++i)
	{
		arr.push(inputString[i]);

		if (arr.size() >= bomb.length())
		{
			string popedString = "";

			for (int i{ 0 }; i < bomb.length(); ++i)
			{
				popedString += arr.top();
				arr.pop();
			}

			reverse(popedString.begin(), popedString.end());

			if (popedString != bomb)
			{
				for (int i{ 0 }; i < bomb.length(); ++i)
				{
					arr.push(popedString[i]);
				}
			}
		}
	}

	if (arr.size() == 0)
		cout << "FRULA";
	else
	{
		string outputString = "";

		while (arr.empty() == false)
		{
			outputString += arr.top();
			arr.pop();
		}

		reverse(outputString.begin(), outputString.end());
		cout << outputString;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();
	solve();

	return 0;
}