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
    void input()                     //function to take input
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
        cout<<"\nNumber of levels are "<<level(root);
       do
        {
          cout<<"\n1.  insert\n2.  delete\n3.  search \n4.  minimum\n5.  maximum\n6.  Predecessor\n7.  successor\n8.  height and bf of any node\n9.  inorder traverse\n10. display tree without height and bf\n11. display tree with height and bf\n12. exit\nEnter your choice : \n";
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
                    int a;
                    cout<<"Enter number "<<endl;
                    cin>>a;
                    height_and_bf(a);
                    break;
                }
            case 9:
                {
                    inorder(root);
                    break;
                }
            case 10:
                {
                    display_without_height();
                    break;
                }
	         case 11:
                {
                    display();
                    break;
                }
            case 12:
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
    void insert(int x)  //function to insert number
    {
        node *temp=new node;
        temp->data=x;
        temp->parent=temp->left=temp->right=NULL;
        if(root==NULL)root=temp;
        else
        {
            curr=root;
            while(curr!=NULL)      //search for right place
            {
                t=curr;
                if(curr->data>x)curr=curr->left;
                else curr=curr->right;
            }
            temp->parent=t;       //insert number at right place
            curr=temp;
            if(x>t->data)t->right=temp;
            else t->left=temp;
        }
        if(level(root)-level(temp)>=2) //if height of tree is greater than 1 then check bf of nodes
        {
        node *z=t->parent->parent;    //start from grand parent of inserted node
        while(z!=NULL)
          {
            node *b=z->parent;        //then go up till root
            balance(z);               //function call for rotations according to bf
            z=b;
          }
        }
    }
    void balance(node *z)             //function for balancing of tree
    {
        node *y=new node;
        if(bfactor(z)==2)
            {
                y=z->left;
                if(bfactor(y)==1)right_rotation(z);     //case 1: imbalance at node z due to the left sub tree of left child of z
                else                                    //case 3: Imbalance at node z due to the right sub tree of left child of z

                {
                    if(bfactor(y)==-1)left_rotation(y);
                    right_rotation(z);
                }
            }
        if(bfactor(z)==-2)
            {
                y=z->right;
                if(bfactor(y)==-1)left_rotation(z);     //case 2: Imbalance at node z due to the right sub tree of right child of z
                else                                    //case 4: Imbalance at node z due to the left sub tree of right child of z
                {
                    if(bfactor(y)==1)right_rotation(y);
                    left_rotation(z);
                }
            }
    }
    void right_rotation(node *z)                    //function for right rotation
    {
        t=z->left;
        t->parent=z->parent;
        if(z->parent==NULL)root=t;
        else if(z->parent->right==z)z->parent->right=t;
        else z->parent->left=t;
        node *tr=t->right;
        z->parent=t;
        t->right=z;
        z->left=tr;
        if(tr!=NULL)tr->parent=z;
    }
    void left_rotation(node *z)                    //function for left rotation
    {
        t=z->right;
        t->parent=z->parent;
        if(z->parent==NULL)root=t;
        else if(z->parent->right==z)z->parent->right=t;
        else z->parent->left=t;
        node *tl=t->left;
        z->parent=t;
        t->left=z;
        z->right=tl;
        if(tl!=NULL)tl->parent=z;
    }
    int bfactor(node *x)                            //function to calculate balancing factor of node x
    {
        int bf;                                     // bf = height of left - height of right
        if(x->left==NULL && x->right!=NULL)bf=-level(x->right);
        else if(x->right==NULL && x->left!=NULL)bf=level(x->left);
        else if(x->left==NULL && x->right==NULL)bf=0;
        else bf=level(x->left)-level(x->right);
        return bf;
    }
    void deletenode(int x)                          //function to delete
    {
        cout<<"Path--->"<<endl;
        curr=root;
        node *z=new node;
        while(curr!=NULL && curr->data!=x)          //search for node to delete
        {
            cout<<curr->data<<endl;
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        if(curr==NULL)
        {
            cout<<x<<" not found"<<endl;
            return;
        }
        else if(curr->left==NULL)                   //case 1: left is NULL
        {
            transplant(curr,curr->right);
            if(curr->right!=NULL)z=curr->right->parent;
            else z=curr->parent;
        }
        else if(curr->right==NULL)                 //case 2: right is NULL
        {
            transplant(curr,curr->left);
            if(curr->left!=NULL)z=curr->left->parent;
            else z=curr->parent;
        }
        else                                    //case 3: left and right both are not NULL
        {
            t=minimum(curr->right);
            if(t->parent!=curr)                 //if successor is not the child of deleting node
            {
                transplant(t,t->right);
                if(t->right!=NULL)z=t->right->parent;
                else z=t->parent;
                t->right=curr->right;
                t->right->parent=t;
                transplant(curr,t);
                t->left=curr->left;
                t->left->parent=t;
                t->parent=curr->parent;
            }
            else                                //if successor is child of deleting node
            {
                transplant(curr,t);
                t->left=curr->left;
                t->left->parent=t;
                t->parent=curr->parent;
                z=t;
            }
        }
        while(z!=NULL)                          //After the node is deleted,go up in the parent link till root and update the balance factor
            {
                node* y;
                y=z->parent;
                balance(z);
                z=y;
            }
    }
    void transplant(node *u,node *v)            //replaces u node from v node
    {
        if(u->parent==NULL) root=v;
        else if(u==u->parent->left)u->parent->left=v;
        else u->parent->right=v;
        if(v!=NULL)v->parent=u->parent;
    }
    node* inorder(node *x)              //function to print in inorder
    {
        if(x!=NULL)
        {
           inorder(x->left);
           cout<<x->data<<"\t";
           inorder(x->right);
        }
    }
    void search(int x)                  //function to search an integer
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
    void height_and_bf(int x)               //gives height and bf of any node
    {
        curr=root;
        while(curr!=NULL && curr->data!=x)
        {
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        if(curr==NULL)cout<<x<<" not found\n";
        else cout<<"height is "<<level(curr)-1<<endl<<"bf is "<<bfactor(curr)<<endl;
    }
    node* minimum(node *a)              //function to find out minimum of tree
    {
        while(a->left!=NULL)a=a->left;
        return a;
    }
    node* maximum(node *x)              //function to find out minimum of tree
    {
        while(x->right!=NULL)x=x->right;
        return x;
    }
    int successor(int x)            //function to search for successor
    {
        curr=root;
        while(curr!=NULL && curr->data!=x)
        {
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        if(curr==NULL)cout<<"data not found\n";
        else if(curr->right!=NULL)cout<<"successor is "<<(minimum(curr->right))->data<<endl;  //case 1: when right is not NULL
        else                //case 2: when right is NULL
        {
            t=curr->parent;
            while(t!=NULL && curr==t->right)          //go up to parent until it becomes left child of its parent
            {
                curr=t;
                t=t->parent;
            }
           if(t!=NULL)cout<<"successor is "<<t->data<<endl;
           else cout<<"successor not found\n";
        }
    }
    int predecessor(int x)          //function to search for predecessor
    {
        curr=root;
        while(curr!=NULL && curr->data!=x)
        {
            if(curr->data>x)curr=curr->left;
            else curr=curr->right;
        }
        if(curr==NULL)cout<<"data not found\n";
        else if(curr->left!=NULL)cout<<"predecessor is "<<(maximum(curr->left))->data<<endl;  //case 1: when left is not NULL
        else                                    //case 2:when left is NULL
        {
            t=curr->parent;
            while(t!=NULL && curr==t->left)       //go up to parent until it becomes left child of its parent
            {
                curr=t;
                t=t->parent;
            }
           if(t!=NULL)cout<<"predecessor is "<<t->data<<endl;
           else cout<<"predecessor not found"<<endl;
        }
    }
void display_without_height()     //function to display tree
    {
        int check=1,i=0,k,l=level(root);
        node *a=new node; //declare a fake pointer
        a->data=-32767;
        a->left=a->parent=a->right=NULL;
        queue<node*>queue1;    //take 1 queue
        queue1.push(root);      //push root
        while(!queue1.empty()&& check!=0 && i<l)
        {
            check=0;
            cout<<endl;
            queue<node*>queue2;  //declare 2nd queue
            for(k=0;k<(pow(2,l-i))-2;k++)cout<<" ";
            while(!queue1.empty())
            {
            t=queue1.front(); //check for front element of queue
            queue1.pop();
            if(t->data!=-32767)
            cout<<t->data;
            else cout<<" ";
            for(k=0;k<(pow(2,l-i+1))-1;k++)cout<<" ";
            if(t->left!=NULL)  //push left and right of front element in 2nd queue
            {
                queue2.push(t->left);
                check++;
            }
            else queue2.push(a); //if any of the left or right is NULL then push the fake pointer
            if(t->right!=NULL)
            {
                queue2.push(t->right);
                check++;
            }
            else queue2.push(a);
            }
            queue1=queue2;  //copy 2nd queue in 1st queue
            i++;
        }
        }
    void display()  //display tree with (value,height,bf) same as above function only difference of indentation of tree
    {
        cout<<endl<<"Read tuple as (value,height,bf): "<<endl;
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
            for(k=0;k<4*((pow(2,l-i))-2);k++)cout<<" ";
            while(!queue1.empty())
            {
            node *p=queue1.front();
            queue1.pop();
            if(p->data!=-32767)
            cout<<"("<<p->data<<","<<level(p)-1<<","<<bfactor(p)<<")";
            else cout<<"       ";
            for(k=0;k<4*((pow(2,l-i+1))-2)+1;k++)cout<<" ";
            if(p->left!=NULL)
            {
                queue2.push(p->left);
                check++;
            }
            else queue2.push(a);
            if(p->right!=NULL)
            {
                queue2.push(p->right);
                check++;
            }
            else queue2.push(a);
            }
            queue1=queue2;
            i++;
        }
        }
    int level(node *x)    //returns level of given node
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
