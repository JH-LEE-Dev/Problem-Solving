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
* �� ������ ������ M �������� �����ϱ� ���ؼ� ������ ������ modulo M�� ���ش�.
* pow�Լ��� double�� ��ȯ�ϹǷ� ����� �� ����.
*/