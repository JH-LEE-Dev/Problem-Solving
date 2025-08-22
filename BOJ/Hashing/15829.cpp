#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	long long N{ 0 };

	long long r{ 1 }, M{ 1234567891 }, hash{ 0 };
	string input;

	cin >> N >> input;

	for (long long i = 0; i < N; ++i)
	{
		hash += ((long long)input[i] - 'a' + 1) * (r) % M;
		r = (r * 31) % M;

		hash %= M;
	}

	cout << hash;

	return 0;
}

/*
* 각 변수의 범위를 M 안쪽으로 보장하기 위해서 연산할 때마다 modulo M을 해준다.
* pow함수는 double을 반환하므로 사용할 수 없다.
*/