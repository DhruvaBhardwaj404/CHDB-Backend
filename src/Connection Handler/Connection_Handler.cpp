#include "Connection_Handler.h"


using namespace std;

Connection_Handler::Connection_Handler():FE(service),
        file_MDB(MDB_FILENAME,ios::in | ios::out ),
        CA(false),
        RI(service),
        RE(service),
        ADMIN(service)

{
    chdir(CON_HAN_PATH);

    try{
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(SOCKET_CONHAN_IP),SOCKET_CONHAN_PORT);
        FE.open(asio::ip::tcp::v4());
        FE.bind(ep);
    }
    catch(...){
        cout<<"[Connection Handler > Constructor ]Unable to bind to given port\n";
    }

    running=true;

}


Connection_Handler::~Connection_Handler(){

}

void Connection_Handler::run_Connector(){

    if(DEBUG_CONN)
        cout<<"[connection Handler] Running\n";

    future<void> reqHand     =  async(bind(&Connection_Handler::init_request_Handler,this),launch::async),
                 mesAdminHand=  async(bind(&Connection_Handler::mesAdmin_Handler,this),launch::async),
                 masterDB    =  async(bind(&Connection_Handler::init_Master,this),launch::async),
                 mesQ_hand   =  async(bind(&Connection_Handler::mesQ_Handler,this),launch::deferred),
                 resQ_hand   =  async(bind(&Connection_Handler::resQ_Handler,this),launch::deferred);

    FE.listen();

    while(!RE.is_open()){
        FE.accept(RE);
    }
    if(RE.is_open()){
        cout<<"[connection Handler > run Connector] Request Emitter Connected\n";
    }
    while(!RI.is_open()){
        FE.accept(RI);
    }
    if(RI.is_open()){
        cout<<"[connection Handler > run Connector] Request Identifier Connected\n";
    }



    future<void> RI_hand    = async(bind(&Connection_Handler::RI_handler,this),launch::deferred),
                 admin_hand = async(bind(&Connection_Handler::admin_Handler,this),launch::deferred);

    FE.accept(ADMIN);
}

void Connection_Handler::init_Master(){

    if(!file_MDB.is_open()){
        file_MDB.open(MDB_FILENAME,ios::in | ios::out);
    }

    client_MDB temp;
    string key;

    while(!file_MDB.eof()){

        file_MDB.read((char*)&temp,sizeof(temp));
        key=enc_UserId(temp.cUsername,temp.cid);
        MDB.insert({key,temp});

    }

    file_MDB.close();  //TODO: timely update file_MDB with new ids

}

void Connection_Handler::init_request_Handler(){
    if(DEBUG_CONN)
        cout<<"[connection Handler > init_request_Handler] Ping\n";
    get_request();   //TODO: run multiple
}

void Connection_Handler::get_request(){

    while(running){
        char buff[MAX_PAC_SIZE];
        RI.receive(asio::buffer(buff,MAX_PAC_SIZE));
        MQ.lock();
        mesQ.push_back(buff);
        MQ.unlock();

    }
}

void Connection_Handler::new_ClientHandler(VVPSS request){

    auto slog=request[0];
    auto log= request[2];
    VVPSS response;
    response.push_back(request[0]);
    vector<pair<string,string> > mesAlive;
    string temp;

    if(log[1].first =="USR" && log[2].first=="PAS" && log[3].first=="CID"){

        auto login=client_Authen(log[1].second,log[2].second,log[3].second);

        if(login!=MDB.end()){

            login->second.cIP=slog[1].second;
            login->second.cLastActive=time(nullptr);
            login->second.active=true;
            //TODO: generate new token and update
            string token= gen_token( login->second.cUsername,login->second.oldTOK);

            authClients.insert({token,login});

            response.push_back({{"STA","LOGIN SUCCESFULL"},{"TOK",token}});
            temp=vvss_to_string(response);
            RQ.lock();
            resQ.push_back(temp);
            RQ.unlock();

            mesAlive.push_back(log[1]);
            CA.send_msg(mesAlive);
            return;
        }
    }

    response.push_back({{"STA","LOGIN UNSUCCESSFUL"}});
    temp=vvss_to_string(response);
    RQ.lock();
    resQ.push_back(temp);
    RQ.unlock();
    return;
}

void Connection_Handler::exist_ClientHandler(VVPSS request){

    auto slog=request[0];
    auto log=request[1];
    VVPSS response;
    string temp;
    vector<pair<string,string> > mesAlive;
    if(log[1].first=="USR" && log[2].first=="TOK"){

        auto client=authClients.find(log[2].second);

        if(client!=authClients.end()){
            if(slog[1].second == client->second->second.cIP && log[1].second == client->second->second.cUsername){
                mesAlive= request[2];
                mesAlive.push_back(slog[0]);        //front end reqNum;
                mesAlive.push_back(request[1][1]);  // Username
                CA.send_msg(mesAlive); //TODO: ADD check
                return;
            }
        }
    }

    response.push_back(request[0]);
    response.push_back({{"STA","LOGIN UNSUCCESSFUL"}});
    temp=vvss_to_string(response);
    RQ.lock();
    resQ.push_back(temp);
    RQ.unlock();
}

unordered_map<string,client_MDB>::iterator Connection_Handler::client_Authen(const string &username,const string &password,const string &id) {
    if(DEBUG_CONN){
        cout<<"[connection handler > client authen] "<<username<<" "<<password<<" "<<id<<endl;
    }
    string key=enc_UserId(username,id);
    auto temp= MDB.find(key);

    if(temp!=MDB.end()){
        if(temp->second.cPassword.compare(password)==0)
            return temp;
    }

    return MDB.end();
}

