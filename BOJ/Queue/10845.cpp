#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T>
class Cir_Q
{
public:
    Cir_Q() {}
    Cir_Q(const int& q_size)
    {
        data.resize(q_size);
        size = q_size;
    }
    void enqueue(const T& val)
    {
        if (!isFull())
        {
            data[tail] = val;
            tail = (tail + 1) % size;
        }
    }
    T dequeue()
    {
        if (!empty())
        {
            T val = data[head];
            head = (head + 1) % size;
        }
        else
        {
            return -1;
        }
    }
    size_t getSize()
    {
        return (tail - head + size) % size;
    }
    T getFront()
    {
        return data[head];
    }
    T getRear()
    {
        return data[(tail - 1 + size) % size];
    }
    bool empty()
    {
        return head == tail;
    }
    bool  isFull()
    {
        return ((tail + 1) % size) == head;
    }
private:
    vector<T> data;
    size_t size;
    int head{ 0 };
    int tail{ 0 };
};

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int count{ 0 };
    cin >> count;
    string order;

    Cir_Q<int> Queue(count);

    while (count != 0)
    {
        cin >> order;

        if (order == "push")
        {
            int val{ 0 };
            cin >> val;
            Queue.enqueue(val);
        }

        if (order == "pop")
        {
            if (Queue.empty())
            {
                cout << -1 << "\n";
            }
            else
            {
                cout << Queue.dequeue() << "\n";
            }
        }

        if (order == "empty")
        {
            if (Queue.empty() == true)
                cout << 1 << "\n";
            else
                cout << 0 << "\n";
        }

        if (order == "size")
        {
            cout << Queue.getSize() << "\n";
        }

        if (order == "front")
        {
            if (!Queue.empty())
                cout << Queue.getFront() << "\n";
            else
                cout << -1 << "\n";
        }

        if (order == "back")
        {
            if (!Queue.empty())
                cout << Queue.getRear() << "\n";
            else
                cout << -1 << "\n";
        }

        --count;
    }

    return 0;
}