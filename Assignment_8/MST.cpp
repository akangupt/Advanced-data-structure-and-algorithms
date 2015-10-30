#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Graph
{
private:
    struct edge
    {
        char pt;
        int weight;
    };
    struct node
    {
        char name;
        node* parent;
    };
    vector<node*>vertexlist;
    vector<vector<edge*> >edgelist;
    public:
    void vertexinput()
    {
        int n;
      cout<<"Enter number of vertices"<<endl;
       cin>>n;
       cout<<"Enter vertices"<<endl;
       for(int i=0;i<n;i++)
       {
          node* temp=new node();
          cin>>temp->name;
          temp->parent=NULL;
          vertexlist.push_back(temp);
       }
       cout<<"Vertexlist done"<<endl;
    }
    void edgesinput()
    {
        for(int i=0;i<vertexlist.size();i++)
        {
            int n;
            vector<edge*>curr;
            edge* temp=new edge();
            temp->pt=vertexlist[i]->name;
            temp->weight=0;
            curr.push_back(temp);
            cout<<"Enter number of edges starting from "<<vertexlist[i]->name<<endl;
            cin>>n;
            for(int j=0;j<n;j++)
            {
                temp=new edge();
               cout<<"Enter end point"<<endl;
               cin>>temp->pt;
               cout<<"Enter weight"<<endl;
               cin>>temp->weight;
               curr.push_back(temp);
            }
            edgelist.push_back(curr);
        }
        cout<<"Edge list done"<<endl;
    }
    struct compare
    {
        bool operator()(edge* a,edge *b)
        {return(a->weight < b->weight);}
    };
    node* representative(node* t)
    {
        if(t->parent==NULL)
            return t;
        else
            return representative(t->parent);
    }
    node* nodify(char a)
    {
        for(int i=0;i<vertexlist.size();i++)
        {
           if(vertexlist[i]->name==a)
                return vertexlist[i];
        }
    }
    void minimum()
    {
         int i,t=0;
         if(edgelist[0].size()==1)
            edgelist.erase(edgelist.begin());
         for(i=1;i<edgelist.size();i++)
        {
            if(edgelist[i].size()>1&& edgelist[t].size()>1)
            {
               if(edgelist[i][1]->weight<edgelist[t][1]->weight)
             t=i;
            }
        }
        node* start=nodify(edgelist[t][0]->pt);
        node* endpt=nodify(edgelist[t][1]->pt);
        node* a=representative(start);
        node* b=representative(endpt);
        if(a!=b)
        {cout<<"Edge included "<<edgelist[t][0]->pt<<" "<<edgelist[t][1]->pt<<endl;
                   b->parent=a;
        }
        edgelist[t].erase(edgelist[t].begin()+1);
        if(edgelist[t].size()==1)
            edgelist.erase(edgelist.begin()+t);
        if(edgelist.size()==1 && edgelist[0].size()==1)
             edgelist.erase(edgelist.begin());
    }
    void minimumspanningtree()
    {
        for(int i=0;i<edgelist.size();i++)
           sort(edgelist[i].begin(),edgelist[i].end(),compare());
        edge* add;
        while(!edgelist.empty())
           minimum();
    }
    /*void display()
    {
        for(int i=0;i<edgelist.size();i++)
            for(int j=0;j<edgelist[i].size();j++)
            cout<<edgelist[i][j]->pt<<endl;
    }*/
};
int main()
{
    Graph g;
    g.vertexinput();
    g.edgesinput();
    g.minimumspanningtree();
}
