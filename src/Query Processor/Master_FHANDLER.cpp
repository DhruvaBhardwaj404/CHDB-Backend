#include "Master_FHANDLER.h"

Master_FHANDLER::Master_FHANDLER(string uname)
{
    uname.resize(10);
    username = uname;
    string fname=username+".dat";
    MasterFile.open(fname.c_str(),ios::in );
    if(MasterFile.is_open()){
        MasterFile.read((char*)this,sizeof(Master_FHANDLER));
    }
    MasterFile.close();
    numAlive=0;
}


Master_FHANDLER::~Master_FHANDLER()
{
    string fname=username+".dat";
    MasterFile.open(fname.c_str(),ios::out);
    if(MasterFile.is_open()){
        MasterFile.seekp(0);
        MasterFile.write((char*)this,sizeof(Master_FHANDLER));
    }
    else{
        cout<<"error";
    }
     MasterFile.close();
}


vector<vector< pair<string,string> > > Master_FHANDLER::query_Table(const vector<pair<string,string> > &command,int mode){
    vector<vector< pair<string,string> > > response;

    if(mode==0){  //client admin mode

        if(command.size()>=4)
        if(command[2].first=="CREA" && command[3].first=="RATT" && command[4].first=="RKEY" ){

            if(tables.find(command[2].second) == tables.end()){

                try{
                    Hybrid_TabHandler New(username+command[2].second);

                    auto rel_attr = string_to_vvss2(command[3].second)[0];
                    auto rel_key =  string_to_vvss2(command[4].second)[0];
                    New.insert_Rel_Attr(rel_attr);
                    New.set_Key(rel_key);
                    tab_Details temp;
                    temp.created=time_t(nullptr);
                    temp.modified= time_t(nullptr);
                    tables.insert({command[2].second,{temp,{} }});
                    response.push_back({{"RES","CREATED"}});

                }
                catch(...){
                    response.push_back({{"RES","SOMETHING WENT WRONG"}});
                }

            }
            else {
                response.push_back({{"RES","ALREADY EXIST"}});
            }
        }

        if(command.size()==3){
        if(command[2].first=="DELE"){

            auto tab=tables.find(command[2].second);
            if(tab != tables.end()){
                remove((username+command[2].second).c_str());
                response.push_back({{"RES","DELETED"}});
            }
            else {
                response.push_back({{"RES","DOESN'T EXIST"}});
            }

        }
        }

        if(command.size()>=4){
        if(command[2].first=="INSE" && command[3].first=="DATA" ){
            auto tab = tables.find(command[2].second);
            if( tab != tables.end()){
                try{
                    auto data= string_to_vvss2(command[3].second);

                    if(tab->second.second){

                        auto ptr=(tab->second.second);
                        ptr->insert_Data(data);

                        response.push_back({{"RES","Values Inserted"}});

                    }
                    else{
                        response.push_back({{"RES","TABLE NOT ACTIVE"}});
                        //TODO: CALL NOT ACTIVE QUERY
                    }
                }
                catch(...){
                    response.push_back({{"RES","something went wrong"}});
                }
            }
            else {
                response.push_back({{"RES","TABLE NOT FOUND"}});
            }
        }
        }
    }

    if(mode==1){  //client user mode
        if(command[1].first=="SELE"){
            auto tab= tables.find(command[0].second);
            if(tab!=tables.end()){
                try{
                if(tab->second.second!=nullptr){
                    auto query=string_to_vvss(command[2].second)[0];

                    auto res=(tab->second.second)->fetch_Data(query);

                    string data= vvss_to_string2(res);
                    response.push_back({{"RES",data}});
                }
                else{
                    //TODO: CALL NOT ACTIVE QUERY
                }
                }catch(...){
                    response.push_back({{"RES","something went wrong"}});
                }

            }
            else{
                response.push_back({{"RES","INVALID REQUEST"}});
            }
        }
    }
    return response;
}

vector<vector<pair<string,string> > > query_Not_Active(const vector<pair<string,string> > &,int mode){
    return {{{"",""}}};
}



bool Master_FHANDLER::set_Table_Active(const string &name){
    auto tab=tables.find(name);
    if(tab!=tables.end()){

        if(tab->second.second==nullptr){

            if(numAlive<MAX_ACTIVE_LIMIT){
                Hybrid_TabHandler *T= new Hybrid_TabHandler(username+name);
                tab->second.second = T->getptr();
                numAlive++;
            }
            else{
                throw "ACTIVE LIMIT REACHED";
            }
        }
        else{
            throw "ALREADY ACTIVE";
        }
    }
    else{
        throw "TABLE DOESN'T EXIST";
    }
}

vector<pair<string,string> > Master_FHANDLER::get_Tables(){
    vector<pair<string,string> >  res;
    for(auto const & t : tables){
        if(t.second.second){
            res.push_back({t.first,""});
        }
    }
    return res;
}



