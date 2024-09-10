#include <iostream>
#include <string>
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	string A, B, C, D;

	cin >> A >> B >> C >> D;

	string A_B = A + B;
	string C_D = C + D;

	long long A_B_num = stoll(A_B);
	long long C_D_num = stoll(C_D);

	cout << A_B_num + C_D_num;

	return 0;
}