#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
class width
{
private:
    struct node
    {
        char ch,color;
        node *next;
    };
    vector<node*>a;
    int siz;
public:
    void input()
    {
        int n,i;
        char c;
        cout<<"Enter the no. of vertices: \n";
        cin>>siz;
        cout<<"Enter vertex: \n";
        for(i=0;i<siz;i++)
        {
            cin>>c;
            node *t=new node;
            t->ch=c;
            t->color='w';
            t->next=NULL;
            a.push_back(t);
        }
        for(i=0;i<siz;i++)
        {
            cout<<"Enter no. of adjacent vertices of "<<a[i]->ch<<endl;
            cin>>n;
            if(n!=0)cout<<"Enter adjacent vertices of "<<a[i]->ch<<endl;
            for(int j=0;j<n;j++)
            {
                cin>>c;
                node* temp=new node;
                temp->ch=c;
                temp->color='w';
                temp->next=a[i]->next;
                a[i]->next=temp;
            }
        }
        cout<<"\nYour input is "<<endl;
        for(i=0;i<siz;i++)
        {
            cout<<a[i]->ch;
            node *curr=new node;
            curr=a[i];
            while(curr->next!=NULL)
            {
                cout<<" --> "<<curr->next->ch;
                curr=curr->next;
            }
            cout<<endl;
        }
        cout<<"\nEnter source node: \n";
        cin>>c;
        DFS(c);
        display(c);
    }
    void DFS(char c)
    {
        int i;
        for(i=0;i<siz;i++){if(a[i]->ch==c)break;}
        a[i]->color='b';
        color(a[i]->ch);
        node *t=new node;
        stack<node*>q;
        q.push(a[i]);
        cout<<endl;
        while(!q.empty())
        {
            t=q.top();
            cout<<t->ch<<" ";
            q.pop();
            c=t->ch;
            for(i=0;i<siz;i++)
            {
                if(a[i]->ch==c)
                {
                    t=a[i];
                    break;
                }
            }
            while(t->next!=NULL )
            {
                if(t->next->color=='w')
                {
                    color(t->next->ch);
                    q.push(t->next);
                }
                t=t->next;
            }
        }
        cout<<endl;
    }
    void color(char c)
    {
        for(int i=0;i<siz;i++)
        {
            node *curr=new node;
            curr=a[i];
            while(curr!=NULL)
            {
               if(curr->ch==c)curr->color='b';
               curr=curr->next;
            }
        }
    }
    void display(char c)
    {
        int i,index,check=0;
        for(i=0;i<siz;i++)
        {
            node *curr=new node;
            curr=a[i];
            while(curr!=NULL)
            {
               curr->color='w';
               curr=curr->next;
            }
            if(a[i]->ch==c)index=i;
        }
        a[index]->color='b';
        color(a[index]->ch);
        node *t=new node;
        stack<node*>q1;
        q1.push(a[index]);
        while(!q1.empty())
        {
            cout<<endl;
            stack<node*>q2;
            while(!q1.empty())
            {
                check=0;
                t=q1.top();
                q1.pop();
                c=t->ch;
                if(c!='z')cout<<c;
                else cout<<" ";
                for(i=0;i<siz;i++)
                {
                    if(a[i]->ch==c)
                    {
                        t=a[i];
                        break;
                    }
                }
                while(t->next!=NULL )
                {
                    if(t->next->color=='w')
                    {
                        color(t->next->ch);
                        q2.push(t->next);
                    }
                    t=t->next;
                    check++;
                }
                if(t->next==NULL && check!=0)
                {
                    node *p=new node;
                    p->ch='z';
                    p->next=NULL;
                    q2.push(p);
                }
            }
            q1=q2;
        }
    }
};
main()
{
    width obj;
    obj.input();
}
