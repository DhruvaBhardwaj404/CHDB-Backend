#include "Master_FHANDLER.h"

Master_FHANDLER::Master_FHANDLER(string uname,string id)
{
    uname.resize(5);
    string n = uname+id;
    //if(exists(n))
        MasterFile.open(n,ios::in | ios::out);
    //else{
      //  MasterFile.open(n,ios::in | ios::out);
        //MasterFile.seekg(1<<MASTER_FILE_SIZE);
        //}
}

Master_FHANDLER::~Master_FHANDLER()
{
    //dtor
}

void Master_FHANDLER::manage_Tables(vector<string> command){
    //TODO: add commands;
}

bool Master_FHANDLER::toggle_MasterLock(){

}

bool Master_FHANDLER::set_Active_Tables(string){
    //TODO: Create Hybrid table object asked by front end
}
