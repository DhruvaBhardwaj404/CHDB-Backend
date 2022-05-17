#include "aliQueHandler.h"

aliQueHandler::aliQueHandler(bool m):aliQue(boost::interprocess::open_only,SHARED_MEM_ALIQUE),
            mutexAQ(boost::interprocess::open_only,ALIQUE_MUTEX)
{
    mode=m;
    //mesQA=aliQue.find<queue<conAliHeader> >(ALIQUE_AQUEUE).first;
    //mesQQ=aliQue.find<queue<conAliHeader> >(ALIQUE_QQUEUE).first;
    //sharedM=aliQue.find<aliQueMeta>(ALIQUE_META).first;
    mesA=aliQue.find<boost::circular_buffer<string> >(ALIQUE_AMESSAGE_BUFFER).first;
    mesQ=aliQue.find<boost::circular_buffer<string> >(ALIQUE_QMESSAGE_BUFFER).first;
//    offQ=0;
//    offA=0;
}


aliQueHandler::~aliQueHandler()
{
    //dtor
}

/***
    string aliQueHandler::fetch_msg()
        returns
            "NONE"  -> if message queue is empty
            MESSAGE -> if message exist

***/

string aliQueHandler::fetch_msg(){
    if(mode && mesQ->size()==0)
        return "NONE";
    else if(!mode && mesA->size()==0)
        return "None";
    string temp;

    mutexAQ.lock();
        if(mode){
            temp=(mesQ->front()).c_str();
            mesQ->pop_front();
            return temp;
        }

        else{
            temp=(mesA->front()).c_str();
            mesA->pop_front();
            return temp;
        }
    mutexAQ.unlock();
}

/***
    bool aliQueHandler::send_msg(int8_t action,const string &mess)

        return
            true  -> messages sent
            false -> unable to send

***/
bool aliQueHandler::send_msg(int8_t action,const string &mess){

    if(mode && mesQ->size()==MAX_QUEUE_ALIQUE){
        if(DEBUG_ALIQUEHANDLER)
            cout<<"[aliQueHandler -> send msg] : max pending req reached\n";
        return false;
    }


    else if(!mode && mesA->size()==MAX_QUEUE_ALIQUE){
        if(DEBUG_ALIQUEHANDLER)
            cout<<"[aliQueHandler -> send msg] : max pending req reached\n";
        return false;
    }

//    uint8_t s=log2((mess.size()/8));
//    conAliHeader temp;
//    temp.action=action;
//    temp.size=s;
//    temp.offset=offQ;
    mutexAQ.lock();
    if(mode){
        mesQ->push_back(mess);
    }
    else{
        mesA->push_back(mess);
    }
    mutexAQ.unlock();

}

//
//bool aliQueHandler::write_meta(){
//}
//
//bool aliQueHandler::read_meta(){
//
//}
