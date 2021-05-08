#ifndef NSQL_COLHANDLER_H
#define NSQL_COLHANDLER_H
#include<string>
using std::string;

class NSQL_ColHandler
{
    public:
        char name[20];
        NSQL_ColHandler();
        void use_colHandler();
        void select_Table(string name);
        void create_Table(string name);
        void display_Table();
        void delete_Table();
        virtual ~NSQL_ColHandler();
    private:
        bool Table_name[3135],table_selected=false;
        string sel_tab_name;

};

#endif // NSQL_COLHANDLER_H
