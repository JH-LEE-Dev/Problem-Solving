#include <iostream>
#include <vector>
using namespace std;

vector<int> arr(1005, 0);

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N{ 0 }, maxScore{ -1 };
	double ave{ 0 };
	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		cin >> arr[i];
		maxScore = max(maxScore, arr[i]);
	}

	for (int i = 0; i < N; ++i)
	{
		ave += (double)arr[i] / (double)maxScore * 100;
	}

	cout.precision(14);
	cout << ave / (double)N;

	return 0;
}
