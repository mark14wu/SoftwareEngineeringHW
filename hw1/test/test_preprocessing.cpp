#include "gmock/gmock.h"
#include "../src/PreProcessing.cpp"
#include <sstream>
#include <vector>

using namespace std;

extern int main(int, char**);

TEST(preprocessing_test, NullTest){
    istringstream null_stream;
    vector<string> vocabulary;
    try{
        PreProcessing::process(null_stream, vocabulary);
        FAIL();
    }
    catch(invalid_argument const& err){
        EXPECT_EQ(err.what(), string("no word found in text!"));
    }
    catch(...){
        FAIL();
    }
}

TEST(preprocessing_test, RemoveDuplicate){
    istringstream test_stream("i have a pen, i have an apple。ah, apple pen.");
    vector<string> vocabulary;
    PreProcessing::process(test_stream, vocabulary);
    
    vector<string> expected = { "have", "pen", "an", "apple", "ah" };

    ASSERT_EQ(vocabulary, expected);
}


TEST(preprocessing_test, CaseInsensitive){
    istringstream test_stream("i have a PeN, i hAve aN aPplE。ah, appLE pen.");
    vector<string> vocabulary;
    PreProcessing::process(test_stream, vocabulary);
    
    vector<string> expected = { "have", "pen", "an", "apple", "ah" };

    ASSERT_EQ(vocabulary, expected);
}