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

int L, K, C;
vector<int> Points;
int Result{ INF };
int FirstPoint{ INF };


void Input()
{
	cin >> L >> K >> C;

	for (int i{ 0 }; i < K; ++i)
	{
		int Temp;
		cin >> Temp;

		Points.push_back(Temp);
	}
}

bool IsValid(int Len)
{
	int Cnt{ 0 };

	//직전 잘랐던 포인트
	int PrevPoint{ L };
	//앞으로 자를 포인트
	int NextPoint{ L };
	bool bValid{ true };

	//뒤에서 최대 길이로 자르기 시작한다.

	for (int i{ (int)Points.size() - 1 }; i >= 0; --i)
	{
		NextPoint = (i == 0 ? 0 : Points[i - 1]);

		//자르려는 구간의 길이가 최대 길이인 Len보다 크다면 false;
		if (PrevPoint - Points[i] > Len)
			return false;

		//현재 구간은 Len보다 작지만, 다음 포인트를 포함했을 때 Len보다 커진다면
		//현재 구간에서 잘라야 하므로 NextPoint를 사용하여 평가한다.
		if (PrevPoint - NextPoint > Len)
		{
			//잘라야 하지만 이미 제한 횟수를 모두 사용했다면 false
			if (Cnt == C)
				return false;

			PrevPoint = Points[i];
			++Cnt;
		}
	}

	//자르기를 완료한 상태에서 남은 길이가 Len보다 크다면 false
	if (PrevPoint > Len)
		return false;

	FirstPoint = PrevPoint;
	Result = Len;

	//만약 자르기를 완료한 상태에서 자를 횟수가 남았다면( 남은 구간은 Len보다 작은 상태 )
	//무조건 첫 번째 포인트를 자를 수 있다.
	if (Cnt < C)
		FirstPoint = Points[0];

	return bValid;
}

void Bsearch()
{
	int Left{ 1 };
	int Right{ L };

	//최대 길이에 대한 이분 탐색이다.
	while (Left <= Right)
	{
		int Middle{ (Left + Right) / 2 };

		if (IsValid(Middle))
		{
			Right = Middle - 1;
		}
		else
		{
			Left = Middle + 1;
		}
	}
}

void Solve()
{
	sort(Points.begin(), Points.end());
	Points.erase(unique(Points.begin(), Points.end()), Points.end());

	Bsearch();

	cout << Result << ' ' << FirstPoint;
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	Input();
	Solve();

	return 0;
}