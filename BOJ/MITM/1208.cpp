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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

vector<int> counting_A;
vector<int> counting_B;
vector<int> arr(1'000'005, 0);
int N{ 0 }, S{ 0 };
long long result{ 0 };

void func_A(int idx, int sum, vector<int>& A)
{
	if (idx == A.size())
	{
		counting_A.push_back(sum);

		return;
	}

	sum += A[idx];

	func_A(idx + 1, sum, A);
	sum -= A[idx];
	func_A(idx + 1, sum, A);
}

void func_B(int idx, int sum, vector<int>& B)
{
	if (idx == B.size())
	{
		counting_B.push_back(sum);

		return;
	}

	sum += B[idx];

	func_B(idx + 1, sum, B);
	sum -= B[idx];
	func_B(idx + 1, sum, B);
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> S;

	for (int i{ 0 }; i < N; ++i)
	{
		cin >> arr[i];
	}

	vector<int> A(arr.begin(), arr.begin() + N / 2);
	vector<int> B(arr.begin() + N / 2, arr.begin() + N);

	func_A(0, 0, A);
	func_B(0, 0, B);

	sort(counting_A.begin(), counting_A.end());
	sort(counting_B.begin(), counting_B.end());

	for (auto& it_A : counting_A)
	{
		result += upper_bound(counting_B.begin(), counting_B.end(), S - it_A) - lower_bound(counting_B.begin(), counting_B.end(), S - it_A);
	}

	if (S == 0)
		result -= 1;

	cout << result;

	return 0;
}