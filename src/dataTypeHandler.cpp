#include "dataTypeHandler.h"


dataTypeHandler::dataTypeHandler()
{
    //ctor
}

dataTypeHandler::~dataTypeHandler()
{
    //dtor
}

string validate_Types(vps &cols){
vector<pair<string,int> > type_Table{{"INT",2},{"LONG LONG",8},{"FLOAT",4},{"DOUBLE",8},{"CHAR",1},{"STRING",20},{"OBJECT",10}};

    bool flag=0;
    for(auto &x:cols){

        for(auto &y:type_Table){
            unsigned int i=1;

            if(strcmp(y.first.c_str(),x.second.c_str())==0){
                x.second=char(i);
                flag=1;
                break;
            }
            i++;
        }
      if(flag==0){
        return ("[!!!]"+x.first+"=> specified type is not recognised!");
      }
      flag=0;
    }

    return "OK";
}
