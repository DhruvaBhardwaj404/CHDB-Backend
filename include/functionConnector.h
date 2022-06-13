#ifndef FUNCTIONCONNECTOR_H
#define FUNCTIONCONNECTOR_H
#include"paramDefinitions.h"
#include<asio.hpp>
#include<string>
#include<chrono>
#include<random>
#include<boost/asio/ip/address.hpp>
//#include"Handler.h"

using namespace std;

namespace functionConnector
{


    struct client_MDB{
        string cid;
        string oldTOK;
        string cUsername;
        string cPassword;
        time_t cLastActive;
        bool active;
        string cIP;

    };
    string gen_token(const string& name,const string &token);
    string gen_rand(const string&,const string&);
    string enc_UserId(const string &username,const string &id);

}

#endif // FUNCTIONCONNECTOR_H
