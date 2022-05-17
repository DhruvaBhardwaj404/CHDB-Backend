#include "Query_Parser.h"
using namespace functionConnector;

Query_Parser::Query_Parser():FE(service),RI(service)
{
    try{
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(SOCKET_QPAR_IP),SOCKET_QPAR_PORT);
        FE.open(asio::ip::tcp::v4());
        FE.bind(ep);
    }
    catch(...){
        cout<<"[Query Parser > Constructor ] Unable to bind to given port\n";
    }
}


Query_Parser::~Query_Parser()
{
    //dtor
}

void Query_Parser::run_Qp(){
    if(DEBUG_QUE)
        cout<<"[query parser] running\n";

    FE.listen();
    asio::error_code e;
    FE.accept(RI,e);
    RI_handler(e);
    while(true){
        ;
    }
}

void Query_Parser::fetch(vector<string> query){             // dbname,collection,table,type,operation,condition
//    string id=query[0];
//    auto db=DB.find(id);
//    if(db==DB.end())
//        database_Open* db_ptr=open_DB(query[0],query[1],query[2],query[3]);

    //string data=get_data(query[3],query[4],db);
    //TODO: implement get_data
    //return data;
}

 void Query_Parser::discard_unused(){
    //TODO discard unused
}
 bool Query_Parser::check_Ifopen(){
    //Todo Check_Ifopen
}

 database_Open* Query_Parser::open_DB(const string &dbname,const string & collection,const string & table,const string & type){
//
//    while(!masterM.try_lock()){
//        if(masterR.find(dbname)){
//
//            masterM.unlock();
//            string loc="./"+dbname;
//            chdir(loc.c_str());
//            Database db;
//            time_t* creation_time;
//            time(creation_time);
//            //DB.insert(dbname.c_str(),{},time_t);
//            //db.goto_Handler(type,collection);
//
//
//            //TODO:restructure database processing methods
//
//        }
//    }
    return nullptr;
}
 bool Query_Parser::get_data(string,string,database_Open*){
    //TODO get data
}

void Query_Parser::RI_handler(asio::error_code){
    if(DEBUG_QUE)
        cout<<"[query parser] Request Emitter connected\n";
}
