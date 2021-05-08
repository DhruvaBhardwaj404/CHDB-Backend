#ifndef SQL_H
#define SQL_H
#include<string>
#include<bitset>
using namespace std;

class Handler
{
    public:
        SQL(string name);
        void use_SQL();
        void select_Collection(string name);
        void create_Collection(string name);
        void delete_collection();
        void display_Collection();
        virtual ~SQL();
    private:
        bitset<3135> col_name;
        bool col_Selected=false;
        char sel_Col_Name[20]="\0";
};

#endif // SQL_H
