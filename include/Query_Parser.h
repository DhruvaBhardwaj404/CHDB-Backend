#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include"paramDefinitions.h"
#include"functionConnector.h"
#include"aliQueHandler.h"
#include"Hybrid_TabHandler.h"
#include"Master_FHANDLER.h"


using namespace functionConnector;
//TODO: Connect to Frontend
class Query_Parser
{
public:
    Query_Parser();
    void run_Qp();
    void query_Handler();
    void RE_Handler();
    ~Query_Parser();
private:
    asio::io_context service;
    asio::ip::tcp::acceptor FE;
    asio::ip::tcp::socket RE;
    aliQueHandler AQ;
    list<string> mesRE;
    mutex MRE;
    unordered_map<string,Master_FHANDLER*> activeClients;
    atomic<bool> running;


};

#endif // QUERY_PARSER_H


//TODO: Remove unnecessary methods and data members for all main classes!!!
