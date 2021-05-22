#include "NSQL_TabHandler.h"


NSQL_TabHandler::NSQL_TabHandler()
{
    fstream tfile("tab_info.dat",ios::in|ios::out),
            afile("attr_info.dat",ios::in|ios::out),
            kfile("attr_keys.dat",ios::in|ios::out);


    if(tfile.is_open()){
        tfile.read((char*)this,sizeof(NSQL_TabHandler));
        tfile.close();
    }

    Table=new tableInfoNSQL();
    Table->make_Attr_List(afile,kfile,NA);
    afile.close();
    kfile.close();
   // Table->tableData.clear();
}


NSQL_TabHandler::NSQL_TabHandler(string name){

    name.resize(MAX_SIZE_NAME);
    strcpy(Name,name.c_str());
    fstream tfile("tab_info.dat",ios::out|ios::binary),
            afile("attr_info.dat",ios::out| ios::binary),
            kfile("attr_keys.dat",ios::out| ios::binary);

    if(tfile.is_open()){
        tfile.write((char*)this,sizeof(NSQL_TabHandler));
        tfile.close();
    }
        Table=new tableInfoNSQL();

}


NSQL_TabHandler::~NSQL_TabHandler(){
    fstream file("tab_info.dat",ios::out|ios::binary);

    if(Table->new_Attr.size()>0){
        fstream  afile("attr_info.dat",ios::out| ios::trunc),
                kfile("attr_keys.dat",ios::out| ios::trunc);
        kfile.seekp(0);
        for(auto x:Table->keys){
            kfile.write((char*)&x,SIZE_KEY);
        }
        afile.seekp(0);
        char type,name[20];
        for(auto x:Table->attr_List){
            x.first.resize(20);
            cout<<"type "<<x.second<<"\n";
            type=char(x.second);
            strcpy(name,x.first.c_str());
            afile.write((char*)&name,SIZE_ATTR_NAME);
            afile.write((char*)&type,SIZE_ATTR_INFO);
        }

        afile.close();
        kfile.close();

    }
    delete Table;
    if(file.is_open()){
        file.write((char*)this,sizeof(NSQL_TabHandler));
        file.close();
    }

}


void NSQL_TabHandler::use_tabHandler(){
 string command;

 while(true){
    vector<string> pcom;
    cout<<"In "<<Name<<"=> ";
    getline(cin,command);
    pcom=parse(command);

    if(pcom.size()>=1){
        if(pcom[0]=="use"){
            //select_Column("");
        }

        else if(pcom[0]=="create"){
            //create_Column(pcom);
        }
        else if(pcom[0]=="insert"){
            insert_Data(command);
        }

        else if(pcom[0]=="display"){
            display_Table();
        }

        else if(pcom[0]=="delete"){
            //delete_Table();
        }
        else if(pcom[0]=="info"){
            col_Info();

            Table->print_attr_list();
        }

        else if(pcom[0]=="found"){

        }

        else if(pcom.size()==2)
            if(pcom[0]=="switch" && pcom[1]=="database")
                break;
        else
            cout<<endl<<"[!!!]Command not recognised!\n"<<endl;
    }
    else
        cout<<endl<<"[!!!]Command not recognised!\n"<<endl;


 }


}

void NSQL_TabHandler::col_Info(){
    cout<<endl<<"Name of Table :"<<Name
              <<"\nNumber of record "<<NR
              <<"\nNumber of records small "<<NRS
              <<"\nNumber of records big "<<NRB
              <<"\nNumber attributes "<<NA
              <<"\nNumber of first chunks "<<NFC
              <<"\nNumber of small chunks "<<NSC
              <<"\nNumber of big chunks "<<NBC<<endl;
}


void NSQL_TabHandler::insert_Data(const string &pcom){
   try{

    vector<vector<pair<string,string> > > data=parseInsert(pcom);
    validate_Data(data);

    int s_rec=0;
    NSQL_Cinfo info;
    info.r_rec=data.size();
    int tempNR=NR,tempNFC=NFC;
    string fname;
    fstream file;


    while(info.r_rec>0){
        get_File_pos(&info,tempNR,tempNFC,SIZE_FCHUNCKS);

        fname="fc-"+to_string(NFC)+".dat";
        file.open(fname,ios::in | ios::out);
        s_rec=0;

        if(!file.is_open()){
            file.open(fname,ios::out);
        }

        write_To_File(data,file,&info);


       info.w_rec=info.e;
       info.r_rec=data.size() - info.w_rec;
       NR+=info.w_rec;

    }
    file.close();

    }
    catch(string mess){
        cout<<mess;
    }
}


