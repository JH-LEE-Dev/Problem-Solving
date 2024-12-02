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
#define INF numeric_limits<int>::max()
using namespace std;

int N{ 0 };
vector<int> arr;
vector<int> result;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i{ 0 }; i < N; ++i)
	{
		int input{ 0 };
		cin >> input;

		arr.push_back(input);
	}

	result.resize(N, -1);

	stack<int> myStack;

	for (int i{ N - 1 }; i >= 0; --i)
	{
		while (true)
		{
			if (myStack.empty())
			{
				result[i] = -1;
				break;
			}

			if (myStack.top() > arr[i])
			{
				result[i] = myStack.top();
				break;
			}
			else
			{
				myStack.pop();
			}
		}
		myStack.push(arr[i]);
	}

	for (auto& num : result)
	{
		cout << num << " ";
	}

	return 0;
}