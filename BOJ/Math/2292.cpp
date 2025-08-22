#include <iostream>
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, shift{ 1 }, count{ 1 };

	cin >> N;

	while (shift < N)
	{
		shift += count * 6;

		++count;
	}

	cout << count;

	return 0;
}