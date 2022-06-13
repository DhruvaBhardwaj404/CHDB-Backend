#include<gtest/gtest.h>
#include"Hybrid_TabHandler.h"

using namespace std;



class Hybrid_TabTEST: public ::testing::Test{
    protected:
    Hybrid_TabTEST():name("testTab")
    {

    }
    void SetUp()override{
        tab=new Hybrid_TabHandler(name);
    }
    void TearDown() override{

    }
    string name;
    Hybrid_TabHandler *tab;
};


TEST_F(Hybrid_TabTEST,test_1){
    vector<pair<string,string> > cmd={{"1","Attr1"},{"2","attr2"},{"3","attr3"}};
    tab->insert_Rel_Attr(cmd);
    auto data1= tab->get_Rel_Attr();
    EXPECT_EQ(data1,cmd);

    vector<vector<pair<string,string> > > cmd2={
                                    {{"Attr1","data1"},{"attr2","data2"},{"attr3","data3"}}
                                    };

    EXPECT_ANY_THROW(tab->insert_Data(cmd2););
    vector<pair<string,string> > key={{"1","Attr1"}};
    EXPECT_NO_THROW(tab->set_Key(key));
    auto skey= tab->get_Key();
    vector<pair<string,string > > data2={{"Attr1","0"}};
    EXPECT_EQ(skey,data2);

    vector<vector<pair<string,string> > > cmd3={
                                    {{"Attr1","data1"},{"attr2","data2"},{"attr3","data3"}}
                                    };
    tab->insert_Data(cmd3);
    auto data3= tab->fetch_Data({});
    EXPECT_EQ(data3,cmd3);
    EXPECT_ANY_THROW(tab->insert_Data(cmd3));

    vector<vector<pair<string,string> > > cmd4={
                                    {{"Attr1","data4"},{"attr2","data2"},{"attr3","data3"},{"NONR","data4"}}
                                    };

    tab->insert_Data(cmd4);
    cmd4.push_back(cmd3[0]);
    auto data4= tab->fetch_Data({});
    EXPECT_EQ(data4,cmd4);

}


TEST_F(Hybrid_TabTEST,TEST_2){

}

//TEST_F(Hybrid_TabTEST,SET_KEY){
//
//}
//
//
//
//TEST_F(Hybrid_TabTEST,INSERT_DATA_WITHOUT_KEY){
//
//}
//
//TEST_F(Hybrid_TabTEST,MULITPLE_INSERT_DATA){
//
//}
//
//TEST_F(Hybrid_TabTEST,INSERT_DATA_WITH_NONREL){
//
//}




