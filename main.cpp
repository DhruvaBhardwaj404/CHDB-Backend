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
#include<boost/interprocess/shared_memory_object.hpp>
#include<boost/interprocess/mapped_region.hpp>



using namespace std;
using namespace functionsDB;

pid_t conHandler,queryPar,aliveHan;
BIP::shared_memory_object conAli,aliQue;


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

bool init_sharedMem(){
    try{
        BIP::shared_memory_object::remove("ConAli");
        BIP::shared_memory_object::remove("AliQue");

        conAli=BIP::shared_memory_object(create_only,SHARED_MEM_CONALI,read_write);
        conAli.truncate(SHARED_MEM_SIZE_C2A);

        aliQue=BIP::shared_memory_object(create_only,SHARED_MEM_ALIQUE,read_write);
        aliQue.truncate(SHARED_MEM_SIZE_A2Q);

        return true;

    }catch(...){
        throw; //TODO:Add exception
    }
}

int main()
{
    try
    {

        char banner[6][50]= {{"|==============================================|"},
                             {"|                 DBMS 1.0                     |"},
                             {"|                   KOSH                       |"},
                             {"|                created by-                   |"},
                             {"|                  Dhruva                      |"},
                             {"|==============================================|"}
                            };

        for(int a=0; a<6; a++)
        {
            cout<<"\t\t\t"<<banner[a]<<endl;
        }




//TODO: create three different processes for AH,CH,QP
//TODO: intialise shared memory for IPC

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
        cout<<"[!!!]error occurred in main()!";
    }
}