void NSQL_TabHandler::select_Column(string name){
;
}

void NSQL_TabHandler::create_Column(vector<string> pcom){
;
}

void NSQL_TabHandler::find_in_Table(){
;
}

void NSQL_TabHandler::display_Table(){
;

}

void NSQL_TabHandler::delete_Table(){
;
}


void NSQL_TabHandler::load_Tab_Data(){
   ;
}

//
//template<typename T>
//void NSQL_TabHandler::read_From_File(fstream &f,unsigned int file_pos,unsigned int page,unsigned int col){
//
//}



void NSQL_TabHandler::validate_Data(vector<vector<pair<string,string> > > &d){
try{
    int key,temp;
    vector<pair<pair<string,int>,int> > new_Attr;
    //cout<<"\n in validate data\n";

    for(auto &x:d){
        for(auto &y:x){
            //cout<<y.first<<" "<<y.second<<endl;
            temp=hashFun(y.first);
            key=Table->search_Key(temp);

            if(key==-1){
                int type=type_Eval(y.second);
                new_Attr.push_back({{y.first,type},temp});
                Table->new_Attr.push_back({y.first,type});
                Table->new_Keys.push_back(temp);
                y.first="a"+to_string(new_Attr.size()-1);
                type_Checker(y.second,{type,0},1);
            }

            else{
                y.first=to_string(key);
                type_Checker(y.second,{Table->attr_List[key].second,0},1);
            }

        }
    }
    attr_Updater(new_Attr);

 }
 catch(string mess){
    cout<<mess<<endl;
    throw "[!!!]Error in validate Data!";
 }
}



bool NSQL_TabHandler::write_To_File(const vector<vector<pair<string,string> > > &data,fstream &f,NSQL_Cinfo *info){

    f.seekp(info->file_pos);
    headChunk head;
    nextChunk tail;
    string fdata,temp,part;

    while( (info->s)  <  (info->e)  ){


        fdata=write_Type_Con(data[info->s]);

        temp=fdata;
        temp.resize(SIZE_FCHUNCKS);
        f.write((char*)&temp,SIZE_FCHUNCKS);

        if(fdata.size()<SIZE_FCHUNCKS){
            tail.ctype=0;
            tail.cnum=0;
            tail.pos=0;
            f.write((char*)&tail,sizeof(tail));
        }

        else{

            NSQL_Cinfo cinfo;
            cinfo.start=SIZE_FCHUNCKS;
            int chunkNum=0;
            bool flag=0;

            int cond=fdata.size()-cinfo.start;

            while(cond>0){

                chunkNum++;

                if(cond<SIZE_SMALL_CHUNKS || cond/2<SIZE_SMALL_CHUNKS){
                    cinfo.mode=1;
                    write_To_Chunks(fdata,&cinfo,SIZE_SMALL_CHUNKS,chunkNum,1);
                }
                else{
                    cinfo.mode=2;
                    write_To_Chunks(fdata,&cinfo,SIZE_BIG_CHUNKS,chunkNum,2);
                }

                if(flag==0){
                    if(cinfo.mode==1){
                        tail.ctype=1;
                        tail.cnum=NBC;
                        tail.pos=int((cinfo.file_pos)/(sizeof(head)+sizeof(tail)+SIZE_SMALL_CHUNKS));
                    }
                    else{
                        tail.ctype=2;
                        tail.cnum=NSC;
                        tail.pos=int((cinfo.file_pos)/(sizeof(head)+sizeof(tail)+SIZE_BIG_CHUNKS));
                    }
                    f.write((char*)&tail,sizeof(tail));
                    flag=1;
                }
                cond=fdata.size()-cinfo.start;
            }
        }

        info->s++;
    }
}


