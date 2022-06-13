#include "Hybrid_TabHandler.h"

Hybrid_TabHandler::Hybrid_TabHandler(const string &name)
{
    tabName=name;
    fstream TAB;
    string fname=tabName+".dat";
    TAB.open(fname.c_str(),ios::in);
    if(!TAB.fail()){
        TAB.read((char*)this,sizeof(Hybrid_TabHandler));
    }
    else{
        TAB.open(fname.c_str(),ios::trunc);
    }
    TAB.close();
}

Hybrid_TabHandler::Hybrid_TabHandler(const Hybrid_TabHandler &obj){
    relAttr=obj.relAttr;
    vrelAttr=obj.vrelAttr;
    key=obj.key;
    relTup=obj.relTup;
    nonRelTup=obj.nonRelTup;
    numRel=obj.numRel;
    tabName=obj.tabName;

}

Hybrid_TabHandler::~Hybrid_TabHandler()
{
    ofstream TAB;
    string fname=tabName+".dat";
    TAB.open(fname.c_str(),ios::out );
    if(TAB.fail()){
        TAB.open(fname.c_str(),ios::out | ios::trunc);
    }
    TAB.write((char*)this,sizeof(Hybrid_TabHandler));
        TAB.flush();
        TAB.close();


}

std::shared_ptr<Hybrid_TabHandler> Hybrid_TabHandler::getptr() {
        return shared_from_this();
}

void Hybrid_TabHandler::set_Key(const vector<pair<string,string> > &a){
    if(relAttr.size()==0)
        throw "Attributes not initialized";

    if(key.size()==0 ){

        for(auto x:a){
            auto it=relAttr.find(x.second);
            if(it!=relAttr.end()){
                key.push_back({x.second,it->second});
            }
            else{
                throw "No column of specified name exist";
            }
        }
        return;
    }

    throw "undefined error";
}

vector<pair<string,string> > Hybrid_TabHandler::get_Key(){
    vector<pair<string,string> > res;
    for(auto const &x:key){
        res.push_back({x.first,to_string(x.second)});
    }
    return res;
}

void Hybrid_TabHandler::insert_Rel_Attr(const vector<pair<string,string> > &a){
    if(numRel==0){
    for(auto x: a){
        if(relAttr.find(x.second)==relAttr.end()){
            relAttr.insert({x.second,numRel});
            vrelAttr.push_back(x.second);
            numRel++;
        }
    }
    }
    else{
        throw;  //TODO
    }
}

vector<pair<string,string> > Hybrid_TabHandler::get_Rel_Attr(){
    vector<pair<string,string> > attr(numRel);

    for(auto x: relAttr){
        string y=to_string(x.second+1);
        attr[x.second]={y,x.first};
    }
    return attr;
}

void Hybrid_TabHandler::insert_Data(const vector<vector<pair<string,string> > > &data){
    vector<string> tempR(numRel);
    vector<pair<string,string> > tempNr;
    vector<vector<string> > pRdata;
    vector<vector<pair<string,string> > > pNRdata;

    if(key.size()==0)
        throw "KEY NOT INITIALISED";

    vector<string> tupKeys;

    for(auto x:data){
        string tempkey;

        for(auto tup:x){

            auto it= relAttr.find(tup.first);
            if(it!=relAttr.end()){
                tempR[it->second]=tup.second;
            }
            else{
                tempNr.push_back(tup);
            }
        }

//        for(auto x:tempR){
//            cout<<x<<" ";
//        }
//        cout<<endl;

        for(auto k:key){
            if(tempR[k.second].size()==0)
                throw "key attribute missing";
            else{
                tempkey+=tempR[k.second];
            }
        }
        if(relTup.find(tempkey)==relTup.end())
            tupKeys.push_back(tempkey);
        else
            throw "key collision";
        pRdata.push_back(tempR);
        pNRdata.push_back(tempNr);
        tempR.clear();
        tempNr.clear();
        tempR.resize(numRel);
    }

//    for(int i=0;i<tupKeys.size();i++){
//        cout<<tupKeys[i]<<endl;
//        for(auto x:  pRdata[i]){
//            cout<<x<<" ";
//        }
//        for(auto x:pNRdata[i]){
//            cout<<x.first<<" "<<x.second<<endl;
//        }
//        cout<<endl;
//    }

    for(int i=0;i<tupKeys.size();i++){
        if(pNRdata[i].size()!=0){
            auto it=nonRelTup.insert({tupKeys[i],pNRdata[i]}).first;
            relTup.insert({tupKeys[i],{pRdata[i],it}});
        }
        else{
            relTup.insert({tupKeys[i],{pRdata[i],nonRelTup.end()}});
        }
    }
   return;
}

void Hybrid_TabHandler::delete_Data(const vector<vector<pair<string,string> > > &data){

}

vector<vector<pair<string,string> > > Hybrid_TabHandler::fetch_Data(const vector<pair<string,string> >  &data){
    vector<vector<pair<string,string> > > res;
    vector<pair<string,string> > temp;
    if(data.size()==0){

        for(auto const &x:relTup){
            for(int i=0;i<vrelAttr.size();i++){
                temp.push_back({vrelAttr[i],x.second.first[i]});
            }
            if(x.second.second!=nonRelTup.end()){
                auto ptr=x.second.second;
                for(auto const &d: ptr->second){
                    temp.push_back(d);
                }
            }
            res.push_back(temp);
            temp.clear();
        }
        return res;
    }
    throw "TABLE EMPTY";
}
