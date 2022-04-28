#ifndef CONALIHANDLER_H
#define CONALIHANDLER_H
#include<boost/interprocess/mapped_region.hpp>
#include<boost/interprocess/shared_memory_object.hpp>
#include"paramDefinitions.h"

using namespace std;
using namespace boost::interprocess;


//TODO: handler shared memory message retreival
class conAliHandler
{
    public:
        conAliHandler();
        ~conAliHandler();
        string fetch_msg();
        void send_msg();
    private:
        shared_memory_object conAli;
        mapped_region mesSpace;


};

#endif // CONALIHANDLER_H
