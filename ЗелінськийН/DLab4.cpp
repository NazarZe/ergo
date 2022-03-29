#include <iostream>
# include "List.h"

using namespace std;

int main()
{
    List A;
    int choice;
    datatype data, result, data1;

    do
    {
        cout << endl;
        cout << "Select action" << endl;
        cout << "1 - Push" << endl;
        cout << "2 - Pop" << endl;
        cout << "3 - Show" << endl;
        cout << "4 - enqueue" << endl;
        cout << "5 - dequeue" << endl;
        cout << "6 - add_begin" << endl;
        cout << "7 - add_end" << endl;
        cout << "8 - del_begin" << endl;
        cout << "9 - del_end" << endl;
        cout << "10 - search" << endl;
        cout << "11 - add_mid" << endl;
        cout << "12 - del_mid" << endl;
        cout << "13 - exit" << endl;
      
        cout << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Input data" << endl;
            cin >> data;
            A.push(data);
            A.show();
            break;
        }
        case 2:
        {
            result = A.pop();
            A.show();
            break;
        }
        case 3:
        {
            A.show();
            break;
        }
        case 4:
        {
        
            cout << "Input data" << endl;
            cin >> data;
            A.enqueue(data);
            A.show();
            break;


        }
        case 5:
        {
            result = A.dequeue();
            A.show();
            break;
        }
        case 6:
        {
            cout << "Input data" << endl;
            cin >> data;
            A.add_begin(data);
            A.show();
            break;
        }
        case 7:
        {
            cout << "Input data" << endl;
            cin >> data;
            A.add_end(data);
            A.show();
            break;
        }
        case 8:
        {
            
            result = A.del_begin();
            A.show();
            break;
        }
        case 9:
        {

            result = A.del_end();
            A.show();
            break;
        }
        case 10:
        {
            cout << "Input data" << endl;
            cin >> data;
            A.search(data);
            
            break;
        }
        case 11:
        {
            cout << "Input data" << endl;
            cin >> data >> data1;
            A.add_mid(data, data1);
            A.show();
            break;
        }
        case 12:
        {
            cout << "Input data" << endl;
            cin >> data;
            A.del_mid(data);
            A.show();
            break;
        }
        }
    }while (choice != 13);
    return 0;
}