#include "Query_Parser.h"
using namespace functionConnector;

Query_Parser::Query_Parser():FE(service),
              RE(service),
              AQ(true)
{

    chdir(QUERY_PATH);

    try{
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(SOCKET_QPAR_IP),SOCKET_QPAR_PORT);
        FE.open(asio::ip::tcp::v4());
        FE.bind(ep);
    }
    catch(...){
        cout<<"[Query Parser > Constructor ] Unable to bind to given port\n";
    }
    running=true;
}


Query_Parser::~Query_Parser()
{
    //dtor
}

void Query_Parser::run_Qp(){
    if(DEBUG_QUE)
        cout<<"[query parser] running\n";

    FE.listen();
    while(!RE.is_open())
        FE.accept(RE);

    if(DEBUG_QUE && RE.is_open()){
        cout<<"[query parser] Request Emitter Connected \n";
    }

    future<void> query_Han = async(std::launch::deferred,bind(&Query_Parser::query_Handler,this)),
                 RE_Han    = async(std::launch::deferred,bind(&Query_Parser::RE_Handler,this));

}

void Query_Parser::query_Handler(){
    while(running){
        string response;
        auto query= AQ.fetch_msg();

        if( query[0].first != "NONE" ){

            if(DEBUG_QUE){
                cout<<"[query parser > run QP] "<<endl;
                for(auto x:query){
                    cout<<x.first<<" : "<<x.second<<" | ";
                }
                cout<<endl;
            }

            if(query[0].first=="CMD"){
                if(query[0].second == "OPN"){
                    auto cPtr=activeClients.find(query[1].second);
                    if(cPtr==activeClients.end()){
                        Master_FHANDLER *temp=new Master_FHANDLER(query[1].second);
                        activeClients.insert({query[1].second,temp});
                        response="DATABASE SERVICE ACTIVE";
                    }
                    else{
                        response="ALREADY ACTIVE";
                    }
                }
                if(query[0].second == "ADM"){

                    if(query[1].second == "QUER"){
                         string usr= query.back().second;
                         auto client=activeClients.find(usr);

                        if(client!=activeClients.end()){

                            auto res=client->second->query_Table(query,0);
                            response= vvss_to_string2(res);

                        }
                        else {
                            response="INVALID REQUEST";
                        }
                    }

                    else if(query[1].second == "ATAB"){

                        string usr= query[query.size()-1].second;
                        auto client=activeClients.find(usr);

                        if(client!=activeClients.end()){
                            try{
                                auto res=client->second->set_Table_Active(query[1].second);
                                response= "INVALID REQUEST";
                            }
                            catch(...){
                                response="SOMETHING WENT WRONG";
                            }
                        }
                        else {
                            response="INVALID REQUEST";
                        }

                    }
                    else if(query[1].second == "DTAB"){
                        //TODO
                        response="NOT FUNCTIONAL";
                    }
                }
            }
            if(query[0].first == "TAB"){
                string usr= query[query.size()-1].second;
                auto client=activeClients.find(usr);

                if(client!=activeClients.end()){

                    auto res=client->second->query_Table(query,1);
                    response= vvss_to_string2(res);

                }
                else {
                    response="INVALID REQUEST";
                }
            }

            VVPSS mesT;
            string resS;
            mesT.push_back({query[query.size()-2]});
            mesT.push_back({{"RES",response}});
            resS=vvss_to_string(mesT);
            MRE.lock();
            mesRE.push_back(resS);
            MRE.unlock();
        }

    }
}

void Query_Parser::RE_Handler(){
    while(running){
        char temp[MAX_PAC_SIZE];
        if(!mesRE.empty()){
            MRE.lock();
            strcpy(temp,mesRE.front().c_str());
            mesRE.pop_front();
            MRE.unlock();
            RE.send(asio::buffer(temp,MAX_PAC_SIZE));
        }
    }
}
