#include<gtest/gtest.h>
#include"commonMeth.h"

using namespace commonMeth;

class commonMethTEST: public ::testing::Test{
    protected:
        void SetUp() override{
            str ="<<!REQ:1234,IP:127.0.0.1!>><<?[(RTY,EXI)(CMD,ADM)(PAS,1234)(CID,1234)][(MOD,CLI)(CMD,NEW)]?>>";
            str2="<<!REQ:1234,IP:127.0.0.1!>><<?[(RTY,EXI)(CMD,ADM)(PAS,1234)(CID,1234)][(MOD,CLI)(CMD,NEW)(QUE,<<$[{RTY:EXI}{CMD:ADM}{PAS:1234}{CID:1234}]$>>)]?>>";
            str3="<<$[{RTY:EXI}{CMD:ADM}{PAS:1234}{CID:1234}]$>>";
            vvss={  {{"REQ","1234"} , {"IP","127.0.0.1"}},
                    {{"RTY","EXI"} , {"CMD","ADM"} , {"PAS","1234"} , {"CID","1234"} },
                    {{"MOD","CLI"} , {"CMD","NEW"} }
                };
            vvss2={  {{"REQ","1234"} , {"IP","127.0.0.1"}},
                    {{"RTY","EXI"} , {"CMD","ADM"} , {"PAS","1234"} , {"CID","1234"} },
                    {{"MOD","CLI"} , {"CMD","NEW"}, {"QUE","<<$[{RTY:EXI}{CMD:ADM}{PAS:1234}{CID:1234}]$>>"} }
                };
            vvss3={ {{"RTY","EXI"} , {"CMD","ADM"} , {"PAS","1234"} , {"CID","1234"}}
                  };
        }

     string str,str2,str3;
     vector<vector<pair<string,string > > > vvss,vvss2,vvss3;
};


TEST_F(commonMethTEST,handles_string){
    auto toD= string_to_vvss(str);
    EXPECT_EQ(toD,vvss)<< "string to vvss normal message";
    toD=string_to_vvss(str2);
    EXPECT_EQ(toD,vvss2)<<"string to vvss embedded query";
}


TEST_F(commonMethTEST,handles_vvss){
    auto toS= vvss_to_string(vvss);
    EXPECT_EQ(toS,str)<<"vvss to string normal string";
    toS= vvss_to_string(vvss2);
    EXPECT_EQ(toS,str2)<<"vvss to string embedded query";
}

TEST_F(commonMethTEST,handles_vvss2){
    auto toS= vvss_to_string2(vvss3);
    EXPECT_EQ(toS,str3)<<"vvss to string embedded query";
}


TEST_F(commonMethTEST,handles_string2){
    auto toD= string_to_vvss2(str3);
    EXPECT_EQ(toD,vvss3)<< "string to vvss normal message";
    string str4="<<$[{1:attr1}{2:attr2}]$>>";
    toD= string_to_vvss2(str4);
    VVPSS res={{{"1","attr1"},{"2","attr2"}}};
    EXPECT_EQ(toD,res);

}
