#include <iostream>
#include <vector>
#include <stack>
#define endl '\n'
using namespace std;

vector<int> arr(100'005, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 };

	stack<int> myStack;
	string output;
	cin >> N;


	int pushCount{ 0 }, index{ 0 };

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;
		if (pushCount < input)
		{
			for (int j{ pushCount + 1 }; j <= input; ++j)
			{
				myStack.push(j);
				++pushCount;
				output += '+';
			}

			myStack.pop();
			output += '-';
		}
		else
		{
			if (myStack.top() != input)
			{
				cout << "NO";
				return 0;

			}
			else
			{
				myStack.pop();
				output += '-';
			}
		}
	}

	for (int i{ 0 }; i < output.size(); ++i)
	{
		cout << output[i] << endl;
	}

	return 0;
}