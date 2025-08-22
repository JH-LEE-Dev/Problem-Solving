#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define endl '\n'
using namespace std;

vector<string> arr(105);

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    string input;
    int N{ 0 }, counting{ 0 };
    int src_count{ 0 };
    cin >> N;

    for (int i{ 0 }; i < N; ++i)
    {
        cin >> arr[i];
    }

    input = arr[0];
    unordered_map<char, int> src;

    sort(input.begin(), input.end());

    for (int i{ 0 }; i < input.size(); ++i)
    {
        if (src.find(input[i]) == src.end())
        {
            src.insert({ input[i],1 });
            ++src_count;
        }
        else
        {
            ++src[input[i]];
            ++src_count;
        }
    }

    for (int i{ 1 }; i < N; ++i)
    {
        int dst_count{ 0 };

        if (abs((int)arr[i].size() - (int)input.size()) > 1)
        {
            continue;
        }
        else
        {
            unordered_map<char, int> dst;

            if (arr[i].size() == (int)input.size())
            {
                for (int j{ 0 }; j < input.size(); ++j)
                {
                    if (src.find(arr[i][j]) != src.end())
                    {
                        if (dst.find(arr[i][j]) != dst.end())
                        {
                            if (src[arr[i][j]] > dst[arr[i][j]])
                            {
                                ++dst[arr[i][j]];
                                ++dst_count;
                            }
                        }
                        else
                        {
                            dst.insert({ arr[i][j],1 });
                            ++dst_count;
                        }
                    }
                }

                if (dst_count >= src_count - 1)
                {
                    ++counting;
                }
            }
            else
            {
                for (int j{ 0 }; j < arr[i].size(); ++j)
                {
                    if (src.find(arr[i][j]) != src.end())
                    {
                        if (dst.find(arr[i][j]) != dst.end())
                        {
                            if (src[arr[i][j]] > dst[arr[i][j]])
                            {
                                ++dst[arr[i][j]];
                                ++dst_count;
                            }
                        }
                        else
                        {
                            dst.insert({ arr[i][j],1 });
                            ++dst_count;
                        }
                    }
                }

                if (input.size() > arr[i].size())
                {
                    if (dst_count >= src_count - 1)
                    {
                        ++counting;
                    }
                }
                else
                {
                    if (dst_count >= src_count)
                    {
                        ++counting;
                    }
                }
            }
        }
    }

    cout << counting;

    return 0;
}