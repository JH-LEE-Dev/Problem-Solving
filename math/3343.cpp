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

	//A*C 개수 (A와 C의 공배수)만큼 산다고 가정했을 때, 더 작은 값을 가진 쪽이 묶음 가성비가 높다.
	//C의 가성비가 더 좋게 만들어준다.
	if (C * B < D * A)
	{
		swap(A, C);
		swap(B, D);
	}

	long long limit{ (long long)ceil((double)N / (double)A) };

	//B를 C번 이상 살 필요가 없다. D를 A번 사면 되기 때문이다.
    //B를 C번 이상 사는 경우는 없다. 이유는 이 경우에 대해서는 D를 A번 사는 것으로
    //바꾸면 되기 때문이다. 따라서 B는 C번 이하로 사게 된다.
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