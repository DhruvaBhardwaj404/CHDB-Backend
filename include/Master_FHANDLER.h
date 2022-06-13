#ifndef MASTER_FHANDLER_H
#define MASTER_FHANDLER_H
#include"paramDefinitions.h"
#include"Hybrid_TabHandler.h"
#include"commonMeth.h"
#define MAX_ACTIVE_LIMIT 10
#include<list>
using namespace std;
using namespace commonMeth;

class Master_FHANDLER
{
    public:
        Master_FHANDLER(string);
        vector<vector<pair<string,string> > > query_Table(const vector<pair<string,string> > &,int mode);
        bool set_Table_Active(const string &);
        bool set_Table_Inactive(const string &);
        vector<pair<string,string> >  get_Tables();
        vector<vector<pair<string,string> > > query_Not_Active(const vector<pair<string,string> > &,int mode);
       ~Master_FHANDLER();

    private:
        unordered_map<string,pair<tab_Details,shared_ptr<Hybrid_TabHandler> > > tables;
        string username;
        uint8_t numAlive;
        fstream MasterFile;

};

        //bool create_Table(const string &name,const vector<pair<string,string> > &attr,const vector<pair<string,string> > &key);
        //bool delete_Table(string name);

#endif // MASTER_FHANDLER_H
