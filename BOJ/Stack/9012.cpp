#include <iostream>
#include <stack>
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T{ 0 };
	cin >> T;

	while (T != 0)
	{
		stack<char> Temp;
		string Input;
		cin >> Input;

		bool isValid{ false };

		for (int i = 0; i < Input.length(); ++i)
		{
			if (i == 0)
			{
				Temp.push(Input[i]);

				if (Input[i] == ')')
					break;

				continue;
			}

			if (Input[i] == '(')
				Temp.push(Input[i]);
			else
			{
				if (Temp.empty() == false)
				{
					if (Temp.top() == '(')
						Temp.pop();
					else
						break;
				}
				else
				{
					Temp.push(Input[i]);
					break;
				}
			}
		}

		if (Temp.empty())
		{
			cout << "YES" << '\n';
		}
		else
		{
			cout << "NO" << '\n';
		}

		--T;
	}

	return 0;
}