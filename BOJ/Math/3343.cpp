#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <algorithm>
#include <limits>
#include <tuple>
#include <string>
#include <cmath>

#define endl '\n'
#define INF numeric_limits<long long>::max()
using namespace std;

long long N{ 0 }, A{ 0 }, B{ 0 }, C{ 0 }, D{ 0 };
long long result{ INF };

int main()
{
	cin.tie(NULL);
	cout.tie(0);
	ios_base::sync_with_stdio(false);

	cin >> N >> A >> B >> C >> D;

	//A*C ���� (A�� C�� �����)��ŭ ��ٰ� �������� ��, �� ���� ���� ���� ���� ���� ������ ����.
	//C�� ������ �� ���� ������ش�.
	if (C * B < D * A)
	{
		swap(A, C);
		swap(B, D);
	}

	long long limit{ (long long)ceil((double)N / (double)A) };

	//B�� C�� �̻� �� �ʿ䰡 ����. D�� A�� ��� �Ǳ� �����̴�.
    //B�� C�� �̻� ��� ���� ����. ������ �� ��쿡 ���ؼ��� D�� A�� ��� ������
    //�ٲٸ� �Ǳ� �����̴�. ���� B�� C�� ���Ϸ� ��� �ȴ�.
	for (long long i{ 0 }; i < C; ++i)
	{
		bool over{ false };
		long long left = (long long)ceil((double)(N - i * A) / (double)C);

		if (left < 0)
		{
			left = 0;
			over = true;
		}

		result = min(result, B * i + D * left);

		if (over)
			break;
	}

	cout << result;

	return 0;
}