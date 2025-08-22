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
*	���� �м�
*	1. (A+B) -> AB+, A*B+C -> AB*C+
*
*	���� �ذ� ����
*	1. ���ڴ� ��� �迭�� �����ϰ�, �����ڴ� ���ÿ� push�Ѵ�.
*	2. +,-�����ڴ� �켱 ������ ���� �����ڸ� ���ÿ��� ��� pop�ϰ� �ڽ��� push�Ѵ�.
*	3. *,/�����ڴ� �켱 ������ ���� �����ڸ� ���ÿ��� ��� pop�ϰ� �ڽ��� push�Ѵ�.
*	4. �ݴ� ��ȣ�� ������, ���� ��ȣ�� ���� �� ���� ���ÿ��� pop�Ѵ�.
*	5. ��� �����ڴ� ( �� ������ �������� pop�Ѵ�.
*/

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()

string inputString;
stack<char> operators;
vector<char> result;

void input()
{
	cin >> inputString;
}

void solve()
{
	for (int i{ 0 }; i < inputString.length(); ++i)
	{
		if (inputString[i] == '*' || inputString[i] == '/')
		{
			while (true)
			{
				if (operators.empty())
				{
					operators.push(inputString[i]);
					break;
				}

				if (operators.top() == '*' || operators.top() == '/')
				{
					result.push_back(operators.top());
					operators.pop();
				}
				else
				{
					operators.push(inputString[i]);
					break;
				}
			}
		}
		else if (inputString[i] == '+' || inputString[i] == '-')
		{
			while (true)
			{
				if (operators.empty())
				{
					operators.push(inputString[i]);
					break;
				}

				if (operators.top() == '(')
				{
					operators.push(inputString[i]);

					break;
				}
				else
				{
					result.push_back(operators.top());
					operators.pop();
				}
			}
		}
		else
		{
			if (inputString[i] == '(')
				operators.push(inputString[i]);
			else if (inputString[i] == ')')
			{
				while (true)
				{
					if (operators.empty())
					{
						operators.push(inputString[i]);
						break;
					}

					if (operators.top() == '(')
					{
						operators.pop();
						break;
					}
					else
					{
						result.push_back(operators.top());
						operators.pop();
					}
				}
			}
			else
			{
				result.push_back(inputString[i]);
			}
		}
	}

	if (operators.empty() == false)
	{
		while (operators.empty() == false)
		{
			result.push_back(operators.top());
			operators.pop();
		}
	}

	for (auto& ch : result)
	{
		cout << ch;
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