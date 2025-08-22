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

#define endl '\n'
#define INF numeric_limits<int>::max()
using namespace std;

#define MAX 100'001

int N{ 0 };
int total{ 0 };
priority_queue<int, vector<int>, greater<int>> myPQ;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int input;
		cin >> input;
		myPQ.push(input);
	}

	while (myPQ.size() != 1)
	{
		if (myPQ.size() > 1)
		{
			int left = myPQ.top();
			myPQ.pop();
			int right = myPQ.top();
			myPQ.pop();

			int newCard = left + right;

			total += (newCard);

			myPQ.push(newCard);
		}
	}

	cout << total;

	return 0;
}