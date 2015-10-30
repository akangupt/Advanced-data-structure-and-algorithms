#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
using namespace std;
class insertion
{
private:
  vector<long long int>vector1;
  long long int t;
public:
  void input(char*);
  void insertion_sort();
  void output();
};
  void insertion::input(char* s)
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
void insertion::insertion_sort()
{
clock_t t=clock();
  for(int k=0;k<vector1.size();k++)
    {
int i=k,save_value=vector1[k];
    while(i>0&&vector1[i-1]>save_value)
    {
        vector1[i]=vector1[i-1];
        i--;
    }
    vector1[i]=save_value;
    }
t=clock()-t;
cout<<float(t)/CLOCKS_PER_SEC;
}
void insertion::output()
 {
   ofstream ofs("output.txt");
   for(int i=0;i<vector1.size();i++)
     ofs<<vector1[i]<<endl;
   ofs.close();
}
 main(int argc,char* argv[]){
   char* s=argv[1];
   insertion o;
   o.input(s);
   o.insertion_sort();
   o.output();
  }
