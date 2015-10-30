#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
using namespace std;
class sort
{
private:
  vector<long long int>vector1;
  long long int t;
public:
  void input(char*);
  void quick_sort(int,int);
  int partition(int,int);
  void output();
};
 void sort::input(char* s)
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
    clock_t t=clock();
    quick_sort(0,vector1.size()-1);
    t=clock()-t;
    cout<<float(t)/CLOCKS_PER_SEC;
  }
void sort::quick_sort(int p,int r)
{
  if(p<r)
    {
      int q=partition(p,r);
      quick_sort(p,q);
      quick_sort(q+1,r);
    }
}
int sort::partition(int start,int end)
{
  int pivot=vector1[end],t=1,i=start-1,j=end+1,temp;
  while(t==1)
    {
          do
         {
            j=j-1;
         }while(vector1[j]>pivot);
          do
         {
            i=i+1;
         }while(pivot>vector1[i]);
          if(j>i)
         {
              temp=vector1[i];
              vector1[i]=vector1[j];
              vector1[j]=temp;
         }
          else
         {
          if(j==i)return j-1;
          else return j;
         }
    }
}
void sort::output()
 {
   ofstream ofs("output.txt");
   for(int i=0;i<vector1.size();i++)
     ofs<<vector1[i]<<endl;
   ofs.close();
 }
 main(int argc,char* argv[])
 {
   char* s=argv[1];
   sort o;
   o.input(s);
   o.output();
 }
