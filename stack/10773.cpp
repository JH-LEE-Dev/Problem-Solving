#include <iostream>
#include <stack>
#define endl '\n'
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	stack<int> account;

	int N{ 0 }, total{ 0 };

	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;

		if (input != 0)
			account.push(input);
		else
			account.pop();
	}

	while (!account.empty())
	{
		total += account.top();
		account.pop();
	}
	cout << total;

	return 0;
}