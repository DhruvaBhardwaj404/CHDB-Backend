#ifndef FUNCTIONCONNECTOR_H
#define FUNCTIONCONNECTOR_H
#include"paramDefinitions.h"
#include<asio.hpp>
#include<string>
#include<chrono>
#include<random>
#include<boost/asio/ip/address.hpp>
#include"Handler.h"

using namespace std;

namespace functionConnector
{



    struct alive_Instance{
        string DB,Col,Tab;
        int type;
    };

    struct table_Nopen{
        vector<NSQL_TabHandler> tab;
        vector<bool> active;
    };

    struct table_Sopen{
        vector<SQL_TabHandler> tab;
        vector<bool> active;
    };

    struct table_Hopen{
    //        vector<Hybrid_TabHandler> tab;
    vector<bool> active;
    };

    struct collection_Open
    {
        unordered_map<string,shared_ptr<table_Nopen> > Ntab;
        unordered_map<string,shared_ptr<table_Sopen> > Stab;
        vector<bool> active;
    };

    struct database_Open
    {
        unordered_map<string,shared_ptr<collection_Open>> col;
        vector<bool> active;
    };

    struct clientData
    {

    string token;
    int clientThread;
    };

    struct client_MDB{
        __int64_t cid;          //changes everyday
        string cUsername;
        string cPassword;
        time_t cLastActive;
        bool active;
        boost::asio::ip::address cIP;

    };

    vector<string> parse_FrontEnd_Mess(const string& mes);
    string gen_rand(const string&,const string&);
    string enc_UserId(string username,__int64_t id);

}

#endif // FUNCTIONCONNECTOR_H
