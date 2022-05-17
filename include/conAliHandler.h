#ifndef CONALIHANDLER_H
#define CONALIHANDLER_H
#include<boost/interprocess/managed_shared_memory.hpp>
#include<boost/interprocess/sync/named_mutex.hpp>
#include<boost/circular_buffer.hpp>
#include"paramDefinitions.h"
#include"commonMeth.h"
#define DEBUG_CONALIHANDLER true


using namespace std;
using namespace commonMeth;

class conAliHandler
{
    public:
        conAliHandler(bool m);
        ~conAliHandler();
        string fetch_msg();
        bool send_msg(const string & mess);
//        bool write_meta();
//        bool read_meta();
    private:
        BIP::managed_shared_memory conAli;
//        queue<conAliHeader> *mesQA,*mesQC;
//        conAliMeta *sharedM;
        boost::interprocess::named_mutex mutexCA;
        boost::circular_buffer<string> *mesA,*mesC;
//        int8_t cur_req,cur_ack;
        bool mode;   //false= con || true=ali



};

#endif // CONALIHANDLER_H
