#ifndef HYBRID_TABHANDLER_H
#define HYBRID_TABHANDLER_H
#include<fstream>
#include"paramDefinitions.h"
#include"functionQuery.h"

using namespace std;
using namespace functionQuery;

class Hybrid_TabHandler:enable_shared_from_this<Hybrid_TabHandler>
{
public:
    Hybrid_TabHandler(const string &name);
    Hybrid_TabHandler(const Hybrid_TabHandler &obj);
    std::shared_ptr<Hybrid_TabHandler> getptr();
    void set_Key(const vector<pair<string,string> >&);
    void insert_Rel_Attr(const vector<pair<string,string> >& );
    void insert_Data(const vector<vector<pair<string,string> > >&);
    void delete_Data(const vector<vector<pair<string,string> > >&);
    vector<pair<string,string> > get_Rel_Attr();
    vector<pair<string,string> > get_Key();
    vector<vector<pair<string,string> > > fetch_Data(const vector<pair<string,string> >& );
    ~Hybrid_TabHandler();
private:
    unordered_map<string,int> relAttr;
    vector<string> vrelAttr;
    vector<pair <string,int> > key;
    //unordered_map<string,uint8_t> Attr;
    unordered_map<string,pair< vector<string>,
                                unordered_map<string,vector < pair < string , string > > >::iterator
                             > > relTup;
    unordered_map<string,vector<pair<string,string> > > nonRelTup;
    uint32_t numRel=0;
    string tabName;

};

#endif // HYBRID_TABHANDLER_H
