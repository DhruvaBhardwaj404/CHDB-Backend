#ifndef ALIVE_HANDLER_H
#define ALIVE_HANDLER_H

#include"paramDefinitions.h"
#include"functionConnector.h"
#include"conAliHandler.h"
#include"aliQueHandler.h"
#include"commonMeth.h"
#include"functionAlive.h"

#define AH_NUM_SOCK 5



using namespace std;
using commonMeth::RQueue;
using namespace functionAlive;

class Alive_Handler{

public:
    Alive_Handler();
    ~Alive_Handler();
    static void RE_handler(asio::error_code);
    static void RI_handler(asio::error_code);
    void run_Ah();
    void authen_client();
    void send_query();
    void send_req_ack();
    void add_client();

private:
    unordered_map<string,Client_Detail> regClients;   //registers clients for query
    conAliHandler CA;
    aliQueHandler AQ;
    asio::io_context service;
    asio::ip::tcp::acceptor FE;
    asio::ip::tcp::socket RI,RE;
    uint8_t numAC;
};

/*
    TODO : create query parser to run on fork and it will recieve and serve request using shared memory
    TODO : alive handler will also run on fork and comm using shared with connection handler
    TODO : Will share message with connection handler through message passign
*/
#endif // ALIVE_HANDLER_H
