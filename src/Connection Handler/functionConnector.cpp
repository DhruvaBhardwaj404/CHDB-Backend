#include "functionConnector.h"

using namespace std;



vector<string> functionConnector::parse_FrontEnd_Mess(const string &mes){
    //TODO: create request structure
    vector<string> request;
    string temp;
    bool flag=false,jflag=false;

    for(auto x: mes){
        if(x==':'){
            flag=true;
            continue;
        }
        if(x=='\n'){
            flag=false;
            request.push_back(temp);
            temp.clear();
            continue;
        }
        if(flag==true){
            temp+=x;
        }
    }
}

string functionConnector::gen_rand(const string& data1,const string& data2){
    //TODO: create random ID generator
    return "ABC";
}

string functionConnector::enc_UserId(string username,__int64_t id){
    //TODO :use openssl enc methods to encrypt
    return "A";
}
