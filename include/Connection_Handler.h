#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include<asio.hpp>
#include<asio/ip/tcp.hpp>
#include<future>
#include<thread>
#include<memory>
#include<atomic>
#include<list>
#include<mutex>
#include"Alive_Handler.h"
#include"Query_Parser.h"
#include"functionsDB.h"
#include"paramDefinitions.h"
#include"functionConnector.h"


#define MAX_THREADS 5
#define MAX_PAC_SIZE 256
#define MAX_WAIT 10
using namespace std;
using namespace functionConnector;

struct clientData
{
    string token;
    int clientThread;
};
//TODO() Connection Handler

class Connection_Handler
{
public:
    Connection_Handler();
    Connection_Handler(string ep,int port);
    void run_Connector();
    void init_Master();
    bool client_Authen(string,string);
    void request_Handler();
    void mes_Handler(const string &);
    static bool comp_Checker(const string & mes,int size);
    void new_ClientHandler(const vector<string> &);
    void exist_ClientHandler(const vector<string> &);
    void start_ClientHandler(const vector<string> &);
    void thread_Handler();
    void admin_Handler();
    ~Connection_Handler();


private:
    asio::io_context service;
    unordered_map<string,clientData> authClients;
    vector<shared_ptr<Alive_Handler> > Alive;
    vector<unique_ptr<thread> > Client;
    asio::ip::tcp::socket Fsock,Asock;
    atomic<bool> running;
    bitset<MAX_THREADS> emptyThreads;
    vector<short> getEmpty;
    Query_Parser *clientDB;
    timed_mutex tLock;
};

#endif // CONNECTION_HANDLER_H
