
#include "parse.h"
#include<string>
#include<iostream>
#include<vector>


using namespace std;

vector<string> parse(string command){
	vector<string> parsed;
	string word;
	int length=command.size();

	for(int a=0;a<length+1;a++){
		if(command[a]==' ' || a==length){
			parsed.push_back(word);
		    word.clear();
		}
		else{
			word.push_back(command[a]);
		}
	}

 return parsed;
}

int hash(string name){
    int Num=0;
    for(int i=0;i<name.size();i++){
        Num+=((int(name[i]))%64)*(i+1);
    }
   // cout<<"\nhash =>"<<Num<<endl;
  return Num;
}
