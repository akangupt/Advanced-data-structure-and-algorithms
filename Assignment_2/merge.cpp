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
      void merge_sort(int,int);
      void Merge(int,int,int);
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
    merge_sort(1,vector1.size());
    t=clock()-t;
    cout<<float(t)/CLOCKS_PER_SEC;
}
void sort::merge_sort(int p,int r)
{
    if(p<r)
    {
        int q=(p + r)/2;
        merge_sort(p,q);
        merge_sort(q+1,r);
        Merge(p,q,r);
    }
}
void sort::Merge(int p,int q,int r)
{
    vector<long long int>L;
    vector<long long int>R;
    int n1=q-p+1,n2=r-q;
    for(int x=0;x<n1;x++)L.push_back(vector1[p+x-1]);
    for(int y=0;y<n2;y++)R.push_back(vector1[q+y]);
    L.push_back(-9223372036854775807);
    R.push_back(-9223372036854775807);
    int i=0,j=0;
    for(int k=p-1;k<r;k++)
    {
      if(L[i]>=R[j])
        {
            vector1[k]=L[i];
            i=i+1;
        }
        else
        {
            vector1[k]=R[j];
            j=j+1;
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
 main(int argc,char* argv[]){
   char* s=argv[1];
   sort o;
   o.input(s);
   o.output();
  }
