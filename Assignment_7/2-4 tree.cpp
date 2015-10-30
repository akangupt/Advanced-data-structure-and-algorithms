#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
class tree
{
private:
   typedef struct node
    {
        node *p;
        int data[3];
        node *next[4];
    };
    node *root;
public:
    tree()
    {
        root=NULL;
    }
    void input()
    {
        int n,size,choice,check=0;;
        cout<<"Enter the size"<<endl;
        cin>>size;
        cout<<"Enter the elements"<<endl;
        for(int i=0;i<size;i++)
            {
                cin>>n;
                insert(n);
            }
            cout<<"Height of the tree is "<<level(root)-1<<endl;
        do
        {
          cout<<"\n1. Insert \n2. Delete\n3. Search\n4. Display\n5. Exit\nEnter your choice : \n";
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
    void insert(int n)
    {
        if(root==NULL)
        {
            node *a=new node;
            a->data[0]=n;
            a->data[1]=32767;
            a->data[2]=32767;
            for(int i=0;i<3;i++)a->next[i]=NULL;
            a->p=NULL;
            root=a;
        }
        else
        {
            int t,c=0;
            node *curr=new node;
            node *prev=new node;
            node *sib=new node;
            node *pp_sib=new node;
            curr=root;
            sib=NULL;
            while(curr!=NULL)
            {
                prev=curr;
                if(n<curr->data[0])curr=curr->next[0];
                else if(n>curr->data[0] && n<curr->data[1])curr=curr->next[1];
                else if(n>curr->data[1] && n<curr->data[2])curr=curr->next[2];
                else curr=curr->next[3];
            }
            while(prev!=NULL)
            {
                pp_sib=prev->next[3];
                if(n<prev->data[0])
                {
                    t=prev->data[2];
                    prev->data[2]=prev->data[1];
                    prev->data[1]=prev->data[0];
                    prev->data[0]=n;
                    for(int i=3;i>1;i--)
                        prev->next[i]=prev->next[i-1];
                    prev->next[1]=sib;
                    if(sib!=NULL)sib->p=prev;
                }
                else if(n>prev->data[0] && n<prev->data[1])
                {
                    t=prev->data[2];
                    prev->data[2]=prev->data[1];
                    prev->data[1]=n;
                    prev->next[3]=prev->next[2];
                    prev->next[2]=sib;
                    if(sib!=NULL)sib->p=prev;
                }
                else if(n>prev->data[1] && n<prev->data[2])
                {
                    t=prev->data[2];
                    prev->data[2]=n;
                    prev->next[3]=sib;
                    if(sib!=NULL)sib->p=prev;
                }
                else t=n;
                if(t!=32767)
                {
                    node *temp=new node;
                    temp->data[0]=t;
                    temp->data[1]=32767;
                    temp->data[2]=32767;
                    temp->p=NULL;
                    temp->next[0]=prev->next[3];
                    if(prev->next[3]!=NULL) prev->next[3]->p=temp;
                    if(sib!=NULL)
                    {
                        if(sib->p==NULL)
                        {
                            temp->next[1]=sib;
                            sib->p=temp;
                        }
                        else
                        {
                            temp->next[1]=pp_sib;
                            pp_sib->p=temp;
                        }
                    }
                    else temp->next[1]=NULL;
                    prev->next[3]=NULL;
                    sib=temp;
                    n=prev->data[2];
                    prev->data[2]=32767;
                    curr=prev;
                    prev=prev->p;
                }
                else break;
            }
            if(prev==NULL)
            {
                node *tempi=new node;
                tempi->data[0]=n;
                tempi->data[1]=32767;
                tempi->data[2]=32767;
                tempi->p=NULL;
                tempi->next[0]=curr;
                tempi->next[1]=sib;
                curr->p=tempi;
                sib->p=tempi;
                root=tempi;
            }
       }
    }
     void search(int x)
     {
        node *curr=new node;
        curr=root;
        cout<<"Path-->\n";
        while(curr!=NULL && curr->data[0]!=x && curr->data[1]!=x && curr->data[2]!=x)
        {
            for(int i=0;i<3;i++)
            {
                if(curr->data[i]!=32767)cout<<curr->data[i]<<"\t";
                else cout<<" "<<"\t";
            }
            cout<<"\n";
            if(x<curr->data[0])curr=curr->next[0];
            else if(x>curr->data[0] && x<curr->data[1])curr=curr->next[1];
            else if(x>curr->data[1] && x<curr->data[2])curr=curr->next[2];
            else curr=curr->next[3];
        }
        if(curr==NULL)cout<<x<<" not found"<<endl;
        else cout<<x<<" found"<<endl;
      }
      void deletenode(int x)
        {
            int k=0;
            node *curr=new node;
            node *pp_sib=new node;
            pp_sib=NULL;
            curr=root;
            cout<<"Path--->\n";
            while(curr!=NULL && curr->data[0]!=x && curr->data[1]!=x && curr->data[2]!=x)
            {
                for(int i=0;i<3;i++)
                {
                    if(curr->data[i]!=32767)cout<<curr->data[i]<<"\t";
                    else cout<<" "<<"\t";
                }
                cout<<"\n";
                if(x<curr->data[0])curr=curr->next[0];
                else if(x>curr->data[0] && x<curr->data[1])curr=curr->next[1];
                else if(x>curr->data[1] && x<curr->data[2])curr=curr->next[2];
                else curr=curr->next[3];
            }
            if(curr==NULL)cout<<x<<" not found";
            else if(curr->next[0]!=NULL)
            {
                node *temp=new node;
                if(curr->data[0]==x)temp=curr->next[1];
                else if(curr->data[1]==x)temp=curr->next[2];
                else temp=curr->next[3];
                while(temp->next[0]!=NULL)
                {
                    temp=temp->next[0];
                }
                cout<<"Successor of "<<x<<" is "<<temp->data[0]<<endl;
                for(int i=0;i<3;i++)
                {
                    if(curr->data[i]==x)
                    {
                        int a;
                        a=curr->data[i];
                        curr->data[i]=temp->data[0];
                        temp->data[0]=a;
                    }
                }
                curr=temp;
            }
            if(curr->next[0]==NULL)
            {
                   if(curr->data[1]!=32767)
                   {
                        int i;
                        for(i=0;i<3;i++)
                        {
                            if(curr->data[i]==x)break;
                        }
                        while(i<2)
                        {
                            curr->data[i]=curr->data[i+1];
                            i++;
                        }
                         curr->data[2]=32767;
                         k=2;
                   }
                   else
                   {
                       while(curr->p!=NULL)
                       {
                       node *sib=new node;
                       if(curr->p->next[0]==curr)
                       {
                           sib=curr->p->next[1];
                           curr->data[0]=curr->p->data[0];
                           if(sib->data[1]!=32767)
                           {
                               curr->p->data[0]=sib->data[0];
                               curr->next[1]=sib->next[0];
                               if(sib->next[0]!=NULL)curr->next[1]->p=curr;
                               for(int i=0;i<2;i++)
                               {
                                   sib->data[i]=sib->data[i+1];
                                   sib->next[i]=sib->next[i+1];
                               }
                               sib->data[2]=32767;
                               sib->next[2]=sib->next[3];
                               sib->next[3]=NULL;
                               break;
                           }
                           else
                           {
                                curr->data[1]=sib->data[0];
                                for(int i=0;i<2;i++)
                                {
                                    curr->p->data[i]=curr->p->data[i+1];
                                    curr->p->next[i+1]=curr->p->next[i+2];
                                    curr->next[i+1]=sib->next[i];
                                    if(sib->next[i]!=NULL)curr->next[i+1]->p=curr;
                                }
                                curr->p->next[3]=NULL;
                               if(curr->p->data[0]==32767)
                               {
                                   curr=curr->p;
                                   k=1;
                               }
                               else break;
                           }
                       }
                       else
                       {
                           int j;
                           if(curr->p->next[1]==curr){sib=curr->p->next[0];j=1;}
                           else if(curr->p->next[2]==curr){sib=curr->p->next[1];j=2;}
                           else {sib=curr->p->next[2];j=3;}
                           if(sib->data[1]!=32767)
                           {
                               int t;
                               if(sib->data[2]!=32767)
                               {
                                    t=sib->data[2];
                                    sib->data[2]=32767;
                                    pp_sib=sib->next[3];
                                    sib->next[3]=NULL;
                               }
                               else
                               {
                                    t=sib->data[1];
                                    sib->data[1]=sib->data[2]=32767;
                                    pp_sib=sib->next[2];
                                    sib->next[2]=NULL;
                               }
                               curr->data[0]=curr->p->data[j-1];
                               curr->p->data[j-1]=t;
                               curr->next[1]=curr->next[0];
                               curr->next[0]=pp_sib;
                               if(pp_sib!=NULL)pp_sib->p=curr;
                               break;
                           }
                           else
                           {
                               sib->data[1]=curr->p->data[j-1];
                               sib->next[2]=curr->next[0];
                               if(curr->next[0]!=NULL)sib->next[2]->p=sib;
                               while(j<3)
                               {
                                   curr->p->data[j-1]=curr->p->data[j];
                                   curr->p->next[j]=curr->p->next[j+1];
                                   j++;
                               }
                               curr->p->data[2]=32767;
                               curr->p->next[3]=NULL;
                               if(curr->p->data[0]==32767)
                               {
                                   curr=curr->p;
                                   k=1;
                               }
                               else break;
                           }
                    }
                }
                }
            }
            if(curr->p==NULL && k==1)
            {
                    curr->next[0]->p=NULL;
                    root=curr->next[0];
            }
            else if(curr->p==NULL && k==0)
            {
                    curr->data[0]=32767;
                    cout<<"Tree is empty\n";
            }
        }
        void display()
        {
            node *t=new node;
            queue<node*>queue1;
            queue1.push(root);
            while(!queue1.empty())
            {
                cout<<endl;
                queue<node*>queue2;
                while(!queue1.empty())
                {
                    t=queue1.front();
                    queue1.pop();
                    cout<<"(";
                    for(int i=0;i<3;i++)
                    {
                        if(t->data[i]!=32767)cout<<t->data[i]<<" ";
                        else cout<<"  ";
                    }
                    cout<<")";
                    if(t->next[0]!=NULL)queue2.push(t->next[0]);
                    if(t->next[1]!=NULL)queue2.push(t->next[1]);
                    if(t->data[1]!=32767 && t->next[2]!=NULL)queue2.push(t->next[2]);
                    if(t->data[2]!=32767 && t->next[3]!=NULL)queue2.push(t->next[3]);
                }
                queue1=queue2;
            }
        }
    int level(node *x)
        {
             int i=1;
             node *curr=new node;
             curr=x;
             while(curr->next[0]!=NULL)
                {
                    curr=curr->next[0];
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
