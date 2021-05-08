#include "NSQL.h"

NSQL::NSQL()
{
    //ctor
}

NSQL::~NSQL()
{
    //dtor
}

void use_NSQL();
void select_Table(string name);
void create_Table(string name);
void display_Table();
void add_entry();
void find_entry();
void update_entry();
void add_column(string name,string type);
void delete_column(string name);
