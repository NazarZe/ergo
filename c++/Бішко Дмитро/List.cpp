#include "list.h"
#include <iostream>

using namespace std;

void List::push(datatype data)
{
    Node* temp = new Node;
    temp->key = data;
    temp->next = front;
    front = temp;
}
datatype List::pop()
{
    datatype result;
    if (stackempty() == true)
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
    else
    {
        Node* temp = front;
        front = temp->next;
        result = (*temp).key;
        delete temp;
    }
    return result;
}
void List::enqueue(datatype data)
{
    Node* temp = new Node;
    temp->key = data;
    temp->next = NULL;
    if (stackempty() == true) {

        front = temp;
        rear = temp;

    }
    else {

        rear->next = temp;
        rear = temp;

    }
}
void List::add_begin(datatype data)
{
    Node* temp = new Node;
    temp->key = data;
    temp->next = front;
    temp->previous = NULL;
    if (stackempty() == true)
    {


        front = end = temp;

    }
    else
    {

        front->previous = temp;
        front = temp;

    }

}
void List::add_end(datatype data)
{
    Node* temp = new Node;
    temp->key = data;
    temp->next = NULL;
    temp->previous = end;
    if (stackempty() == true)
    {


        front = temp;
        end = temp;

    }
    else
    {

        end->next = temp;
        end = temp;

    }

}
datatype List::dequeue()
{
    datatype result;
    if (stackempty() == true)
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
    else
    {
        Node* temp = front;
        front = temp->next;
        result = (*temp).key;
        delete temp;
    }
    return result;
}
bool List::stackempty()
{
    if (front == NULL) return true;
    else return false;
}
void List::show()
{
    Node* temp = front;
    while (temp != NULL)
    {
        cout << temp->key << " ";
        temp = temp->next;
    }
    cout << endl;
}
datatype List::del_begin()
{
    datatype result;
    if (stackempty() == true)
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
    else
    {
        Node* temp = front;

        if (temp->next == NULL) {
            front = temp->next;
            result = (*temp).key;
            end = NULL;
            delete temp;
        }
        else {


            front = temp->next;
            result = (*temp).key;
            front->previous = NULL;
            delete temp;
        }
    }
    return result;
}
datatype List::del_end()
{
    datatype result;
    if (stackempty() == true)
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
    else
    {
        Node* temp = end;

        if (temp->previous == NULL) {
            end = temp->previous;
            result = (*temp).key;
            front = NULL;
            delete temp;
        }
        else {


            end = temp->previous;
            result = (*temp).key;
            end->next = NULL;
            delete temp;
        }
    }
    return result;
}
void List::search(datatype data) {
    int  k = 1;
    Node* temp = front;
    Node* kuy = NULL;
    while (temp != NULL) {
        if (data == temp->key) {


            kuy = temp;
            cout << kuy << "  " << k;
            break;

        }
        else {

            temp = temp->next;
            k++;

        }
    }
    cout << endl;
}
void List::add_mid(datatype data, datatype data1)
{

    Node* temp = front;
    Node* kuy = NULL;
    while (temp != NULL) {
        if (data == temp->key) {
            kuy = temp;
            break;
        }
        else {
            temp = temp->next;
        }
    }
    if (kuy == end) {

        add_end(data1);

    }
    else {

        Node *temp = new Node;
        temp->key = data1;
        temp->next = kuy->next;
        temp -> previous = kuy;
        kuy->next = temp;
        (temp->next)->previous = temp;
    }

}
void List::del_mid(datatype data)
{
    int data1;
    Node* temp = front;
    Node* kuy = NULL;
    while (temp != NULL) {
        if (data == temp->key) {
            data1 = temp->key;
            kuy = temp;
            break;
        }
        else {
            temp = temp->next;
        }
    }
    if (kuy == end) {

            del_end();

    }
    else {

        if (kuy == front) {

            del_begin();

        }
        else {

            (kuy->previous)->next = kuy->next;
            (kuy->next)->previous = kuy->previous;
            delete kuy;

        }
    }
}

