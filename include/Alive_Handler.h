#ifndef ALIVE_HANDLER_H
#define ALIVE_HANDLER_H

#include"paramDefinitions.h"
#include"functionConnector.h"
#include"conAliHandler.h"
#include"aliQueHandler.h"
#include"commonMeth.h"
#include"functionAlive.h"


using namespace std;
using namespace commonMeth;
using namespace functionAlive;

class Alive_Handler{

public:
    Alive_Handler();
    ~Alive_Handler();

    void run_Ah();
    unordered_map<string,Client_Detail>::iterator authen_client(const string &TOK,const string &TAB);
    void CH_handler();
    void RE_handler();
    void RI_handler();
    void mesRI_handler();



private:
    unordered_map<string,Client_User> regUsers;
    unordered_map<string,Client_Detail> regClients;
    conAliHandler CA;
    aliQueHandler AQ;
    asio::io_context service;
    asio::ip::tcp::acceptor FE;
    asio::ip::tcp::socket RI,RE;
    list<string> mesRI,mesRE;
    mutex MRI,MRE;
    atomic<bool> running;
};

    //void send_query(const vector<pair<string,string> > &query);
    //void send_req_ack();

#endif // ALIVE_HANDLER_H
