#include <iostream>
#include "../../Lab_4/LAB4/List.h"
#define N 8
string rib;
void Dfs(int vertex);
using namespace std;

    int i, j;
    int DFS=1;
    int BFS=1;
    bool visited[N];
    int dfsnumber[N];
    int bfsnumber[N];
    int start=0;
    int Adj [N][N] = {{1,1,1,1,0,0,1,1},
                      {1,0,0,0,0,0,1,1},
                      {1,0,0,0,0,0,0,0},
                      {1,0,0,0,1,1,0,0},
                      {0,0,0,1,0,1,0,0},
                      {0,0,0,1,1,0,0,0},
                      {1,1,0,0,0,0,0,1},
                      {1,1,0,0,0,0,1,0}};

int main()
{
    head=front = rear=NULL;
    Item *temp;
    DFS=0;
    cout<<"Select method: \n"<<"1)NotRecursive;\n2)Recursive;\n3)BreadthFirstSearch;\n";
    i=0;
    cin>>i;
    switch(i)
    {
        case 1:
    visited[start]=true;
    dfsnumber[start]=++DFS;
    push(start);
    cout<<"V"<<(head->data)<<"   "<<dfsnumber[head->data]<<"   <->";
    temp = head;
    while(temp != NULL)
    {
        cout<<"V"<<temp->data;
        temp = temp->next;
    }
    cout<<endl;
    while(head!=NULL)
    {
        i=head->data;
        for(j=0; j<N; j++)
        {
            if(Adj[i][j]==1)
                if(visited[j]==false)
                    break;
        }
        if(j>=N)
            j=N-1;
        if(visited[j]==false)
            {
                visited[j]=true;
                dfsnumber[j]=++DFS;
                push(j);
                cout<<"V"<<head->data<<"   "<<dfsnumber[head->data]<<"   <->";
                Item *temp = head;
                while(temp != NULL)
                {
                    cout<<"V"<<temp->data;
                    temp = temp->next;
                }
                cout<<"   {V"<<i<<",V"<<j<<"}"<<endl;
            }
            else
            {
                pop();
                Item *temp = head;
                if(temp==NULL)
                cout<<" -"<<"   -"<<"   <->NULL"<<endl;
                else
                {
                    cout<<" -"<<"   -"<<"   <->";
                    while(temp != NULL)
                    {
                        cout<<"V"<<temp->data;
                        temp = temp->next;
                    }
                    cout<<endl;
                }
            }
    }
    break;
    case 2:
        Dfs(start);
    break;
    case 3:
        visited[start]=true;
        bfsnumber[start]=1;
        enqueue(start);
        cout<<"V"<<(rear->data)<<"   "<<bfsnumber[rear->data]<<"   <--";
        temp = front;
        while(temp != NULL)
    {
        cout<<"V"<<temp->data;
        temp = temp->next;
    }
    cout<<"<--"<<endl;
        while(front!=NULL)
    {
        i=front->data;

        for(j=0; j<N; j++)
        {
            if(Adj[i][j]==1)
                if(visited[j]==false)
                    break;
        }
        if(j>=N)
            j=N-1;
        if(visited[j]==false)
            {
                visited[j]=true;
                bfsnumber[j]=++BFS;
                enqueue(j);
                cout<<"V"<<rear->data<<"   "<<bfsnumber[rear->data]<<"   <--";
                Item *temp = front;
                while(temp != NULL)
                {
                    cout<<"V"<<temp->data;
                    temp = temp->next;
                }
                cout<<"<--   {V"<<i<<",V"<<j<<"}"<<endl;
            }
            else
            {
                dequeue();
                Item *temp = front;
                if(temp==NULL)
                cout<<" -"<<"   -"<<"   <--NULL<--"<<endl;
                else
                {
                    cout<<" -"<<"   -"<<"   <--";
                    while(temp != NULL)
                    {
                        cout<<"V"<<temp->data;
                        temp = temp->next;
                    }
                    cout<<"<--"<<endl;
                }
            }
        }
    }

}
void Dfs(int vertex)
{
    visited[vertex]=true;
    dfsnumber[vertex]=++DFS;
    cout<<"V"<<vertex<<"   "<<dfsnumber[vertex]<<endl;
    for(int j=0; j<N; j++)
        {
            if(Adj[vertex][j]==1)
                if(visited[j]==false)
                   {
                       cout<<"   {V"<<vertex<<",V"<<j<<"}"<<endl;
                       Dfs(j);
                   }
        }
}
