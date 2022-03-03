#include "Connection_Handler.h"


using namespace std;

Connection_Handler::Connection_Handler():Fsock(service),Asock(service)
{
    try{
        Fsock.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"),5000));
        Asock.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"),5001));
    }
    catch(...){
        cout<<"[!!!]Unable to connect to Fsock or Asock!\n";
    }

    running=true;
    for(int i=0;i<MAX_THREADS;i++){
        Client.push_back({});
        emptyThreads[i]=0;
        getEmpty.push_back(i);
        Alive.push_back({});
    }
}

Connection_Handler::Connection_Handler(string ep,int port):Fsock(service),Asock(service)
{
    try{
        Fsock.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(ep),port));
        Asock.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string(ep),port));
    }
    catch(...){
        cout<<"[!!!]Unable to connect to Fsock or Asock!\n";
    }

    for(int i=0;i<MAX_THREADS;i++){
        Client.push_back({});
        Alive.push_back({});
        emptyThreads[i]=0;
        getEmpty.push_back(i);
    }
}

Connection_Handler::~Connection_Handler()
{

}

void Connection_Handler::run_Connector(){
    future<void> reqHand= async(bind(&Connection_Handler::request_Handler,this),launch::async),
                threadHan=async(bind(&Connection_Handler::thread_Handler,this),launch::async),
                adminHand=async(bind(&Connection_Handler::admin_Handler,this),launch::async);
                //masterDB=async(bind(&Connection_Handler::init_Master,this,launch::async));

}

void Connection_Handler::init_Master()
{
    clientDB= new Query_Parser();

    // TODO- open master table of clients
}

void Connection_Handler::request_Handler(){
    char message[256];
    //message.resize(200);
    while(running){
        asio::read(Fsock,asio::buffer(message),bind(comp_Checker,message,asio::buffer(message).size()));
        mes_Handler(message);
        /*TODO: Add log entry*/
    }
}

void Connection_Handler::mes_Handler(const string &mes){
    vector<string> request=parse_FrontEnd_Mess(mes);

    if(request[0]=="NEW"){
        new_ClientHandler(request);
    }
    else if(request[0]=="EXI"){
        exist_ClientHandler(request);
    }
    else if(request[0]=="STA"){
        start_ClientHandler(request);
    }
    else{
        throw "UNEXPECTED REQUEST";
    }
}

bool Connection_Handler::comp_Checker(const string &mes,int size){
    if(size>2 && size<MAX_PAC_SIZE){
        if(mes[size-2]=='\\' && mes[size-2]=='>')
            return true;
        else
            return false;
    }
   return false;
}

void Connection_Handler::new_ClientHandler(const vector<string> &request){
    //TODO: authenticate using table from database
}
void Connection_Handler::exist_ClientHandler(const vector<string> &request){
    //TODO: manage existing active client accessed by admin panel
}

void Connection_Handler::start_ClientHandler(const vector<string> &request){
    try{
        clientData C;
        string temp=request[1];
        string::iterator s=temp.begin(),e=temp.end();
        vector<pair<string,string>> details=functionsDB::parse(s,e);
        if(client_Authen(details[0].second,details[1].second)==true){
            string ID=gen_rand(details[0].second,details[1].second);
            string token=gen_rand(details[1].second,ID);
            C.token=token;
            int i;
            if(getEmpty.empty()==false){
                if(tLock.try_lock_for(chrono::milliseconds(MAX_WAIT))){
                    i=getEmpty.back();
                    getEmpty.pop_back();
                    emptyThreads[i]=0;
                    tLock.unlock();
                }
                getEmpty.pop_back();
                C.clientThread=i;
                authClients.insert({ID,C});
                Alive[i] = shared_ptr<Alive_Handler>(new Alive_Handler());
                Client[i]= unique_ptr<thread>(new thread(bind(&Alive_Handler::run_Ah,(Alive[i].get()))));

            }
            else{
                throw;
                //TODO: Add exceptions
            }
        }

    }
    catch(...){
        cout<<"[!!!] Error in start_ClientHandler!\n";
    }
}



bool Connection_Handler::client_Authen(string username,string password){
    //TODO:return true if client exist
    return true;
}

void Connection_Handler::admin_Handler(){
    ;
}

void Connection_Handler::thread_Handler(){
    while(running){
        for(short i=0;i<MAX_THREADS;i++){
            if(emptyThreads[i]==1 && tLock.try_lock_for(chrono::milliseconds(MAX_WAIT))){
                if(Client[i].get()!=nullptr){
                    if((Client[i].get())->joinable()==true){
                        Alive[i].reset();
                        Client[i].release();
                        emptyThreads[i]==0;
                        getEmpty.push_back(i);
                    }
                }
                tLock.unlock();
            }
        }
    }
}


