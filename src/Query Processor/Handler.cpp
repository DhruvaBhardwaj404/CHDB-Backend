#include "Handler.h"

Handler::Handler(const string &name,unsigned int m)
{
    try{
        mode=m;
        switch(m){

        case 0:chdir("./sql");break;
        case 1:chdir("./nsql");break;
        case 2:chdir("./hybrid");break;
        default:throw; //Todo add exception
        }

        fstream file("handler_info.dat",ios::in|ios::binary);

        if(file.is_open()){
            file.read((char*)this,sizeof(Handler));
            file.close();
        }

        //name.resize(MAX_COL_NAME);

        if(strcmp(name.c_str(),"N-N")!=0){

            if(col_Name[hashFun(name)]==1){
               strcpy(sel_Col_Name,name.c_str());
            }
            else{
                cout<<"[!!!] No collection with specified name exist!\n";
            }
        }
    }
    catch(...){
        cout<<"[!!!] Error while creating sql object!";
        throw "";
    }

}

Handler::Handler(const string &name,const string& table, unsigned m){
    try{
        mode=m;
        switch(m){

            case 0:chdir("./sql");break;
            case 1:chdir("./nsql");break;
            case 2:chdir("./hybrid");break;
            default:throw; //Todo add exception
        }

        fstream file("handler_info.dat",ios::in|ios::binary);
        if(file.is_open()){
            file.read((char*)this,sizeof(Handler));
            file.close();
        }
        //name.resize(MAX_COL_NAME);

        if(strcmp(name.c_str(),"N-N")!=0){

            if(col_Name[hashFun(name)]==1){
               strcpy(sel_Col_Name,name.c_str());
            }
            else{
                cout<<"[!!!] No collection with specified name exist!\n";
            }
        }
    }
    catch(...){
        cout<<"[!!!] Error while creating sql object!";
        throw "";
    }
}


Handler::~Handler()
{
try{
    strcpy(sel_Col_Name,"N-N\0");
    fstream file("handler_info.dat",ios::out|ios::binary);
    if(file.is_open()){
        file.write((char*)this,sizeof(Handler));
        file.close();
    }
}
catch(...){
    cout<<"[!!!] Error while destructing Sql object!";
}
}


void Handler::use_Handler(const vector<string> &command){
  try{
    string m=(mode==0?"sql":"nsql");
    vector<string> pcom;
    //cout<<"Selected mode=>"<<m<<" : ";
    // TODO : Add interface commands for query parser


    /*
    if(strcmp(sel_Col_Name,"N-N")!=0){
        goto_Col("N-N");
    }




    try{
        pcom=parse(command);
    }
    catch(...){
        throw;//cout<<"[!!!]Error while parsing!\n";
    }

    if(pcom.size()<1){
        throw;//cout<<"[!!!] Insufficient number of arguments!\n";
    }

    if(pcom.size()==1){

        if(pcom[0]=="display"){
            display_Collection();
        }
        else
            throw; //cout<<"[!!!] Too few arguments specified!\n";
    }

    if(pcom.size()>=2){

        if(pcom[0]=="use"){
            select_Collection(pcom);
        }

        else if(pcom[0]=="create"){
            create_Collection(pcom);
        }

        else if(pcom[0]=="delete"){
            delete_Collection(pcom);
        }

        else
         throw; //TODO add handler exception
    }

    */
  }
  catch(...){
    cout<<"[!!!] Error in use handler\n";
   }
}



void  Handler::select_Collection(const vector<string> &pcom){
try{
    if(col_Name[hashFun(pcom[1])]==1){
        if(pcom.size()==3){
            strcpy(sel_Col_Name,pcom[1].c_str());
            goto_Col(pcom[2]);
        }

        else if(pcom.size()==2){
            strcpy(sel_Col_Name,pcom[1].c_str());
            goto_Col("N-N");
        }
    }
    else{
        throw;//cout<<"[!!!]No collection with the specified name exist!\n";
    }
}catch(...){
    cout<<"[!!!] Error in select_Collections!\n";
}
}


void  Handler::create_Collection(const vector<string> &pcom){

    if(col_Name[hashFun(pcom[1])]==1){
        cout<<"[!!!] Collection with given name exist!\n";
        return ;
    }
    else{
        col_Name[hashFun(pcom[1])]=1;
    }

    try{
        string command="mkdir "+pcom[1];
        system(command.c_str());
        strcpy(sel_Col_Name,pcom[1].c_str());
        goto_Col("New");
    }
    catch(...){
        cout<<"Error while creating the collection\n";
    }
}


void  Handler::delete_Collection(const vector<string> &pcom){
;
}

void  Handler::display_Collection(){
;
}

void Handler::goto_Col(string tab){
try{
    if(strcmp(sel_Col_Name,"N-N")!=0){
        chdir(("./"+string(sel_Col_Name)).c_str());

        if(strcmp(tab.c_str(),"New")==0){
            try{
                col=new Col_Handler(sel_Col_Name,mode);
            }
            catch(...){
                string command="rm -r "+tab;
                chdir("../");
                system(command.c_str());
                return;
            }
        }

        else if(strcmp(tab.c_str(),"N-N")==0)
            col=new Col_Handler("N-N");

        else
            col=new Col_Handler(tab);

        //return col;
        //TODO: Change method return to Collection type
        //strcpy(sel_Col_Name,"N-N\0");
        //chdir("../");

    }

    else{
        cout<<"[!!!]No collection selected!\n";
    }
}
catch(...){
    cout<<"[!!!]Error in goto_Col!\n";
}
}




