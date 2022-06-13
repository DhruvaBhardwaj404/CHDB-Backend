#include<gtest/gtest.h>
#include"commonMeth.h"

using namespace commonMeth;

TEST(string_to_vvss_test,handles_conversion){
    string test="<<!REQ:1234,IP:127.0.0.1!>><<??>>"
    EXPECT_EQ(string_to_vvss())
}




