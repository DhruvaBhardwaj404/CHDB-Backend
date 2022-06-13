#include<gtest/gtest.h>
#include"Master_FHANDLER.h"

using namespace std;

class Master_FTEST: public ::testing::Test{
    protected:
    Master_FTEST():username("testUser"){}
    void SetUp() override {
        handler= new Master_FHANDLER(username);
    }
    void TearDown() override {
        delete handler;
    }
    string username;
    Master_FHANDLER *handler;
};

TEST_F(Master_FTEST,test1){
    vector<pair<string,string> > cmd1={{"MOD","ADM"},{"CMD","QUE"},{"CREA","TAB1"},{"RATT","<<$[{1:attr1}{2:attr2}]$>>"},{"RKEY","<<$[{1:attr1}]$>>"},{"NRQ","1234"},{"USR","test1"}};
    auto res=handler->query_Table(cmd1,0);
    VVPSS Eres1={{{"RES","CREATED"}}};
    EXPECT_EQ(res,Eres1);

    EXPECT_NO_FATAL_FAILURE(handler->set_Table_Active("TAB1"));

    cmd1={{"MOD","ADM"},{"CMD","QUE"},{"INSE","TAB1"},{"DATA","<<$[{attr1:data1}{attr2:data2}]$>>"},{"NRQ","1234"},{"USR","test1"}};
    auto res3= handler->query_Table(cmd1,0);
    VVPSS Eres3={{{"RES","Values Inserted"}}};
    EXPECT_EQ(res3,Eres3);
}

