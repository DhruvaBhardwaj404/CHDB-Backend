#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include"paramDefinitions.h"
#include"Alive_Handler.h"
#include"Query_Parser.h"
#include"functionsDB.h"
#include"functionConnector.h"
#include"conAliHandler.h"
#include<fstream>

#define MDB_FILENAME "MDB"


using namespace std;
using functionConnector::collection_Open;


//TODO: Connect to Frontend

class Connection_Handler
{
public:
    Connection_Handler();
    //Connection_Handler(string ep,int port);
    void run_Connector();
    void init_Master();
    bool client_Authen(string,string);
    void init_request_Handler();
    void get_request();
    void mes_Handler(const string &);
    static bool comp_Checker(const string & mes,int size);
    void new_ClientHandler(const vector<string> &);
    void exist_ClientHandler(const vector<string> &);
    void start_ClientHandler(const vector<string> &);
    //void thread_Handler();
    void admin_Handler();
    static void RI_handler(asio::error_code);
    ~Connection_Handler();


private:

    asio::io_context service;
    unordered_map<string,clientData> authClients;
    unordered_map<string,client_MDB> MDB;
    //not required vector<std::shared_ptr<Alive_Handler> > Alive;
    vector<std::unique_ptr<thread> > reqHandler;
    asio::ip::tcp::acceptor FE;//Asock;
    asio::ip::tcp::socket RI;
    atomic<bool> running;
    fstream file_MDB;
    //not required bitset<MAX_THREADS> emptyThreads;
    //not required vector<short> getEmpty;
    //not required Query_Parser *clientDB;
    //not required timed_mutex tLock;
    conAliHandler CA;
};

#endif // CONNECTION_HANDLER_H
