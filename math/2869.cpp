#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	long long A{ 0 }, B{ 0 }, V{ 0 }, day{ 0 };

	cin >> A >> B >> V;

	day = 1;

	if (A >= V)
	{
		cout << "1";
		return 0;
	}

	day += (V - A) / (A - B);

	if ((V - A) % (A - B) != 0)
		++day;

	cout << day;

	return 0;
}
