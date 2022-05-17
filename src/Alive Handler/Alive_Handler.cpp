#include "Alive_Handler.h"


Alive_Handler::Alive_Handler():CA(true),
                            AQ(false),
                            FE(service),
                            RE(service),
                            RI(service)
{
;//TODO: use methods in conALiHandler;
    try{
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(SOCKET_ALIVE_IP),SOCKET_ALIVE_PORT);
        FE.open(asio::ip::tcp::v4());
        FE.bind(ep);
    }
    catch(...){
        cout<<"[Alive Handler > constructor] Couldn't bind to given port\n";
    }

}


Alive_Handler::~Alive_Handler()
{
    ;//dtor
}

void Alive_Handler::run_Ah(){
    if(DEBUG_ALIVE)
        cout<<"[Alive Handler] Running \n";

    FE.listen();
    asio::error_code e1,e2;
    FE.accept(RE,e1);
    FE.accept(RI,e2);
    RE_handler(e1);
    RI_handler(e2);
    while(true){
        ;
    }
}

void Alive_Handler::authen_client(){
    //TODO: authenticate client
}

void Alive_Handler::send_query(){
    //TODO: send user query
}

void Alive_Handler::send_req_ack(){
    //TODO: send user ack to request emitter
}

void Alive_Handler::add_client(){

}

void Alive_Handler::RE_handler(asio::error_code){
    if(DEBUG_ALIVE)
        cout<<"[Alive Handler] Request Emitter Connected\n";
}

void Alive_Handler::RI_handler(asio::error_code){
    if(DEBUG_ALIVE)
        cout<<"[Alive Handler] Request Identifier Connected\n";
}
