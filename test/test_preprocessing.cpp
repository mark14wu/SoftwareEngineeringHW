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
        vocabulary = PreProcessing::process(null_stream);
        FAIL(); // 不抛出异常，失败
    }
    catch(invalid_argument const& err){
        EXPECT_EQ(err.what(), string("no word found in text!"));
    }
    catch(...){
        FAIL(); // 抛出其他异常，失败
    }
}

TEST(preprocessing_test, RemoveDuplicate){
    istringstream test_stream("i have a pen, i have an apple。ah, apple pen.");
    vector<string> vocabulary;
    vocabulary = PreProcessing::process(test_stream);
    
    vector<string> expected = { "have", "pen", "an", "apple", "ah" };

    ASSERT_EQ(vocabulary, expected);
}


TEST(preprocessing_test, CaseInsensitive){
    istringstream test_stream("i have a PeN, i hAve aN aPplE。ah, appLE pen.");
    vector<string> vocabulary;
    vocabulary = PreProcessing::process(test_stream);
    
    vector<string> expected = { "have", "pen", "an", "apple", "ah" };

    ASSERT_EQ(vocabulary, expected);
}

TEST(preprocessing_test, MultipleWordInOneWordNode){
    istringstream test_stream("i have a PeN, i hAve aN aPplE and an appppppple and also an appple。ah, appLE pen.");
    vector<string> vocabulary;
    vocabulary = PreProcessing::process(test_stream);
    
    vector<string> expected = { "have", "pen", "an", "apple", "and", "appppppple", "also", "appple", "ah" };

    ASSERT_EQ(vocabulary, expected);
}