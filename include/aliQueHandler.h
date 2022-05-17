#ifndef ALIQUEHANDLER_H
#define ALIQUEHANDLER_H
#include"paramDefinitions.h"
#include<boost/interprocess/shared_memory_object.hpp>
#include<boost/interprocess/sync/named_mutex.hpp>
#include<boost/circular_buffer.hpp>
#include"commonMeth.h"
#define DEBUG_ALIQUEHANDLER true

using namespace std;
using namespace commonMeth;

class aliQueHandler
{
public:
        aliQueHandler(bool m);
        ~aliQueHandler();
        string fetch_msg();
        bool send_msg(int8_t action,const string &mess);
//        bool write_meta();
//        bool read_meta();
    private:
        BIP::managed_shared_memory aliQue;
        //queue<conAliHeader> *mesQA,*mesQQ;
        //aliQueMeta *sharedM;
        boost::interprocess::named_mutex mutexAQ;
        boost::circular_buffer<string> *mesA,*mesQ;
        //int16_t offQ,offA;
        bool mode;   //false= ali || true=que
};

#endif // ALIQUEHANDLER_H
