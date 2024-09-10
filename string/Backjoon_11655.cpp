#include <iostream>
#include <string>
using namespace std;

#define ASCII_UPPER_CASE_START 65
#define ASCII_UPPER_CASE_END 90

#define ASCII_LOWER_CASE_START 97
#define ASCII_LOWER_CASE_END 122

#define ROT_13 13

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	string Input;

	getline(cin, Input);
	string Rot13(Input.length(), ' ');

	for (int i = 0; i < Input.length(); ++i)
	{
		int ascii_code = (int)Input[i];

		//lower case
		if (ascii_code >= ASCII_LOWER_CASE_START &&
			ascii_code <= ASCII_LOWER_CASE_END)
		{
			if (ascii_code + ROT_13 > ASCII_LOWER_CASE_END)
			{
				int offset = (ascii_code + ROT_13) - ASCII_LOWER_CASE_END - 1;

				ascii_code = offset + ASCII_LOWER_CASE_START;
			}
			else
			{
				ascii_code += ROT_13;
			}

			Rot13[i] = (char)ascii_code;

			continue;
		}

		//upper case
		if (ascii_code >= ASCII_UPPER_CASE_START &&
			ascii_code <= ASCII_UPPER_CASE_END)
		{
			if (ascii_code + ROT_13 > ASCII_UPPER_CASE_END)
			{
				int offset = (ascii_code + ROT_13) - ASCII_UPPER_CASE_END - 1;

				ascii_code = offset + ASCII_UPPER_CASE_START;
			}
			else
			{
				ascii_code += ROT_13;
			}

			Rot13[i] = (char)ascii_code;

			continue;
		}

		Rot13[i] = Input[i];
	}

	cout << Rot13;

	return 0;
}