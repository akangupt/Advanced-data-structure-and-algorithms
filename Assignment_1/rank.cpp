#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
using namespace std;
class rank
{
private:
  vector<long long int>vector1;
  long long int t;
public:
  void input(char*);
  void rank_sort();
};
  void rank::input(char* s)
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
void rank::rank_sort()
{
  clock_t t=clock();
  int n=vector1.size();
  int j,R[n],L[n];
    for(j=0;j<n;j++)
        R[j]=1;
    for(j=1;j<n;j++)
    {
        for(int i=0;i<j;i++)
        {
            if(vector1[j]>vector1[i])
                R[j]+=1;
            else
                R[i]+=1;
        }
    }
    for(j=0;j<n;j++)
        L[R[j]-1]=vector1[j];
    t=clock()-t;
    cout<<((float)t)/CLOCKS_PER_SEC;
    ofstream ofs("output.txt");
   for(int i=0;i<n;i++)
     ofs<<L[i]<<endl;
   ofs.close();
}
 main(int argc,char* argv[]){
   char* s=argv[1];
   rank o;
   o.input(s);
   o.rank_sort();
  }
