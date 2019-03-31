#include "gmock/gmock.h"
#include "../src/Core.cpp"
#include <string>

using namespace std;

int main(int argc, char** argv){
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

// Test Failed
/*
TEST(GenChainTest, case1_NullTest){
    vector<string> words;
    vector<string> results;
    int len = Core::gen_chain(words, words.size(), results);
    ASSERT_EQ(len, 0);
    ASSERT_TRUE(words.empty());
    ASSERT_TRUE(results.empty());
}
*/

Test(GenChainTest, case2){
    
}

