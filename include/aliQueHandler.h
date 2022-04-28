#ifndef ALIQUEHANDLER_H
#define ALIQUEHANDLER_H
#include"paramDefinitions.h"
#include<boost/interprocess/shared_memory_object.hpp>
#include<boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

class aliQueHandler
{
    public:
        aliQueHandler();
        virtual ~aliQueHandler();

    private:
        shared_memory_object aliQue;
        mapped_region mesSpace;
};

#endif // ALIQUEHANDLER_H
