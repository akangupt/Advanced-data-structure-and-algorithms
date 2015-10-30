#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
class skip_list
{
private:
  struct node
  {
    int data;
    node *level[10];
  };
  node *head,*curr,*temp;
  float maxlevel;
public:
  skip_list(int size)
  {
    maxlevel=(log(size)/log(2))-1;
    head->data=-32767;
    for(int i=0;i<=maxlevel;i++)
      head->level[i]=NULL;
  }
  void insert(int x)
  {
    int i=leveli();cout<<"Lev "<<i<<"\n\n";
    node* block=new node;
    node* curr=new node;
    node* temp=new node;
    block->data=x;
    curr=head;
    temp=head;
    while(i>=0)
      {
	while(curr!=NULL && curr->data<x)
	  {
	    temp=curr;
	    curr=curr->level[i];
	  }
	block->level[i]=curr;
	temp->level[i]=block;
	curr=block;
	i=i-1;
        curr=temp->level[i];
      }
  }
  int leveli()
  {
    int r=rand()%1000,i;
    for(i=1;i<=maxlevel+1;i++)
      {
	if(r>=1000/pow(2,i))return i-1;
      }
    return maxlevel;
  }
  void deletenode(int x)
  {
    int i=maxlevel,t=0;
    node *delnode=new node;
    curr=head;
    while(i>=0)
      {
	while(curr!=NULL && curr->data<x)
	  {
	    temp=curr;
	    curr=curr->level[i];
	  }
	if(curr!=NULL && curr->data==x)
	  {
	    delnode=curr;
	    temp->level[i]=curr->level[i];
	    t=1;
	  }
	 i=i-1;
	 curr=temp->level[i];
      }
    delete delnode;
    if(t==0) cout<<"\n\n"<<x<<" not found \n";
    else cout<<"\n\n"<<x<<" successfully deleted \n";
  }
  void search(int x)
  {
    cout<<"\n\nsearching data...\n";
    int i=maxlevel;
    node* temp=new node;
    curr=head;
    while(i>=0)
      {
	cout<<"\nLevel "<<i<<"\t";
	if(i!=maxlevel)cout<<temp->data<<"\t";
	while(curr!=NULL && curr->data<x)
	  {
	    temp=curr;
	    cout<<curr->data<<"\t";
	    curr=curr->level[i];
	  }
	if(curr!=NULL && curr->data==x)
	  {
	    cout<<"Data found \n";
	    break;
	  }
	else
	  {
	    i=i-1;
	    curr=temp->level[i];
	  }
      }
    if(i==-1)cout<<"\n\n"<<x<<" is not in list \n";
  }

  void option(int size)
  {
    int choice,i,num,check=0;
    cout<<"So how do you want to insert "<<size<<" elements in list?\nTo insert manually enter 1 \nTo insert random numbers enter 2 \n";
    do
      {
          cout<<"To delete any element enter 3 \nTo search any element enter 4 \nTo exit enter 5 \nEnter your choice : \n";
          cin>>choice;
          switch(choice)
            {
            case 1:
                {
                cout<<"Enter the list of numbers : \n";
                for(i=0;i<size;i++)
                {
                    cin>>num;
                    insert(num);
                }
                display();
                break;
                }
            case 2:
                {
                    for(i=0;i<size;i++)
                    {
                      num=rand()%1000;
                      cout<<num<<endl;
                      insert(num);
                    }
                    display();
                    break;
                }
             case 3:
              {
                int p;
                cout<<"Enter the element to delete \n";
                cin>>p;
                deletenode(p);
                display();
                break;
              }
            case 4:
              {
                int q;
                cout<<"Enter the element to search \n";
                cin>>q;
                search(q);
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
  void display()
  {
    for(int i=maxlevel;i>=0;i--)
      {
	cout<<"\nLevel "<<i<<"\t";
	curr=head;
	while(curr!=NULL)
	  {
	    cout<<curr->data<<"\t";
	    curr=curr->level[i];
	  }
      }
      cout<<"\n\n";
  }
};
main()
{
  srand (time(NULL));
  int size,num,z,i;
  cout<<"Enter the size: \n";
  cin>>size;
  skip_list s(size);
  s.option(size);
}
