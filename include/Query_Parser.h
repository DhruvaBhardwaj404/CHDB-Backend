#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H
#include<unordered_map>
#include"Database.h"
#include"functionConnector.h"
#include"mutex"
#include<ctime>
#include<tuple>
#include"Exisiting_DB.h"
//TODO Query Parser
using namespace functionConnector;

class Query_Parser
{
public:
    Query_Parser();
    static unordered_map<string,tuple<database_Open,mutex,time_t>> DB;
    static void discard_unused();
    static bool check_Ifopen();
    static database_Open* open_DB(const string &,const string &,const string &,const string &);
    static bool get_data(string,string,database_Open*);
    void fetch(vector<string> query);
    static Exisiting_DB masterR;
    static mutex masterM;
    ~Query_Parser();

protected:

private:
};

#endif // QUERY_PARSER_H
