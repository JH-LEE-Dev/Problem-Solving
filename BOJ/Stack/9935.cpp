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
*  문제 분석
*	1. 특정 문자열이 발견되면, 파괴하면 된다.
*
*	문제 해결 전략
*	1. 스택을 활용해서 문자열을 누적하는데, 만약 파괴해야 할 문자열이 발견된다면, 문자열 길이만큼 스택 pop 연산을 실행한다.
*	-> 문제 발견
*	12a12abb
*	12ab
*	위와 같은 예제를 풀 수 없음.
*
*	전략 정정
*	1. 스택에 문자를 누적시키다가, 폭탄 문자열 길이보다 같거나 커지면, 폭탄 문자열 길이만큼 pop해서 해당 문자열이
*	폭탄 문자열인지 확인, 아니라면 다시 스택에 push
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