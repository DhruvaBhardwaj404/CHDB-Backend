#include "conAliHandler.h"

conAliHandler::conAliHandler(bool m):conAli(boost::interprocess::open_only,SHARED_MEM_CONALI),
            mutexCA(boost::interprocess::open_only,CONALI_MUTEX)
{
    mode=m;
//    mesQA=conAli.find<queue<conAliHeader> >(CONALI_AQUEUE).first;
//    mesQC=conAli.find<queue<conAliHeader> >(CONALI_CQUEUE).first;
//    sharedM=conAli.find< conAliMeta > (CONALI_META).first;
    mesA=conAli.find< boost::circular_buffer<string> > (CONALI_AMESSAGE_BUFFER).first;
    mesC=conAli.find< boost::circular_buffer<string> > (CONALI_CMESSAGE_BUFFER).first;

}

conAliHandler::~conAliHandler()
{
    //dtor
}

string conAliHandler::fetch_msg(){
if(mode && mesA->size()==0)
        return "NONE";
    else if(!mode && mesC->size()==0)
        return "None";
    string temp;

    mutexCA.lock();
        if(mode){
            temp=(mesA->front()).c_str();
            mesA->pop_front();
            return temp;
        }

        else{
            temp=(mesC->front()).c_str();
            mesC->pop_front();
            return temp;
        }
    mutexCA.unlock();
}


bool conAliHandler::send_msg(const string & mess){

    if(mode && mesA->size()==MAX_QUEUE_CONALI){
        if(DEBUG_CONALIHANDLER)
            cout<<"[colAliHandler -> send msg] : max pending req reached\n";
        return false;
    }


    else if(!mode && mesC->size()==MAX_QUEUE_CONALI){
        if(DEBUG_CONALIHANDLER)
            cout<<"[colAliHandler -> send msg] : max pending req reached\n";
        return false;
    }

//    uint8_t s=log2((mess.size()/8));
//    conAliHeader temp;
//    temp.action=action;
//    temp.size=s;
//    temp.offset=offQ;
    mutexCA.lock();
    if(mode){
        mesA->push_back(mess);
    }
    else{
        mesC->push_back(mess);
    }
    mutexCA.unlock();

}


//bool conAliHandler::write_meta(){
////    if(mode)
////        info_W->con_ack++;
////    else
////        info_w->ali_ack++;
//}
//bool conAliHandler::read_meta(){
//
//}
