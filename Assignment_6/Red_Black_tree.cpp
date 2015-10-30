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
      char color;
      node *parent,*left,*right;
    };
    node *temp,*root,*curr,*t,*NIL;
    int size;
public:
    tree()
    {
        root=NULL;
        NIL->data=-32767;
        NIL->left=NIL->right=NIL->parent=NULL;
        NIL->color='B';
        t=NULL;
    }
    void input()
    {
        int n,choice,check=0;
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
          cout<<"\n1. Insert \n2. Delete\n3. Search\n4. Display without black height\n5. Display with black height\n6. Exit\nEnter your choice : \n";
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
                    display();
                    break;
                }
                case 5:
                {
                    display_with_height();
                    break;
                }
            case 6:
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
  void inorder(node *x)
    {
        if(x!=NIL)
        {
           inorder(x->left);
           cout<<x->data<<"\t"<<x->parent->data<<"\t"<<x->left->data<<"\t"<<x->right->data<<"\t"<<x->color<<"\n";
           inorder(x->right);
        }
    }
    void insert(int x)
    {
        int i=0;
        node *temp=new node;
        temp->data=x;
        temp->color='R';
        temp->parent=temp->left=temp->right=NIL;
        if(root==NULL)
        {
            temp->color='B';
            root=temp;
        }
        else
        {
            curr=root;
            while(curr!=NIL)
            {
                t=curr;
                if(curr->data>x)curr=curr->left;
                else curr=curr->right;
            }
            temp->parent=t;
            curr=temp;
            if(x>t->data)t->right=temp;
            else t->left=temp;
            if(t->color!='B')insertion_fix_up(temp);
        }
    }
    void insertion_fix_up(node *z)
    {
        if(z->parent==NIL || z->parent==NULL)
        {
            z->color='B';
            return;
        }
        if(z->parent->color=='B')return;
        node *y=z->parent->parent;
        if(y->left==z->parent)
        {
            if(y->right->color=='R')
            {
                z->parent->color='B';
                y->right->color='B';
                y->color='R';
                insertion_fix_up(y);
            }
            else
            {
                if(z->parent->right==z)
                {
                    node *p=z->parent;
                    left_rotation(z->parent);
                    insertion_fix_up(p);
                }
                else
                {
                    right_rotation(z->parent->parent);
                    z->parent->color='B';
                    z->parent->right->color='R';
                }
            }
        }
        else
        {
            if(y->left->color=='R')
            {
                z->parent->color='B';
                y->left->color='B';
                y->color='R';
                insertion_fix_up(y);
            }
            else
            {
                if(z->parent->left==z)
                {
                    node *p=z->parent;
                    right_rotation(z->parent);
                    insertion_fix_up(p);
                }
                else
                {
                    left_rotation(z->parent->parent);
                    z->parent->color='B';
                    z->parent->left->color='R';
                }
            }
        }
    }
    void right_rotation(node *m)                    //function for right rotation
    {
        t=m->left;
        t->parent=m->parent;
        if(m->parent==NIL)root=t;
        else if(m->parent->right==m)m->parent->right=t;
        else m->parent->left=t;
        node *tr=t->right;
        m->parent=t;
        t->right=m;
        m->left=tr;
        if(tr!=NIL)tr->parent=m;
    }
    void left_rotation(node *z)                    //function for left rotation
    {
        t=z->right;
        t->parent=z->parent;
        if(z->parent==NIL)root=t;
        else if(z->parent->right==z)z->parent->right=t;
        else z->parent->left=t;
        node *tl=t->left;
        z->parent=t;
        t->left=z;
        z->right=tl;
        if(tl!=NIL)tl->parent=z;
    }
    void deletenode(int x)
    {
        cout<<"Path--->"<<endl;
        curr=root;
        while(curr!=NIL && curr->data!=x)
        {
            cout<<curr->data<<"\t"<<curr->color<<endl;
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        node *y=curr;
        node *z;
        char y_original_color=y->color;
        if(curr==NIL){cout<<x<<" not found"<<endl;return;}
        else if(curr->left==NIL)
        {
            z=curr->right;
            transplant(curr,curr->right);
        }
        else if(curr->right==NIL)
        {
            z=curr->left;
            transplant(curr,curr->left);
        }
        else
        {
            y=curr->right;
            while(y->left!=NIL)y=y->left;
            y_original_color=y->color;
            z=y->right;
            if(y->parent!=curr)
            {
                transplant(y,y->right);
                y->right=curr->right;
                y->right->parent=y;
                transplant(curr,y);
                y->left=curr->left;
                y->left->parent=y;
                y->color=curr->color;
            }
            else
            {
                transplant(y,y->right);
                y->right=curr->right;
                y->right->parent=y;
                transplant(curr,y);
                y->left=curr->left;
                y->left->parent=y;
                y->color=curr->color;
                if(z==NIL)z->parent=y;
            }
        }
        if(y_original_color=='B')delete_fixup(z);
    }
    void transplant(node *u,node *v)
    {
        if(u->parent==NIL)root=v;
        else if(u==u->parent->left)u->parent->left=v;
        else u->parent->right=v;
        v->parent=u->parent;
    }
    void delete_fixup(node *z)
    {
        while(z!=root && z->color=='B')
        {
            if(z->parent->left==z)
            {
                node *w=z->parent->right;
                if(w->color=='R')
                {
                    w->color='B';
                    z->parent->color='R';
                    left_rotation(z->parent);
                    w=z->parent->right;
                }
                if(w->left->color=='B' && w->right->color=='B')
                {
                    w->color='R';
                    z=z->parent;
                }
                else if(w->right->color=='B')
                {
                    w->left->color='B';
                    w->color='R';
                    right_rotation(w);
                    w=z->parent->right;
                }
                else
                {
                    w->color=z->parent->color;
                    z->parent->color='B';
                    w->right->color='B';
                    left_rotation(z->parent);
                    z=root;
                }
            }
        else
            {
                node *w=z->parent->left;
                if(w->color=='R')
                {
                    w->color='B';
                    z->parent->color='R';
                    right_rotation(z->parent);
                    w=z->parent->left;
                }
                if(w->left->color=='B' && w->right->color=='B')
                {
                    w->color='R';
                    z=z->parent;
                }
                else if(w->left->color=='B')
                {
                    w->right->color='B';
                    w->color='R';
                    left_rotation(w);
                    w=z->parent->left;
                }
                else
                {
                    w->color=z->parent->color;
                    z->parent->color='B';
                    w->left->color='B';
                    right_rotation(z->parent);
                    z=root;
                }
            }
        }
        z->color='B';
    }
    void search(int x)                  //function to search an integer
    {
        cout<<"Path--->"<<endl;
        curr=root;
        while(curr!=NIL && curr->data!=x)
        {
            cout<<curr->data<<"\t"<<curr->color<<endl;
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        if(curr==NIL)cout<<x<<" not found\n";
        else cout<<x<<" found\n";
    }
    int black_height(node *x)
    {
        int i=0;
        curr=x;
        while(curr!=NULL)
        {
            if(curr->color=='B')i++;
            curr=curr->right;
        }
        if(x->color=='B')return i-1;
        else return i;
    }
    void display_with_height()
    {
        cout<<endl<<"Read tuple as (value,color,black height): "<<endl;
        int check=1,i=0,k,l=level(root);
        node *a=new node;
        a->data=-32767;
        a->left=a->parent=a->right=NIL;
        queue<node*>queue1;
        queue1.push(root);
        while(!queue1.empty()&& check!=0 && i<l)
        {
            check=0;
            cout<<endl;
            queue<node*>queue2;
            for(k=0;k<4*((pow(2,l-i))-2);k++)cout<<" ";
            while(!queue1.empty())
            {
            t=queue1.front();
            queue1.pop();
            if(t->data!=-32767)
            cout<<"("<<t->data<<","<<t->color<<","<<black_height(t)<<")";
            else cout<<"       ";
            for(k=0;k<4*((pow(2,l-i+1))-2)+1;k++)cout<<" ";
            if(t->left!=NIL)
            {
                queue2.push(t->left);
                check++;
            }
            else queue2.push(a);
            if(t->right!=NIL)
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
        void display()
    {
        int check=1,i=0,k,l=level(root);
        node *a=new node;
        a->data=-32767;
        a->left=a->right=a->parent=NIL;
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
            if(t->left!=NIL)
            {
                queue2.push(t->left);
                check++;
            }
            else queue2.push(a);
            if(t->right!=NIL)
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
                if(t->left!=NIL)queue2.push(t->left);
                if(t->right!=NIL)queue2.push(t->right);
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
