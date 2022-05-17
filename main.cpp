#include <iostream>
#include<string>
#include<cstdlib>
#include<new>
#include<fstream>
#include<unistd.h>
#include"functionsDB.h"
#include"Exisiting_DB.h"
#include"Database.h"
#include"Connection_Handler.h"
#include<syscall.h>
#include<unistd.h>
#include<sys/types.h>
#include"Alive_Handler.h"
#include"Query_Parser.h"
#include<boost/interprocess/managed_shared_memory.hpp>
#include<boost/interprocess/sync/named_mutex.hpp>
#include<boost/circular_buffer.hpp>
#include"commonMeth.h"



using namespace std;
using namespace functionsDB;

pid_t conHandler,queryPar,aliveHan;
BIP::managed_shared_memory conAli,aliQue;


bool start_ConHandler(){
    conHandler = fork();

    if(DEBUG_MAIN)
        cout<<"[main > start ConHandler] pid "<<conHandler<<endl;

    if(conHandler<0)
        throw ; //add exception
    else if(conHandler>0)
        return true;
    else
        return false;
}

bool start_queryPar(){
    queryPar = fork();

    if(DEBUG_MAIN)
        cout<<"[main > start queryPar] pid "<<queryPar<<endl;

    if(queryPar<0)
        throw ; //add exception
    else if(queryPar>0)
        return true;
    else
        return false;
}

bool start_aliveHandler(){

    aliveHan = fork();

    if(DEBUG_MAIN)
        cout<<"[main > start aliveHandler] pid "<<aliveHan<<endl;

    if(aliveHan<0)
        throw ; //add exception
    else if(aliveHan>0)
        return true;
    else
        return false;
}

/***
    init_sharedMem
    -  Initializes shared memory for communication between Connection_Handler,
        Alive_Handler and Query_Parser
    -  Intializes mutexes for the both the shared memories

**/
bool init_sharedMem(){
    try{
        BIP::shared_memory_object::remove(SHARED_MEM_ALIQUE);
        BIP::shared_memory_object::remove(SHARED_MEM_CONALI);

        conAli=BIP::managed_shared_memory(boost::interprocess::create_only,SHARED_MEM_CONALI,SHARED_MEM_SIZE_C2A*4);
        //conAliMeta temp{0,0,time(nullptr)};
        //conAli.construct<conAliMeta>(CONALI_META)(temp);

        conAli.construct< boost::circular_buffer<string> > (CONALI_CMESSAGE_BUFFER) (MAX_QUEUE_ALIQUE);
        conAli.construct< boost::circular_buffer<string> > (CONALI_AMESSAGE_BUFFER) (MAX_QUEUE_ALIQUE);
        //conAli.construct< queue<conAliHeader> >(CONALI_CQUEUE)();
        //conAli.construct< queue<conAliHeader> >(CONALI_AQUEUE)();

        boost::interprocess::named_mutex conAliMutex(boost::interprocess::open_or_create,CONALI_MUTEX);

        aliQue=BIP::managed_shared_memory(boost::interprocess::create_only,SHARED_MEM_ALIQUE,SHARED_MEM_SIZE_A2Q*4);
        //aliQueMeta temp2{0,0,time(nullptr)};
        //aliQue.construct<aliQueMeta>(ALIQUE_META)(temp2);

        aliQue.construct< boost::circular_buffer<string> > (ALIQUE_AMESSAGE_BUFFER) (MAX_QUEUE_CONALI);
        aliQue.construct< boost::circular_buffer<string> > (ALIQUE_QMESSAGE_BUFFER) (MAX_QUEUE_CONALI);
        //aliQue.construct< queue<aliQueHeader> >(ALIQUE_AQUEUE)();
        //aliQue.construct< queue<aliQueHeader> >(ALIQUE_QQUEUE)();

        boost::interprocess::named_mutex aliQueMutex(boost::interprocess::open_or_create,ALIQUE_MUTEX);

        return true;

    }catch(...){
        if(DEBUG_MAIN)
            cout<<"[main > init_sharedMem] Error\n";
        throw; //TODO:Add exception
    }
}

int main()
{
    try
    {

        char banner[6][50]= {{"|==============================================|"},
                             {"|           Cloud-Hybird Database              |"},
                             {"|                 MEGH KOSH                    |"},
                             {"|                Created by-                   |"},
                             {"|                  Dhruva                      |"},
                             {"|==============================================|"}
                            };

        for(int a=0; a<6; a++)
        {
            cout<<"\t\t\t"<<banner[a]<<endl;
        }







/*
//  fstream db;
//
//  do{
//
//   cout.flush();
//   cout<<endl<<"=> ";
//   getline(cin,command);
//   pcom=parse(command);
//
//   if(pcom[0]=="exit"){
//        break;
//     }
//
//   if(pcom.size()<2){
//        cout<<"[!!!]Insufficient arguments!";
//        continue;
//   }
//
//   if(pcom.size()==3){
//      if(pcom[0]=="create" && pcom[1]=="database"){
//
//          if(DB_info.find(pcom[2])==0){
//            cout<<endl<<"[!!!] Database with the same name exist!!"<<endl;
//          }
//
//          else{
//                DB_info.add(pcom[2]);
//                DB=new Database(pcom[2]);
//                DB->use_DB();
//                delete DB;
//                chdir("../");
//            }
//        }
//    }
//    else if(pcom.size()==2){
//      if(pcom[0]=="use"){
//          if(DB_info.find(pcom[1])==0){
//            string loc="./"+pcom[1];
//            chdir(loc.c_str());
//            DB=new Database();
//            DB->use_DB();
//            chdir("../");
//
//          }
//          else{
//            cout<<"[!!!] No database with specified name exist!";
//          }
//      }
//    }
//     else if(pcom[0]!="exit"){
//        cout<<endl<<"[!!!]Command not recognised!"<<endl;
//     }
//
//    db.open("Database_Info.txt",ios::out|ios::binary);
//    if(db.is_open()){
//        db.write((char*)&DB_info,sizeof(DB_info));
//        db.close();
//    }
//    else{
//        cout<<"[!!!]Couldn't update Database_Info.txt!";
//        exit(0);
//    }
//
//  }
//   while(command!="exit");
//    db.close();
*/
    init_sharedMem();
    if(start_ConHandler()){
         Connection_Handler Con;
         Con.run_Connector();//TODO: implement run_connector
    }
    else{
     if(start_aliveHandler()){//TODO: implement run aive_handler
              Alive_Handler Ah;
              Ah.run_Ah();
       }
        else{
            if(start_queryPar()){ //TODO: implement run querpar
                Query_Parser QP;
                QP.run_Qp(); //TODO: implement run QP;
            }
       }
    }
}
catch(...)
    {
        if(DEBUG_MAIN)
            cout<<"[!!!]error occurred in main()!";
    }
}



//TODO: SET UP SOCKET ACCEPTOR TO ACCEPT FE CONNETIONS
