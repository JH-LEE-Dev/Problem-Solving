#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Cir_Deque
{
public:
    Cir_Deque(const int& deq_size)
    {
        size = deq_size;
        data.resize(deq_size);
    }
    void enqueue_front(const T& val)
    {
        if (!isFull())
        {
            head = (head - 1 + size) % size;
            data[head] = val;
        }
    }
    void enqueue_rear(const T& val)
    {
        if (!isFull())
        {
            data[tail] = val;
            tail = (tail + 1) % size;
        }
    }
    T dequeue_front()
    {
        if (!empty())
        {
            T returnValue{ data[head] };
            head = (head + 1) % size;
            return returnValue;
        }
    }
    T dequeue_rear()
    {
        if (!empty())
        {
            tail = (tail - 1 + size) % size;
            return data[tail];
        }
    }
    bool isFull()
    {
        return (tail + 1) % size == head;
    }
    bool empty()
    {
        return (head == tail);
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
        return data[(tail - 1) % size];
    }
private:
    size_t size{ 0 };
    vector<int>    data;
    int head{ 0 };
    int tail{ 0 };
};

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int count{ 0 };
    cin >> count;

    Cir_Deque<int> Deque(count);

    while (count != 0)
    {
        string order;
        cin >> order;

        if (order == "push_front")
        {
            int val{ 0 };
            cin >> val;
            Deque.enqueue_front(val);
        }

        if (order == "push_back")
        {
            int val{ 0 };
            cin >> val;
            Deque.enqueue_rear(val);
        }

        if (order == "pop_front")
        {
            if (Deque.empty())
                cout << -1 << "\n";
            else
                cout << Deque.dequeue_front() << "\n";
        }

        if (order == "pop_back")
        {
            if (Deque.empty())
                cout << -1 << "\n";
            else
                cout << Deque.dequeue_rear() << "\n";
        }

        if (order == "size")
        {
            cout << Deque.getSize() << "\n";
        }

        if (order == "empty")
        {
            if (Deque.empty())
                cout << 1 << "\n";
            else
                cout << 0 << "\n";
        }

        if (order == "front")
        {
            if (Deque.empty())
                cout << -1 << "\n";
            else
                cout << Deque.getFront() << "\n";
        }

        if (order == "back")
        {
            if (Deque.empty())
                cout << -1 << "\n";
            else
                cout << Deque.getRear() << "\n";
        }
        --count;
    }

    return 0;
}