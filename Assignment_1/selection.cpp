#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
using namespace std;
class selection
{
private:
  vector<long long int>vector1;
  long long int t;
public:
  void input(char*);
  void selection_sort();
  void change(int,int);
  void output();
};
void selection::input(char* s)
  {
   ifstream f(s);
   f>>t;
    if(f.is_open())
{
    while(!f.eof())
      {
    vector1.push_back(t);
    f>>t;
    }
    f.close();
    }
    else cout<<"unable to open file"<<endl;
  }
void selection::selection_sort()
{
clock_t t=clock();
int i,min;
 for(i=0;i<vector1.size();i++)
    {
      min=i;
   for(int k=i;k<vector1.size();k++)
     {
      if(vector1[min]>vector1[k])min=k;
     }
      if(min!=i)change(i,min);
    }
t=clock()-t;
cout<<float(t)/CLOCKS_PER_SEC;
}
void selection::change(int i,int min)
{
  int temp;
  temp=vector1[i];
  vector1[i]=vector1[min];
  vector1[min]=temp;
}
 void selection::output()
 {
   ofstream ofs("output.txt");
   for(int i=0;i<vector1.size();i++)
     ofs<<vector1[i]<<endl;
   ofs.close();
}
 main(int argc,char* argv[]){
   char* s=argv[1];
   selection o;
   o.input(s);
   o.selection_sort();
   o.output();
  }

