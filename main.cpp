#include <iostream>
#include<string>
#include<cstdlib>
#include<new>
#include<fstream>
#include<unistd.h>
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
#include<gtest/gtest.h>
#include<syscall.h>

#define GLOBAL_DEBUG false


using namespace std;


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

        conAli.construct< boost::circular_buffer<vector<pair<string,string> > > > (CONALI_CMESSAGE_BUFFER) (MAX_QUEUE_ALIQUE);
        conAli.construct< boost::circular_buffer<vector<pair<string,string> > > > (CONALI_AMESSAGE_BUFFER) (MAX_QUEUE_ALIQUE);
        //conAli.construct< queue<conAliHeader> >(CONALI_CQUEUE)();
        //conAli.construct< queue<conAliHeader> >(CONALI_AQUEUE)();

        boost::interprocess::named_mutex conAliMutex(boost::interprocess::open_or_create,CONALI_MUTEX);

        aliQue=BIP::managed_shared_memory(boost::interprocess::create_only,SHARED_MEM_ALIQUE,SHARED_MEM_SIZE_A2Q*4);
        //aliQueMeta temp2{0,0,time(nullptr)};
        //aliQue.construct<aliQueMeta>(ALIQUE_META)(temp2);

        aliQue.construct< boost::circular_buffer<vector<pair<string,string> > > > (ALIQUE_AMESSAGE_BUFFER) (MAX_QUEUE_CONALI);
        aliQue.construct< boost::circular_buffer<vector<pair<string,string> > > > (ALIQUE_QMESSAGE_BUFFER) (MAX_QUEUE_CONALI);
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

int main(int argc, char **argv)
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



    init_sharedMem();

    if(GLOBAL_DEBUG){
        chdir("/home/Death/Desktop");
        system("rm -r \"$PWD/test_CHDB\"");
        system("mkdir test_CHDB");
        chdir("/home/Death/Desktop/test_CHDB");
        system("pwd");
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();

    }
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
