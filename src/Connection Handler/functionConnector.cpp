#include "functionConnector.h"

using namespace std;


string functionConnector::gen_rand(const string& data1,const string& data2){
    //TODO: create random ID generator
    return data1+data2;
}

string functionConnector::enc_UserId(const string &username,const string &id){
    //TODO :use openssl enc methods to encrypt
    return username+id;
}

string functionConnector::gen_token(const string& name,const string &token){
    return name+token;
}
