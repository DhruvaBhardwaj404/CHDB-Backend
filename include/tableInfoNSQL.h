#ifndef TABLEINFONSQL_H
#define TABLEINFONSQL_H
#include<vector>
#include<string>
#include<fstream>
#include"functionsDB.h"
#define SIZE_ATTR_NAME 20
#define SIZE_ATTR_INFO 1
#define SIZE_KEY 2

using namespace std;
using functionsDB::NSQL_Cinfo;
class tableInfoNSQL
{
    public:
        vector<pair<string,int> > attr_List,new_Attr;
        vector<int> keys,new_Keys;
        void make_Attr_List(fstream &afile,fstream &kfile,int NA);
        int search_Key(int value);
        void sort_key(int size);
        void print_info(NSQL_Cinfo *info);
        void print_attr_list();

};

#endif // TABLEINFONSQL_H
