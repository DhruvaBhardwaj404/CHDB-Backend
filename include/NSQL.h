#ifndef NSQL_H
#define NSQL_H
#include<string>
#include<bitset>
using namespace std;

class NSQL
{
    public:
        NSQL();
        void use_NSQL();
        void select_Collection(string name);
        void create_Collection(string name);
        void display_Collection();
        void add_Collection();
        void delete_collection();
        virtual ~NSQL();

    private:
        bitset<3135> Collection_name;
        bool collection_selected=false;
        string sel_col_name;
};

#endif // NSQL_H
