#include <iostream>
#include <vector>
using namespace std;

#define ASCII_OFFSET_LOWERCASE 97

vector<int> arr(26, -1);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	string Input;

	cin >> Input;

	for (int i = 0; i < Input.length(); ++i)
	{
		if (arr[(int)Input[i] - ASCII_OFFSET_LOWERCASE] == -1)
			arr[(int)Input[i] - ASCII_OFFSET_LOWERCASE] = i;
		else
			arr[(int)Input[i] - ASCII_OFFSET_LOWERCASE] = min(arr[(int)Input[i] - ASCII_OFFSET_LOWERCASE], i);
	}

	for (int i = 0; i < arr.size(); ++i)
	{
		cout << arr[i] << " ";
	}

	return 0;
}