#include "hash.h"

int Exisiting_DB::hash(string name){
    int Num=0;
    for(int i=0;i<name.size();i++){
        Num+=((int(name[i]))%64)*(i+1);
    }
   // cout<<"\nhash =>"<<Num<<endl;
  return Num;
}
