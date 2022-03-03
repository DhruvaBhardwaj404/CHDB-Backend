#ifndef FUNCTIONCONNECTOR_H
#define FUNCTIONCONNECTOR_H
#include"paramDefinitions.h"
#include<asio.hpp>
#include<string>
#include<chrono>
#include<random>
#include"Handler.h"

using namespace std;

namespace functionConnector
{
struct alive_Instance
{
    string DB,Col,Tab;
    int type;
};

struct table_Nopen
{
    vector<NSQL_TabHandler> tab;
    vector<bool> active;
};

struct table_Sopen
{
    vector<SQL_TabHandler> tab;
    vector<bool> active;
};

struct table_Hopen
{
//        vector<Hybrid_TabHandler> tab;
    vector<bool> active;
};

struct collection_Open
{
    unordered_map<string,shared_ptr<table_Nopen> > Ntab;
    unordered_map<string,shared_ptr<table_Sopen> > Stab;
    vector<bool> active;
};

struct database_Open
{
    unordered_map<string,shared_ptr<collection_Open>> col;
    vector<bool> active;
};

vector<string> parse_FrontEnd_Mess(const string& mes);
string gen_rand(const string&,const string&);
}

#endif // FUNCTIONCONNECTOR_H
