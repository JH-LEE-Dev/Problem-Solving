#include <iostream>
#include <vector>
using namespace std;

vector<int> arr(1005, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int A{ 0 }, B{ 0 }, GCD{ 0 }, LCM{ 0 };
	cin >> A >> B;
	int a = A, b = B;

	while (1)
	{
		GCD = a % b;

		if (GCD == 0)
		{
			GCD = b;
			break;
		}

		a = b;

		b = GCD;
	}

	cout << GCD << '\n' << A * B / GCD;

	return 0;
}
