#include <iostream>
#include <vector>
#include <string>

#define endl '\n'
using namespace std;

#define MAX 20'005
vector<char> table(MAX, 0);
vector<bool> filter(MAX, false);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, K{ 0 }, result{ 0 };
	cin >> N >> K;

	string input;
	cin >> input;
	for (int i{ 0 }; i < N; ++i)
	{
		table[i] = input[i];
	}

	for (int i{ 0 }; i < N; ++i)
	{
		bool eaten = false;
		if (table[i] == 'P')
		{
			for (int j{ K }; j >= 1; --j)
			{
				if (i - j >= 0 && table[i - j] == 'H')
				{
					if (filter[i - j] == false)
					{
						eaten = true;
						filter[i - j] = true;
						++result;
						break;
					}
				}
			}

			if (eaten == false)
			{
				for (int j{ 1 }; j <= K; ++j)
				{
					if (i + j <= N - 1 && table[i + j] == 'H')
					{
						if (filter[i + j] == false)
						{
							filter[i + j] = true;
							++result;
							break;
						}
					}
				}
			}
		}
	}

	cout << result;

	return 0;
}