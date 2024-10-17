#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;

bool isVowel(const char& _char)
{
	return (_char == 'a') ||
		(_char == 'e') ||
		(_char == 'i') ||
		(_char == 'o') ||
		(_char == 'u');
}

bool check(const string& input)
{
	int consonant{ 0 }, vowel{ 0 };
	bool isThereVowel{ false };
	bool isDuplication{ false };

	for (int i{ 0 }; i < input.size(); ++i)
	{
		if (i == 0)
		{
			if (isVowel(input[i]))
			{
				isThereVowel = true;
				++vowel;
			}
			else
			{
				++consonant;
			}

			continue;
		}

		if (isVowel(input[i]))
		{
			isThereVowel = true;

			if (i > 0)
			{
				if (isVowel(input[i - 1]))
				{
					++vowel;
				}
				else
				{
					vowel = 1;
				}

				if (input[i] == input[i - 1])
				{
					if (input[i] != 'e' && input[i] != 'o')
					{
						return false;
					}
				}
			}
		}
		else
		{
			if (i > 0)
			{
				if (!isVowel(input[i - 1]))
				{
					++consonant;

					if (input[i] == input[i - 1])
					{
						return false;
					}
				}
				else
				{
					consonant = 1;
				}
			}
		}

		if (consonant >= 3 || vowel >= 3)
		{
			return false;
		}
	}

	if (isThereVowel == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (1)
	{
		string input;
		cin >> input;

		if (input == "end")
			break;

		if (check(input))
		{
			cout << "<" << input << "> is acceptable." << endl;
		}
		else
		{
			cout << "<" << input << "> is not acceptable." << endl;
		}
	}

	return 0;
}