#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> suffixes(1005);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	string Input;

	cin >> Input;

	size_t length = Input.length();

	for (int i = 0; i < length; ++i)
	{
		suffixes[i] = Input.substr(i, length - i);
	}

	sort(suffixes.begin(), suffixes.begin() + length);

	for (int i = 0; i < length; ++i)
	{
		cout << suffixes[i] << '\n';
	}

	return 0;
}