#ifndef MASTER_FHANDLER_H
#define MASTER_FHANDLER_H

#define MASTER_FILE_SIZE 25               //4kb
#define MAX_ACTIVE_LIMIT
#include"paramDefinitions.h"
#include<filesystem>
#include"Hybrid_TabHandler.h"

using namespace std;

class Master_FHANDLER
{
    public:
        Master_FHANDLER(string,string);
        void manage_Tables(vector<string>);
        bool set_Active_Tables(string);
        bool toggle_MasterLock();
       ~Master_FHANDLER();

    private:
        map<string, pair<vector<int8_t>,bool > > Tables;
        vector<Hybrid_TabHandler> active_Tables;
        bool MasterLock;
        fstream MasterFile;
        string nextMasterFile;

};

#endif // MASTER_FHANDLER_H
