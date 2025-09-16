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
#include <bitset>
#include <iomanip>

using namespace std;

#define endl '\n'
#define INF numeric_limits<int>::max()
#define MAX 10'000'005

int N, T;
vector<bool> CheckPrime(MAX, true);
vector<int> PrimeArr;
vector<int> Arr;
int Max;

void CalcPrime(int N)
{
	CheckPrime[0] = false;
	CheckPrime[1] = false;

	for (int i{ 2 }; i * i <= N; ++i)
	{
		if (CheckPrime[i])
		{
			for (int j{ i * i }; j <= N; j += i)
			{
				CheckPrime[j] = false;
			}
		}
	}

	for (int i = 2; i <= N; ++i)
	{
		if (CheckPrime[i])
			PrimeArr.push_back(i);
	}
}

void Input()
{
	cin >> N;

	Arr.clear();

	for (int i{ 0 }; i < N; ++i)
	{
		int Temp;
		cin >> Temp;

		Arr.push_back(Temp);

		Max = max(Max, Arr[i]);
	}

	sort(Arr.begin(), Arr.end());
}

int SWindow()
{
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> PQ;

	int Sum{ 0 };
	int Idx{ 0 };

	unordered_set<int> Check;

	for (int i{ 0 }; i < Max; ++i)
	{
		Sum += PrimeArr[i];

		if (Idx == Arr.size())
			break;

		if (i == Arr[Idx] - 1)
		{
			PQ.push({ Sum,Idx,0 });
			Check.insert(Sum);
			++Idx;
		}
	}

	while (true)
	{
		if (Check.size() == 1 && CheckPrime[*Check.begin()])
			break;

		auto Min{ PQ.top() };
		PQ.pop();

		auto [CurSum, CurIdx, Start] {Min};
		Check.erase(CurSum);

		CurSum -= PrimeArr[Start];
		CurSum += PrimeArr[Start + Arr[CurIdx]];

		Check.insert(CurSum);

		PQ.push({ CurSum,CurIdx,Start + 1 });
	}

	return *Check.begin();
}

void Solve()
{
	CalcPrime(10'000'000);

	cin >> T;

	int Idx{ 0 };

	while (Idx != T)
	{
		Input();
		cout << "Scenario " << Idx + 1 << ':' << endl << SWindow() << endl << endl;

		++Idx;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Solve();

	return 0;
}