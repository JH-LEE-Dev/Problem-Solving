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
*	문제 분석
*	1. (A+B) -> AB+, A*B+C -> AB*C+
*
*	문제 해결 전략
*	1. 문자는 결과 배열에 삽입하고, 연산자는 스택에 push한다.
*	2. +,-연산자는 우선 순위가 높은 연산자를 스택에서 모두 pop하고 자신을 push한다.
*	3. *,/연산자는 우선 순위가 같은 연산자를 스택에서 모두 pop하고 자신을 push한다.
*	4. 닫는 괄호를 만나면, 여는 괄호를 만날 때 까지 스택에서 pop한다.
*	5. 모든 연산자는 ( 를 만나기 전까지만 pop한다.
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