void NSQL_TabHandler::write_To_Chunks(string &temp, NSQL_Cinfo *info,int chunk_size,int chunkNum,int m){
        string part,fname;
        headChunk head;
        nextChunk tail;

        if(temp.begin()+(info->start)<temp.end())
            part=string(temp.begin()+info->start,temp.begin()+info->start+chunk_size);

        else{
            part=string(temp.begin()+info->start,temp.end());
            part.resize(chunk_size);
        }


        info->s+=chunk_size;

        if(info->mode==1){
            int tempNRS=NRS,tempNSC=NSC;
            NSQL_Cinfo temp=*info;
            get_File_pos(&temp,tempNRS,tempNSC,SIZE_SMALL_CHUNKS);
            NRS=tempNRS;
            NSC=tempNSC;
            *info=temp;
        }

        else if(info->mode==2){
            int tempNRB=NRB;
            int tempNSB=NBC;
            NSQL_Cinfo temp=*info;
            get_File_pos(&temp,tempNRB,tempNSB,SIZE_BIG_CHUNKS);
            NRB=tempNRB;
            NBC=tempNSB;
            *info=temp;
        }

        if(info->last!=-1){
            if(info->lmode==1){
                info->sfile->seekp(info->lfile_pos);
                tail.ctype=1;
                tail.cnum=NSC;
                tail.pos=int((info->file_pos)/(sizeof(head)+sizeof(tail)+chunk_size));
                info->sfile->write((char*)&tail,sizeof(tail));
                info->sfile->close();
                delete info->sfile;
            }
            else if(info->lmode==2){
                info->sfile->seekp(info->lfile_pos);
                tail.ctype=2;
                tail.cnum=NBC;
                tail.pos=int((info->file_pos)/(sizeof(head)+sizeof(tail)+SIZE_BIG_CHUNKS));
                info->bfile->write((char*)&tail,sizeof(tail));
                info->bfile->close();
                delete info->bfile;
            }
        }

        if(info->mode==1){

            fname="sc-"+to_string(NSC)+".dat";
            info->sfile=new fstream(fname,ios::in|ios::out);

            if(!info->sfile->is_open()){
                info->sfile->open(fname,ios::out);
            }

            info->sfile->seekp(info->file_pos);
            cout<<info->sfile->tellp()<<" \n";

            head.chunkNum=chunkNum;
            info->sfile->sync();
            info->sfile->write((char*)&head,sizeof(head));
            info->sfile->write((char*)part.c_str(),chunk_size);
            NRS++;
            info->lmode=1;

            info->start+=chunk_size;

            if(info->start>=temp.size()){
                tail.ctype=0;
                tail.cnum=0;
                tail.pos=0;
                info->sfile->write((char*)&tail,sizeof(tail));
            }
            else{
                 info->lfile_pos=info->sfile->tellp();
                 info->last=1;
            }
        }

        else if(info->mode==2){

            fname="bc-"+to_string(NBC)+".dat";
            info->bfile=new fstream(fname,ios::in|ios::out);

            if(!info->bfile->is_open()){
                info->bfile->open(fname,ios::out);
            }

            info->bfile->seekp(info->file_pos);
            cout<<"size of part "<<part.size()<<endl;
            head.chunkNum=chunkNum;
            info->bfile->write((char*)&head,sizeof(head));
            info->bfile->write((char*)part.c_str(),chunk_size);
            NRB++;
            info->lmode=2;

            info->start+=chunk_size;

            if(info->start>=temp.size()){
                tail.ctype=0;
                tail.cnum=0;
                tail.pos=0;
                info->bfile->write((char*)&tail,sizeof(tail));
            }

            else{
                info->lfile_pos=info->bfile->tellp();
                info->last=1;
            }
        }
}


void NSQL_TabHandler::get_File_pos(NSQL_Cinfo *info,int &numRec,int &numChunks,int chunkSize){

    info->s=info->w_rec==0?0:info->w_rec+1;

       if(numRec%MAX_CHUNCKS==0 || numRec==0){
         numChunks++;

         if(info->r_rec<=MAX_CHUNCKS)
            info->e=info->s+info->r_rec;

         else
            info->e=info->s+MAX_CHUNCKS;

       }

       else
        if( ( (numRec%MAX_CHUNCKS) + info->r_rec ) <= MAX_CHUNCKS )
            info->e=info->s+info->r_rec;
        else
            info->e = info->s + ( MAX_CHUNCKS-( numRec%MAX_CHUNCKS ) );



       if(numRec%MAX_CHUNCKS!=0)
            info->file_pos=chunkSize*(numRec%MAX_CHUNCKS);

        else
            info->file_pos=0;

    Table->print_info(info);
}


