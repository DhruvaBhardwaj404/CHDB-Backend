#include "Alive_Handler.h"


Alive_Handler::Alive_Handler():CA(true),
                            AQ(false),
                            FE(service),
                            RE(service),
                            RI(service)
{

    try{
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(SOCKET_ALIVE_IP),SOCKET_ALIVE_PORT);
        FE.open(asio::ip::tcp::v4());
        FE.bind(ep);
    }
    catch(...){
        cout<<"[Alive Handler > constructor] Couldn't bind to given port\n";
    }
    running=true;
}


Alive_Handler::~Alive_Handler()
{
    ;//dtor
}

void Alive_Handler::run_Ah(){
    if(DEBUG_ALIVE)
        cout<<"[Alive Handler] Running \n";

    FE.listen();
    while(!RE.is_open())
        FE.accept(RE);
    if(RE.is_open()){
        cout<<"[Alive Handler > run Ah] Request Emitter Connected\n";
    }
    while(!RI.is_open())
        FE.accept(RI);

    if(RI.is_open()){
        cout<<"[connection Handler > run Ah] Request Identifier Connected\n";
    }
    if(DEBUG_ALIVE){
        cout<<"[Alive Handler] Request Emitter Connected \n";
        cout<<"[Alive Handler] Request Identifier Connected \n";
    }

    future<void> RE_hand=async(std::launch::deferred,bind(&Alive_Handler::RE_handler,this)),
                 RI_hand=async(std::launch::deferred,bind(&Alive_Handler::RI_handler,this)),
                 //mesRE_hand=async(std::launch::deferred,bind(&Alive_Handler::mesRE_handler,this)),
                 CH_hand=async(std::launch::deferred,bind(&Alive_Handler::CH_handler,this));

}

unordered_map<string,Client_Detail>::iterator Alive_Handler::authen_client(const string &TOK,const string &TAB){

    auto C= regUsers.find(TOK);
    if(C!=regUsers.end()){
        for(auto tab:C->second.table){
            if(tab == TAB){
                return C->second.client;
            }
        }
    }
    return regClients.end();
}

void Alive_Handler::CH_handler(){

    while(running){
        string response;
        auto temp=CA.fetch_msg();
        vector< pair <string,string> > mesQuery;

          if(DEBUG_ALIVE){
                cout<<"[alive handler > CH handler] "<<endl;

                for(auto x:temp){
                    cout<<x.first<<" : "<<x.second<<" | ";
                }
                cout<<endl;
            }

        VVPSS mes;
        if(strcmp(temp[0].first.c_str(),"NONE")!=0){
            if(temp.size()<3){
               if(temp[0].first=="USR"){
                    Client_Detail tempC;
                    regClients.insert({temp[0].second,tempC});
                    AQ.send_msg({{"CMD","OPN"},{temp[0]}});              //send message to query parser to setup FHANDLER
                    continue;
               }
               else{
                    response="INVALID REQUEST";
               }
            }

            else if(temp[0].first=="MOD" && temp[1].first == "CMD" ){

                if(temp[0].second == "CLI"  && temp[2].first == "TOK"){


                    if(temp[1].second == "NEW" ){

                        auto clt= regUsers.find(temp[2].second);
                        if(clt==regUsers.end()){
                            Client_User tempU;
                            tempU.client= regClients.find(temp.back().second);

                            for(int i=3;i<temp.size()-2;i++){
                                if(temp[i].first=="TNAM"){
                                    tempU.table.push_back(temp[i].second);
                                }

                            }
                            response="USER ADMITTED";
                        }
                        else{
                            response="INVALID TOKEN";
                        }
                    }

                    else if(temp[1].second == "DEL"){                //delete current client
                        auto clt= regUsers.find(temp[2].second);

                        if(clt!=regUsers.end() && clt->second.client->first==temp.back().second){
                            regUsers.erase(clt);
                            response="USER DELETED";
                        }
                        else{
                            response="INVALID CLIENT IDENTIFIER";
                        }
                    }


                }

                else if(temp[0].second == "ADM" ){

                    auto tempC= regClients.find(temp.back().second);

                    if(tempC!=regClients.end()) {

                        if(temp[1].first == "ATAB" ){                 //set table to alive
                            auto tempC= regClients.find(temp.back().second);
                            if(tempC!=regClients.end()){
                                AQ.send_msg(temp);
                                continue;
                            }
                            else
                                response="INVALID RESPONSE";
                        }

                        if(temp[1].second == "DTAB"){                 //set table to dead
                                AQ.send_msg(temp);
                                continue;
                        }


                        else if(temp[1].second == "MLCK"){                  //toggle masterlock
                            //TODO: implement
                            response+="NOT FUNCTIONAL";
                        }

                        else if(temp[1].second == "TLCK"){                  //lock table

                            for(int i=2;i<temp.size()-1;i++){

                                if(temp[i].first=="TAB")
                                    tempC->second.locked_Tables.push_back(temp[i].second);
                                else
                                    break;
                            }
                            response="TABLES LOCKED";

                        }

                        else if(temp[1].second == "ULCK"){                  //unlock table

                            //TODO: IMPLEMENT
                            response="NOT FUNCTIONAL";
                        }


                        else if(temp[1].second == "QUER"){                  //Query on table
                            AQ.send_msg(temp);
                            continue;
                        }
                    }
                    else{
                        response="UNAUTHORIZED\n";
                    }
                }
            }

            mes.push_back({{temp[temp.size()-2]}});
            mes.push_back({{"RES",response}});
            string tempS=vvss_to_string(mes);
            MRE.lock();
            mesRE.push_back(tempS);
            MRE.unlock();
        }
    }
}


