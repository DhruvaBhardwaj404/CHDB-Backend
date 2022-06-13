#ifndef FUNCTIONALIVE_H
#define FUNCTIONALIVE_H

#include<string>
#include<vector>
#include"paramDefinitions.h"

using namespace std;

namespace functionAlive{
    struct Client_Detail{
        bool MasterLock=false;
        vector<string> locked_Tables;
    };

    struct Client_User{
        unordered_map<string,Client_Detail>::iterator client;
        vector<string> table;
    };



}

#endif // FUNCTIONALIVE_H