void Connection_Handler::admin_Handler(){
    if(DEBUG_CONN)
        cout<<"[connection Handler > admin_Handler] Ping\n";
    char buff[1024];
    while(running ){
        if(ADMIN.is_open()){
            ADMIN.read_some(asio::buffer(buff,MAX_PAC_SIZE));
            MA.lock();
            mesAdmin.push_back(buff);
            MA.unlock();
        }
    }
}

void Connection_Handler::mesAdmin_Handler(){
    if(DEBUG_CONN)
        cout<<"[connection Handler > mesAdmin_Handler] Ping\n";
    while(running){
        string temp;
        if(!mesAdmin.empty()){
            MA.lock();
            temp=mesAdmin.front();
            mesAdmin.pop_front();
            MA.unlock();
            auto request = string_to_vvss(temp);

             if(DEBUG_CONN){
                cout<<"[connection Handler > mesAdmin Handler] "<<temp<<endl;
                for(auto v:request){
                    for(auto x:v){
                        cout<<x.first<<" : "<<x.second<<" | ";
                    }
                    cout<<endl;
                }
            }

            if(request[0][0].second == "NEW"){
                string username=request[0][1].second;
                string id=request[0][2].second;
                string password=request[0][3].second;
                string ip=request[0][4].second;
                if(MDB.find(username)==MDB.end()){
                    client_MDB temp;
                    temp.cUsername=username;
                    temp.cid=id;
                    temp.cPassword=password;
                    temp.cIP=ip;

                    MDB.insert({username,temp});
                }
                else{
                    //TODO send invalid response
                }
            }
        }
    }
}

void Connection_Handler::RI_handler(){

    if(DEBUG_CONN)
        cout<<"[connection Handler > RI handler] Ping\n";

    char buff[MAX_PAC_SIZE];
    while(running){
        RI.read_some(asio::buffer(buff,MAX_PAC_SIZE));
        MQ.lock();
        mesQ.push_back(buff);
        MQ.unlock();
    }
}

void Connection_Handler::resQ_Handler(){
    if(DEBUG_CONN)
        cout<<"[connection Handler > resQ handler] Ping\n";
    char buff[MAX_PAC_SIZE];

    while(running){
        if(!resQ.empty()){
            RQ.lock();
            strcpy(buff,resQ.front().c_str());
            resQ.pop_front();
            RQ.unlock();
            RE.send(asio::buffer(buff,MAX_PAC_SIZE));
        }
    }
}

void Connection_Handler::mesQ_Handler(){
     if(DEBUG_CONN)
        cout<<"[connection Handler > mesQ Handler] Ping\n";

    vector<vector<pair<string,string> > > temp;
    string tempM;
    while(running){
        if(!mesQ.empty()){
            MQ.lock();
            tempM=mesQ.front();
            mesQ.pop_front();
            MQ.unlock();

            temp= string_to_vvss(tempM);

            if(DEBUG_CONN){
                cout<<"[connection Handler > mesQ Handler] "<<tempM<<endl;
                for(auto v:temp){
                    for(auto x:v){
                        cout<<x.first<<" : "<<x.second<<" | ";
                    }
                    cout<<endl;
                }
            }

            if( temp[1][0].first.compare("RTY") != 0){

            }
            string reqT=temp[1][0].second;

            if( reqT=="NEW"){
                new_ClientHandler(temp);
            }
            else if(reqT=="EXI"){
                exist_ClientHandler(temp);
            }

        }
    }
}


/*
void Connection_Handler::thread_Handler(){
    while(running){
        for(short i=0;i<MAX_THREADS;i++){
            if(emptyThreads[i]==1 && tLock.try_lock_for(chrono::milliseconds(MAX_WAIT))){
                if(Client[i].get()!=nullptr){
                    if((Client[i].get())->joinable()==true){
                        //Alive[i].reset();
                        reqHandler[i].release();
                        emptyThreads[i]==0;
                        getEmpty.push_back(i);
                    }
                }
                tLock.unlock();
            }
        }
    }
}
*/

//void Connection_Handler::mes_Handler(){
//    vector<vector<pair<string,string> > > req;
//    string temp;
//    while(running){
//        while(!mesQ.empty()){
//            MQ.lock();
//            temp=mesQ.front();
//            mesQ.pop_front();
//            MQ.unlock();
//
//            req = string_to_vvss(temp);
//            if( req[0][0].first.compare("RTY") == 0 && req[0][1].first.compare("TOK")==0 ){
//
//                if(req[0][0].second.compare("NEW")){
//                    new_ClientHandler(req);
//                }
//                else if(req[0][0].second.compare("EXI")){
//                    exist_ClientHandler(req);
//                }
//                else if(req[0][0].second.compare("STA")){
//                    start_ClientHandler(req);
//                }
//                else{
//                    throw "UNEXPECTED REQUEST";
//                }
//            }
//        }
//    }
//}

//void Connection_Handler::start_ClientHandler(VVPSS request){
//

//}
/*
Connection_Handler::Connection_Handler(string ep,int port):Fsock(service)//,Asock(service)
{
    try{
        Fsock.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(ep),port));
        Asock.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(ep),port));
    }
    catch(...){
        cout<<"[!!!]Unable to connect to Fsock or Asock!\n";
    }

    for(int i=0;i<MAX_THREADS;i++){
        reqHandler.push_back({});
        Alive.push_back({});
        emptyThreads[i]=0;
        getEmpty.push_back(i);
    }
}
*/


