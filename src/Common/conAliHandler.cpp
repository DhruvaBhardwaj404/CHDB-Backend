#include "conAliHandler.h"

conAliHandler::conAliHandler():conAli(open_only,SHARED_MEM_CONALI,read_write),mesSpace(conAli,read_write,0,SHARED_MEM_SIZE_C2A)
{

    //TODO: rectify constructor error
    //cout<<mesSpace.get_address();
}

conAliHandler::~conAliHandler()
{
    //dtor
}

string conAliHandler::fetch_msg(){

}

void conAliHandler::send_msg(){

}
