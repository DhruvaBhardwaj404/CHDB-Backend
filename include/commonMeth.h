#ifndef COMMONMETH_H
#define COMMONMETH_H

#include"paramDefinitions.h"

using namespace std;

namespace commonMeth{
    struct conAliHeader{
        int action:4;
        int size:4;
    };

    struct aliQueHeader{
        int action:4;
        int payload:4;
    };

    struct RQueue{
        unsigned long long id;
        vector<string> query;
        vector<string> result;
    };

    struct conAliMeta{

    };

    struct aliQueMeta{

    };


}


#endif // COMMONMETH_H