string NSQL_TabHandler::write_Type_Con(const vector<pair<string,string> > &values){
    string data,attr,value,temp;
    int type,key,index;
    for(auto x:values){
        attr=x.first;
        value=x.second;
        if(x.first[0]!='a'){
            key=stoi(x.first);
            type=Table->attr_List[key].second;
            key=Table->keys[key];
            data+=to_string(key)+":"+con_To_String(value,type);
        }
        else{
            temp=string(attr.begin()+1,attr.end());
            key=Table->new_Keys[stoi(temp)];
            index=Table->new_Keys[key];
            type=Table->new_Attr[index].second;
            data+=to_string(key)+":"+con_To_String(value,type);
        }
    }
    return data;
}


string NSQL_TabHandler::con_To_String(const string &dat,int type){
    switch(type){
        case 1 :{
                    long long t1= stoll(dat);
                    char t2[8],t3;
                    for(int i=0;i<8;i++){
                        t3=*(&t1+i);
                        t2[i]=t3;
                    }
                    return t2;
                }
                break;
        case 5 :
                return dat+"\0";
    }
}


//bool NSQL_TabHandler::write_To_File(vector<string> data,fstream &f,unsigned int file_pos,unsigned int s,unsigned int e,unsigned int size){
//
//}


//
//void NSQL_TabHandler::read_From_File(fstream &f,unsigned int file_pos,unsigned int page,unsigned int col,unsigned int size){
//;
//}

void NSQL_TabHandler::attr_Updater(vector<pair<pair<string,int>,int> > &attr){
    //cout<<"here in attr_Updater\n";
    sort(attr.begin(),attr.end(),[](pair<pair<string,int>,int> a,pair<pair<string,int>,int>  b)
                                        { if(a.second<b.second)
                                                return true;
                                          return false;
                                        });

    for(auto x:attr){
        Table->keys.push_back(x.second);
        Table->attr_List.push_back(x.first);
    }
    NA=Table->keys.size();
    Table->sort_key(attr.size());
}




//                if(temp.begin()+start<temp.end())
//                    part=string(temp.begin()+start,SIZE_SMALL_CHUNKS);
//                else{
//                    part=string(temp.begin()+start,temp.end());
//                    part.resize(SIZE_SMALL_CHUNKS);
//                }
//
//                s+=SIZE_SMALL_CHUNKS;
//                get_File_pos(file_pos,s,r,r_chunks,w_chunks,NRS,NSC,SSC);
//
//                if(last!=-1){
//                    if(mode==1){
//                        sfile.seekp(lfile_pos);
//                        tail.ctype=1;
//                        tail.cnum=NSC;
//                        tail.pos=int((file_pos)/(sizeof(head)+sizeof(tail)+SIZE_SMALL_CHUNKS));
//                        sfile.write((char*)&tail,sizeof(tail));
//                    }
//                    else if(mode==2){
//                        sfile.seekp(lfile_pos);
//                        tail.ctype=2;
//                        tail.cnum=NBC;
//                        tail.pos=int((file_pos)/(sizeof(head)+sizeof(tail)+SIZE_BIG_CHUNKS));
//                        bfile.write((char*)&tail,sizeof(tail));
//                    }
//                }
//
//                fname="sc-"+to_string(NSC)+".dat";
//                sfile.open(fname,ios::in|ios::out|ios::binary);
//
//                if(!sfile.is_open){
//                    sfile.open(fname,ios::out|ios::binary);
//                }
//
//                sfile.seekp(file_pos);
//                head.chunkNum=chunkNum;
//                sfile.write((char*)&head,sizeof(head));
//                sfile.write((char*)&part,SIZE_SMALL_CHUNKS);
//                mode=1;
//                if(start+SIZE_SMALL_CHUNKS>=temp.size()){
//                    tail.ctype=0;
//                    tail.cnum=0;
//                    tail.pos=0;
//                    sfile.write((char*)&tail,sizeof(tail));
//                }
//                else{
//                    lfile_pos=sfile.tellp();
//                    last=1
//                    mode=1;
//                }
