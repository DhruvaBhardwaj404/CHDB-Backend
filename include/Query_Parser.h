#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include"paramDefinitions.h"
#include"Database.h"
#include"functionConnector.h"
#include"Exisiting_DB.h"
#include"aliQueHandler.h"


//TODO Query Parser
using namespace functionConnector;

class Query_Parser
{
public:
    Query_Parser();
    static unordered_map<string,tuple<database_Open,mutex,time_t>> DB;
    static void discard_unused();
    static bool check_Ifopen();
    void run_Qp();
    static database_Open* open_DB(const string &,const string &,const string &,const string &);
    static bool get_data(string,string,database_Open*);
    void fetch(vector<string> query);
    static Exisiting_DB masterR;
    static mutex masterM;
    ~Query_Parser();
private:
    //shared_memory_object AQ;
};

#endif // QUERY_PARSER_H


//TODO: Remove unnecessary methods and data members for all main classes!!!
