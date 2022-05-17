#include "Connection_Handler.h"


using namespace std;

Connection_Handler::Connection_Handler():FE(service),
        file_MDB(MDB_FILENAME,ios::in | ios::out ),
        CA(false),
        RI(service)

{
    try{
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(SOCKET_CONHAN_IP),SOCKET_CONHAN_PORT);
        FE.open(asio::ip::tcp::v4());
        FE.bind(ep);
    }
    catch(...){
        cout<<"[Connection Handler > Constructor ]Unable to bind to given port\n";
    }

    //TODO: use conAliHAndler methods to share messages;

    running=true;

}

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

Connection_Handler::~Connection_Handler()
{

}

void Connection_Handler::run_Connector(){

    if(DEBUG_CONN)
        cout<<"[connection Handler] Running\n";

    future<void> reqHand= async(bind(&Connection_Handler::init_request_Handler,this),launch::async),
                //threadHan=async(bind(&Connection_Handler::thread_Handler,this),launch::async),
                adminHand=async(bind(&Connection_Handler::admin_Handler,this),launch::async),
                masterDB=async(bind(&Connection_Handler::init_Master,this),launch::async);

    FE.listen();
    asio::error_code e;
    FE.accept(RI,e);
    RI_handler(e);
}

void Connection_Handler::init_Master()
{
    /* TODO- open master_DB file and populate the table for MDB which is indexed with username
             in encrypted format
    */
    if(!file_MDB.is_open()){
        file_MDB.open(MDB_FILENAME,ios::in | ios::out);
    }
    client_MDB temp;
    string key;

    while(!file_MDB.eof()){
        file_MDB.read((char*)&temp,sizeof(temp));
        key=enc_UserId(temp.cUsername,temp.cid);
        //MDB.insert(make_pair(key,string));
    }

    file_MDB.close();  //TODO: timely update file_MDB with new ids


}

void Connection_Handler::init_request_Handler(){
    /* TODO: Run get_request handler on threads
    */

}
void Connection_Handler::get_request(){
    /*TODO: accept request from client server and send them to mes_handler */
//    char message[256];
//    //message.resize(200);
//    while(running){
//        asio::read(Fsock,asio::buffer(message),bind(comp_Checker,message,asio::buffer(message).size()));
//        mes_Handler(message);
//        /*TODO: Add log entry*/
//    }

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
            //TODO: on successful authentication send message to alive handler with client details
            // and return token id to client

//
            }
            else{
                throw;
                //TODO: Add exceptions
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

void Connection_Handler::RI_handler(asio::error_code){
    if(DEBUG_CONN)
        cout<<"[connection Handler] Request Identifier Connected\n";
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


