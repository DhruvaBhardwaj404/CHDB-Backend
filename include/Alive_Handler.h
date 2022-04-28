#ifndef ALIVE_HANDLER_H
#define ALIVE_HANDLER_H

#include"paramDefinitions.h"
#include"paramDefinitions.h"
#include"functionConnector.h"
#include"conAliHandler.h"
#include"aliQueHandler.h"
#include"commonMeth.h"




using namespace std;
using commonMeth::RQueue;

class Alive_Handler{

public:
    Alive_Handler();
    ~Alive_Handler();
    void run_Ah();
    void request_Handler();
    //queue<RQueue> req;
    string client_id,token;
    vector< unique_ptr<thread> > fetch_Query;
    bitset<MAX_THREADS> empty_Thread;
    vector<short> getEmpty;
private:
    conAliHandler CA;
    aliQueHandler AQ;
};

/*
    TODO : create query parser to run on fork and it will recieve and serve request using shared memory
    TODO : alive handler will also run on fork and comm using shared with connection handler
    TODO : Will share message with connection handler through message passign
*/
#endif // ALIVE_HANDLER_H
