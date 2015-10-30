/* Name-Akanksha Gupta */

#include<iostream>
#include<cmath>
#include<queue>
using namespace std;
class tree
{
private:
    struct node
    {
      int data;
        node *parent,*left,*right;
    };
    node *temp,*root,*curr,*t;
    int size;
public:
    tree()
    {
        root=NULL;
        t=NULL;
    }
   void input()
    {
        int n,choice,check=0;;
        cout<<"Enter the size"<<endl;
        cin>>size;
        cout<<"Enter the elements"<<endl;
        for(int i=0;i<size;i++)
            {
                cin>>n;
                insert(n);
            }
        cout<<"\nNumber of levels are "<<level(root)<<endl;
       do
        {
          cout<<"\nTo insert numbers enter 1 \nTo delete any element enter 2 \nTo search any element enter 3 \nTo know minimum number enter 4\nTo know maximum number enter 5\nTo know predecessor of any number enter 6\nTo know successor of any number enter 7\nFor inorder traverse enter 8\nTo display tree enter 9\nTo exit enter 10\nEnter your choice : \n";
          cin>>choice;
          switch(choice)
            {
            case 1:
                {
                cout<<"Enter number : \n";
                cin>>n;
                insert(n);
                break;
                }
            case 2:
                {
                    cout<<"Enter no. to delete"<<endl;
                    cin>>n;
                    deletenode(n);
                    break;
                }
             case 3:
              {
                cout<<"Enter the element to search \n";
                cin>>n;
                search(n);
                break;
              }
            case 4:
              {
                cout<<"minimum is "<<(minimum(root))->data<<endl;
                break;
              }
            case 5:
              {
                cout<<"maximum is "<<(maximum(root))->data<<endl;
                break;
              }
            case 6:
                {
                    cout<<"Enter number "<<endl;
                    cin>>n;
                    predecessor(n);
                    break;
                }
            case 7:
                {
                    cout<<"Enter number "<<endl;
                    cin>>n;
                    successor(n);
                    break;
                }
            case 8:
                {
                    inorder(root);
                    break;
                }
            case 9:
                {
                    display();
                    break;
                }
            case 10:
              {
                check=1;
                break;
              }
            default:
              {
                cout<<"Invalid Choice\n";
              }
                }
            }while(check==0);
  }
    void insert(int x)
    {
        int i=0;
        node *temp=new node;
        temp->data=x;
        temp->parent=temp->left=temp->right=NULL;
        if(root==NULL)
        {
            root=temp;
            i++;
        }
        else
        {
            curr=root;i++;
            while(curr!=NULL)
            {
                t=curr;
                if(curr->data>x)curr=curr->left;
                else curr=curr->right;
                i++;
            }
            temp->parent=t;
            curr=temp;
            if(x>t->data)t->right=temp;
            else t->left=temp;
        }
        cout<<"Allocated level "<<i<<endl;
    }
    void deletenode(int x)
    {
        cout<<"Path--->"<<endl;
        curr=root;
        while(curr!=NULL && curr->data!=x)
        {
            cout<<curr->data<<endl;
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        if(curr==NULL)cout<<x<<" not found"<<endl;
        else if(curr->left==NULL)transplant(curr,curr->right);
        else if(curr->right==NULL)transplant(curr,curr->left);
        else
        {
            t=minimum(curr->right);
            if(t->parent!=curr)
            {
                transplant(t,t->right);
                t->right=curr->right;
                t->right->parent=t;
            }
            transplant(curr,t);
            t->left=curr->left;
            t->left->parent=t;
        }
    }
    void transplant(node *u,node *v)
    {
        if(u->parent==NULL) root=v;
        else if(u==u->parent->left)u->parent->left=v;
        else u->parent->right=v;
        if(v!=NULL)v->parent=u->parent;
    }
    void inorder(node *x)
    {
        if(x!=NULL)
        {
           inorder(x->left);
           cout<<x->data<<"\t";
           inorder(x->right);
        }
    }
    void search(int x)
    {
        cout<<"Path--->"<<endl;
        curr=root;
        while(curr!=NULL && curr->data!=x)
        {
            cout<<curr->data<<endl;
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        if(curr==NULL)cout<<x<<" not found\n";
        else cout<<x<<" found\n";
    }
    node* minimum(node *a)
    {
        while(a->left!=NULL)a=a->left;
        return a;
    }
    node* maximum(node *x)
    {
        while(x->right!=NULL)x=x->right;
        return x;
    }
    int successor(int x)
    {
        curr=root;
        while(curr!=NULL && curr->data!=x)
        {
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        if(curr==NULL)cout<<"data not found\n";
        else if(curr->right!=NULL)cout<<"successor is "<<(minimum(curr->right))->data<<endl;
        else
        {
            t=curr->parent;
            while(t!=NULL && curr==t->right)
            {
                curr=t;
                t=t->parent;
            }
           if(t!=NULL)cout<<"successor is "<<t->data<<endl;
           else cout<<"successor not found\n";
        }
    }
    int predecessor(int x)
    {
        curr=root;
        while(curr!=NULL && curr->data!=x)
        {
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        if(curr==NULL)cout<<"data not found\n";
        else if(curr->left!=NULL)cout<<"predecessor is "<<(maximum(curr->left))->data<<endl;
        else
        {
            t=curr->parent;
            while(t!=NULL && curr==t->left)
            {
                curr=t;
                t=t->parent;
            }
           if(t!=NULL)cout<<"predecessor is "<<t->data<<endl;
           else cout<<"predecessor not found"<<endl;
        }
    }
    void display()
    {
        int check=1,i=0,k,l=level(root);
        node *a=new node;
        a->data=-32767;
        a->left=a->right=NULL;
        queue<node*>queue1;
        queue1.push(root);
        while(!queue1.empty()&& check!=0 && i<l)
        {
            check=0;
            cout<<endl;
            queue<node*>queue2;
            for(k=0;k<(pow(2,l-i))-2;k++)cout<<" ";
            while(!queue1.empty())
            {
            t=queue1.front();
            queue1.pop();
            if(t->data!=-32767)
            cout<<t->data;
            else cout<<" ";
            for(k=0;k<(pow(2,l-i+1))-1;k++)cout<<" ";
            if(t->left!=NULL)
            {
                queue2.push(t->left);
                check++;
            }
            else queue2.push(a);
            if(t->right!=NULL)
            {
                queue2.push(t->right);
                check++;
            }
            else queue2.push(a);
            }
            queue1=queue2;
            i++;
        }
        }
    int level(node *x)
        {
            int i=0;
            queue<node*>queue1;
            queue1.push(x);
            while(!queue1.empty())
            {
                queue<node*>queue2;
                while(!queue1.empty())
                {
                t=queue1.front();
                queue1.pop();
                if(t->left!=NULL)queue2.push(t->left);
                if(t->right!=NULL)queue2.push(t->right);
                }
                queue1=queue2;
                i++;
             }
             return i;
        }
};
main()
{
    tree o;
    o.input();
}
