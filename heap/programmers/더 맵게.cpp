#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

priority_queue<int, vector<int>, greater<int>> pQ;

int solution(vector<int> scoville, int K) {
    int answer = 0;

    for (auto& num : scoville)
    {
        pQ.push(num);
    }

    while (pQ.empty() == false)
    {
        int top = pQ.top();
        if (top >= K)
            break;

        int first = pQ.top();
        pQ.pop();
        int second = pQ.top();
        pQ.pop();

        int result = first + (second * 2);

        pQ.push(result);

        ++answer;
    }

    return answer;
}

int main()
{
    vector<int> scoville{ 1,2,3,9,10,12 };
    cout << solution(scoville, 7);

    return 0;
}