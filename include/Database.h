#ifndef DATABASE_H
#define DATABASE_H
#include"Database.h"
#include<string>
#include<map>
#include<bitset>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<iostream>
#include<unistd.h>
#include<fstream>
#include"functionsDB.h"
#include"Handler.h"
#define MAX_DB_NAME 20
#define HASH_SIZE 3135

using namespace functionsDB;
using namespace std;

class Database
{
    public:

        Database();
        Database(string n);
        ~Database();
        //bool find(string,int);
        void use_DB();
        void goto_Handler(const string &mode,string name);


    private:
        int SQLCollections,NSQLCollections;
        bitset<HASH_SIZE> SQLColSchema,NSQLColSchema;
        Handler *col;
        char name[MAX_DB_NAME];

};

#endif // DATABASE_H
