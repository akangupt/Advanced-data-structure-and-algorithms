#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
using namespace std;
class bubble
{
private:
  vector<long long int>vector1;
  long long int t;
public:
  void input(char*);
  void bubble_sort();
  void output();
};
  void bubble::input(char* s)
  {
   ifstream f(s);
   f>>t;
    if(f.is_open()){
    while(!f.eof())
      {
    vector1.push_back(t);
f>>t;
    }
    f.close();
    }
    else cout<<"unable to open file"<<endl;
  }
void bubble::bubble_sort()
{
clock_t t=clock();
  int n=vector1.size();
for(int i=0;i<n;i++)
    {
        for(int j=n-1;j>i;j--)
            if(vector1[j]<vector1[j-1])
            {
                int temp=vector1[j];
                vector1[j]=vector1[j-1];
                vector1[j-1]=temp;
            }
    }
t=clock()-t;
cout<<float(t)/CLOCKS_PER_SEC;
}
void bubble::output()
 {
   ofstream ofs("output.txt");
   for(int i=0;i<vector1.size();i++)
     ofs<<vector1[i]<<endl;
   ofs.close();
}
 main(int argc,char* argv[]){
   char* s=argv[1];
   bubble o;
   o.input(s);
   o.bubble_sort();
   o.output();
  }