void Alive_Handler::RI_handler(){
    if(DEBUG_ALIVE)
        cout<<"[Alive Handler > RE handler] Ping\n";

    char buff[MAX_PAC_SIZE];
    RI.read_some(asio::buffer(buff,MAX_PAC_SIZE));
    MRI.lock();
    mesRI.push_back(buff);
    MRI.unlock();
}

void Alive_Handler::RE_handler(){
    if(DEBUG_ALIVE)
        cout<<"[Alive Handler > RR handler] Ping\n";
    while(running){
        if(!mesRE.empty()){
            MRE.lock();
            string temp=mesRE.front();
            mesRE.pop_front();
            MRE.unlock();
        }
    }
}

void Alive_Handler::mesRI_handler(){

    while(running){

        string temp;
        if(!mesRI.empty()){
            MRI.lock();
            temp=mesRI.front();
            mesRI.pop_front();
            MRI.unlock();
            auto request = string_to_vvss(temp);

            if(DEBUG_ALIVE){
                cout<<"[alive handler > mesRI handler] "<<temp<<endl;
                for(auto v:request){
                    for(auto x:v){
                        cout<<x.first<<" : "<<x.second<<" | ";
                    }
                    cout<<endl;
                }
            }

            auto slog= request[0];
            auto ulog= request[1];
            auto query= request[2];
            vector<pair<string,string> > mesQue;
            string response;
            if(ulog[0].first=="TOK" && query[0].first=="TAB"){
                auto client= authen_client(ulog[0].second,query[1].second);

                if(client!= regClients.end()){
                    mesQue=query;
                    mesQue.push_back({"USR",client->first});
                    mesQue.push_back(slog[0]);
                    AQ.send_msg(mesQue);
                    continue;
                }
            }

            string res= vvss_to_string({slog, { {"RES","INVALID" } } } );
            MRE.lock();
            mesRE.push_back(res);
            MRE.unlock();
        }
    }

}

//void Alive_Handler::mesQ_handler(){
//   if(DEBUG_ALIVE)
//        cout<<"[Alive Handler > mesQ handler] Request Identifier Connected\n";
//
//    while(running){
//        if(!mesQ.empty()){
//            MQ.lock();
//            auto mes=mesQ.front();
//            mesQ.pop_front();
//            MQ.unlock();
//
//            if(authen_client(mes)){
//
//                reqToToken[numReq]=mes[0][0].second;
//
//                if(numReq==1<<16)
//                    numReq=0;
//                else
//                    numReq++;
//
//                mes[1].push_back({"Rid",to_string(numReq)});
//
//                send_query(mes[1]);
//            }
//        }
//    }
//}

//void Alive_Handler::send_query(const vector<pair<string,string> > &query){
//    AQ.send_msg(query);
//}

//void Alive_Handler::send_req_ack(){
//    //TODO: send user ack to request emitter
//}

