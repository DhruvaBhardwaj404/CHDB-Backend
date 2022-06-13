#include "commonMeth.h"


/*  <<!
    first:second,
    !>>
    <<?
        [(first,second),]
        []
     ?>>
*/
vector<vector<pair<string,string > > > commonMeth::string_to_vvss(string data){

    vector<vector<pair<string,string > > > res;
    vector<pair<string,string > >  tempV;
    pair<string,string> tempP;
    string tempS;
    int i=0;

    if(data[i]=='<' && data[i+1]=='<' && data[i+2]=='!'){
    //Extracting Server Added Information

    for(i=3;i<data.size();i++){


        if(data[i]=='!'){
            tempP.second=tempS;
            tempS.clear();
            tempV.push_back(tempP);
            tempP.first.clear();
            tempP.second.clear();
            i+=3;
            break;
        }
        if(data[i]==','){
            tempP.second=tempS;
            tempS.clear();
            tempV.push_back(tempP);
            tempP.first.clear();
            tempP.second.clear();
            continue;
        }
        if(data[i]==':'){
            tempP.first=tempS;
            tempS.clear();
            continue;
        }

        tempS+=data[i];

    }
    res.push_back(tempV);
    tempV.clear();

    //Extracting Client Data

    if(data[i]=='<' && data[i+1]=='<' && data[i+2]=='?'){
        for(i=i+3;i<data.size();){

            if(data[i]=='['){
                int ind=i+1;                //vector

                while(data[ind]!=']'){

                    int ind2=ind;             //pair
                    tempP.first="";
                    tempP.second="";
                    tempS.clear();

                    if(data[ind2]=='('){
                        ind2++;

                        while(data[ind2]!=')' ){

                            if(data[ind2]==','){
                                tempP.first=tempS;
                                tempS.clear();
                            }

                            else{
                                tempS+=data[ind2];
                            }
                            ind2++;
                        }
                        tempP.second=tempS;
                        tempS.clear();
                    }
                    else{
                        throw "Wrong Format";
                    }

                    if(tempP.first.size()>0)
                        tempV.push_back(tempP);
                    ind=ind2+1;
                }
                res.push_back(tempV);
                tempV.clear();
                i=ind+1;
            }
            else{
                throw "Wrong Format";
            }
            if(data[i]=='?'){
                break;
            }
        }
//            cout<<endl;
//            for(auto x:res){
//            for(auto y:x){
//                cout<<y.first<<" : "<<y.second<<endl;
//            }
//            }
        return res;
    }
    }

    throw -1;
}

vector<vector<pair<string,string > > > commonMeth::string_to_vvss2(string data){
    vector<vector<pair<string,string > > > res;
    vector<pair<string,string > >  tempV;
    pair<string,string> tempP;
    string tempS;

    if(data[0]=='<' && data[1]=='<' && data[2]=='$'){
        for(int i=3;i<data.size();){

            if(data[i]=='['){
                int ind=i+1;                //vector
                while(data[ind]!=']'){

                    int ind2=ind;             //pair
                    tempP.first="";
                    tempP.second="";
                    ;tempS.clear();

                    if(data[ind2]=='{'){
                        ind2++;
                        while(data[ind2]!='}'){
                            if(data[ind2]==':'){
                                tempP.first=tempS;
                                tempS.clear();
                            }
                            else{
                                tempS+=data[ind2];
                            }
                            ind2++;
                        }
                        tempP.second=tempS;
                        tempS.clear();
                    }
                    else{
                        throw "Wrong format";
                    }
                    tempV.push_back(tempP);
                    ind=ind2+1;
                }
                res.push_back(tempV);
                tempV.clear();
                i=ind+1;
            }
            else{
                throw "WRONG FORMAT";
            }


            if(data[i]=='$'){
                break;
            }
        }

        return res;
    }

    throw -1;
}

string commonMeth::vvss_to_string( vector<vector<pair<string,string > > > data){
    string res;
    //Packing server Information
    res+="<<!";
    for(int i=0;i<data[0].size();i++){
        res+=data[0][i].first + ":" + data[0][i].second;
        if(i!=data[0].size()-1)
            res+=",";
    }

    //Packing Other Information
    res+="!>><<?";


    for(int i=1;i<data.size();i++){
        res+="[";
        for(auto p:data[i]){
            res+="(";
            res+=p.first;
            res+=",";
            res+=p.second;
            res+=")";
        }
        res+="]";
    }
    res+="?>>";
    return res;

}

string commonMeth::vvss_to_string2( vector<vector<pair<string,string > > > data){
    string res;

    res+="<<$";


    for(int i=0;i<data.size();i++){
        res+="[";
        for(auto p:data[i]){
            res+="{";
            res+=p.first;
            res+=":";
            res+=p.second;
            res+="}";
        }
        res+="]";
    }
    res+="$>>";
    return res;

}

