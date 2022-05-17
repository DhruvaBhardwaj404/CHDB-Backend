#ifndef COMMONMETH_H
#define COMMONMETH_H

#include"paramDefinitions.h"

using namespace std;

namespace commonMeth{
//    struct conAliHeader{
//        uint8_t action:4;
//        uint8_t size:4;
//        uint16_t offset;
//    };
//
//    struct aliQueHeader{
//        uint8_t action:4;
//        uint8_t payload:4;
//        uint16_t offset;
//    };

    struct RQueue{
        unsigned long long id;
        vector<string> query;
        vector<string> result;
    };

//    struct conAliMeta{
//        uint8_t con_ack;
//        uint16_t con_sent;
//        uint8_t ali_ack;
//        uint16_t ali_sent;
//        time_t last;
//    };
//
//    struct aliQueMeta{
//        uint8_t que_ack;
//        uint16_t que_sent;
//        uint8_t ali_ack;
//        uint16_t ali_sent;
//        time_t last;
//    };

}


#endif // COMMONMETH_H
