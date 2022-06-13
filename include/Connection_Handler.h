#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include"paramDefinitions.h"
#include"Alive_Handler.h"
#include"Query_Parser.h"
#include"functionConnector.h"
#include"conAliHandler.h"


using namespace std;
using namespace functionConnector;


class Connection_Handler
{
public:
    Connection_Handler();
    void run_Connector();
    void init_Master();
    unordered_map<string,client_MDB>::iterator client_Authen(const string&,const string&,const string&) ;
    void init_request_Handler();
    void get_request();
    void new_ClientHandler(VVPSS);
    void exist_ClientHandler(VVPSS);
    void mesQ_Handler();
    void resQ_Handler();
    void admin_Handler();
    void mesAdmin_Handler();
    void RI_handler();
    ~Connection_Handler();

private:

    asio::io_context service;
    unordered_map<string,unordered_map<string,client_MDB>::iterator> authClients;
    unordered_map<string,client_MDB> MDB;
    asio::ip::tcp::acceptor FE;
    asio::ip::tcp::socket RE,RI,ADMIN;
    atomic<bool> running;
    fstream file_MDB;
    list< string > mesQ,resQ,mesAdmin;
    conAliHandler CA;
    mutex MQ,RQ,MA;

};


    //Connection_Handler(string ep,int port);
    //void thread_Handler();
    //void start_ClientHandler(VVPSS);
    //void mes_Handler();

    // vector<std::shared_ptr<Alive_Handler> > Alive;
    // vector<std::unique_ptr<thread> > reqHandler;
    // bitset<MAX_THREADS> emptyThreads;
    // vector<short> getEmpty;
    // Query_Parser *clientDB;
    // timed_mutex tLock;

#endif // CONNECTION_HANDLER_H
