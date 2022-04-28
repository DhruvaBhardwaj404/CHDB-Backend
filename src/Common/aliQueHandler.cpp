#include "aliQueHandler.h"

aliQueHandler::aliQueHandler():aliQue(open_only,SHARED_MEM_ALIQUE,read_write),mesSpace(aliQue,read_write,0,SHARED_MEM_SIZE_A2Q)
{
//TODO: directly use shared memory;
}

aliQueHandler::~aliQueHandler()
{
    //dtor
}
