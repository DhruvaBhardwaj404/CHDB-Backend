#ifndef COMMONMETH_H
#define COMMONMETH_H

#include"paramDefinitions.h"

using namespace std;

namespace commonMeth{

    struct RQueue{
        unsigned long long id;
        vector<string> query;
        vector<string> result;
    };
    vector<vector<pair<string,string > > > string_to_vvss(string data);
    vector<vector<pair<string,string > > > string_to_vvss2(string data);
    string vvss_to_string( vector<vector<pair<string,string > > > data);
    string vvss_to_string2( vector<vector<pair<string,string > > > data);

}


#endif // COMMONMETH_H
