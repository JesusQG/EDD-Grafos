#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
    T data;
    Node<T> *next = nullptr;

public:
    Node(T data, Node<T> *next)
    {
        this->data = data;
        this->next = next;
    }
    Node(Node<T> *next)
    {
        this->next = next;
    }
    ~Node()
    {
        this->next = nullptr;
    }
    T getData()
    {
        return this->data;
    }
    void setData(T data)
    {
        this->data = data;
    }
    Node<T> *getNext()
    {
        return this->next;
    }
    void setNext(Node<T> *next)
    {
        this->next = next;
    }
    void print()
    {
        cout << this->data << endl;
    }
};