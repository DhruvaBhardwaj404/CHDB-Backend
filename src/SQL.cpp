#include<unistd.h>
#include<fstream>
#include<iostream>
#include<cstring>
#include "SQL.h"
#include "functionsDB.h"
#include "SQL_ColHandler.h"
#include"functionsDB.h"


using namespace std;


SQL::SQL(string name="\0")
{
    try{
        chdir("./sql");
        fstream file("Sql_info.txt",ios::in|ios::binary);
        if(file.is_open()){
            file.read((char*)this,sizeof(SQL));
            file.close();
        }
        name.resize(20);
        if(name!="\0"){
            if(col_name[hashFun(name)]=1){
               strcpy(sel_Col_Name,name.c_str());
            }
            else{
                cout<<"[!!!] No collection with specified name exist!";
            }
        }
    }
    catch(...){
        cout<<"[!!!] Error while creating sql object!";
    }

}

SQL::~SQL()
{
try{
    fstream file("Sql_info.txt",ios::out|ios::binary);
    if(file.is_open()){
        file.seekp(0);
        file.write((char*)this,sizeof(SQL));
        file.close();
    }
}
catch(...){
    cout<<"[!!!] Error while destructing Sql object!";
}
}
void SQL::use_SQL(){
cout<<"hello";
}

void select_Collection(string name){
}

void create_Collection(string name){
}

void delete_collection(){
}

void display_Collection(){

}


