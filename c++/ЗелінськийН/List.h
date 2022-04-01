#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <iostream>

using namespace std;

typedef int datatype;

struct Node
{
    datatype key;
    Node* next;
    Node* previous;
};

class List
{
    Node*  front, * end, * rear;
public:
    List() { front = NULL; end = NULL; rear = NULL; }
    ~List() {};
    void push(datatype data);
    datatype pop();
    void enqueue(datatype data);
    datatype dequeue();
    bool stackempty();
    void show();
    void add_begin(datatype data);
    void add_end(datatype data);
    void search(datatype data);
    datatype del_begin();
    datatype del_end();
    void add_mid(datatype data, datatype data1);
    void del_mid(datatype data);
};


#endif // LIST_H_INCLUDED


