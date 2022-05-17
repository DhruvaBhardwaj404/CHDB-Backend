#ifndef HYBRID_TABHANDLER_H
#define HYBRID_TABHANDLER_H

#include"paramDefinitions.h"

#define MAX_HYBRID_SIZE 20
#define MAX_RDATA_SPACE 8
#define MAX_SCHUNKS_SPACE 5
#define MAX_FCHUNKS_SPAC 7

using namespace std;

class Hybrid_TabHandler
{
public:
    Hybrid_TabHandler(string data);
    void insert_Data(string);
    void delete_Data(string);
    void fetch_Data(string);
    ~Hybrid_TabHandler();

private:
};

#endif // HYBRID_TABHANDLER_H
