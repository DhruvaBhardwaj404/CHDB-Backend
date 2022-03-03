#include "Query_Parser.h"
using namespace functionConnector;

Query_Parser::Query_Parser()
{
    //ctor
}


Query_Parser::~Query_Parser()
{
    //dtor
}

void Query_Parser::fetch(vector<string> query){             // dbname,collection,table,type,operation,condition
    string id=query[0];
    auto db=DB.find(id);
    if(db==DB.end())
        database_Open* db_ptr=open_DB(query[0],query[1],query[2],query[3]);

    //string data=get_data(query[3],query[4],db);
    //TODO: implement get_data
    return data;
}

static void Query_Parser::discard_unused(){
    //TODO discard unused
}
static bool Query_Parser::check_Ifopen(){
    //Todo Check_Ifopen
}
static database_Open* Query_Parser::open_DB(const string &dbname,const string & collection,const string & table,const string & type){
    while(!masterM.try_lock()){
        if(masterR.find(dbname)){
            masterM.unlock();
            chdir("./"+dbname.c_string());
            Database db;
            time_t creation_time;
            time(creation_time);
            DB.insert(dbname.c_string(),{},time_t);
            db.goto_Handler(type,collection);
            //

            //TODO restructure database processing methods

        }
    }
}
static bool Query_Parser::get_data(string,string,database_Open*){
    //TODO get data
}
