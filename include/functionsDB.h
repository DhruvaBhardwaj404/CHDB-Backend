#ifndef FUNCTIONSDB_H
#define FUNCTIONSDB_H
#include<vector>
#include<string>
#include<cstring>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<unistd.h>
#include<syscall.h>
#include<functional>
#define vs vector<string>
#define vps vector<pair<string,string> >
#define TYPE_SIZE 7

using namespace std;

namespace functionsDB{
    static char type_name[TYPE_SIZE][20]={"INT","LONG LONG","FLOAT","DOUBLE","CHAR","STRING","OBJECT"};
    static unsigned int type_size[TYPE_SIZE]={2,8,4,8,1,0,0};
    vs parse(const string &command);
    vps parse(string::iterator start,string::iterator end);
    pair<vs,vps > parseData(const string &command);
    vector<vector<pair<string,string> > > parseInsert(const string &command);
    string padding_Remover(string data);
    string validate_Types(vps &cols) ;
    bool type_checker(string value,pair<unsigned int,unsigned int>  type);
    int hashFun(string name);
}

#endif // FUNCTIONSDB_H
