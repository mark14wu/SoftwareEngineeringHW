#include "gmock/gmock.h"
#include "../src/Core.cpp"
#include <string>
#include <vector>
#include <sstream>

extern int main(int, char **);

using namespace std;

TEST(gen_chain_test, NullTest){
    vector<string> words;
    vector<string> results;
    int len = Core::gen_chain(words, results);
    ASSERT_EQ(len, 0);
    ASSERT_TRUE(words.empty());
    ASSERT_TRUE(results.empty());
}


TEST(gen_chain_test, LoopTest){
    vector<string> input = {"aab", "bbc", "ccd", "dda"};
    vector<string> results;
    vector<string> expected = {"aab", "bbc", "ccd", "dda"};
    int len = Core::gen_chain(input, results);
    ASSERT_EQ(len, 4);
    ASSERT_EQ(results, expected);
}
TEST(gen_chain_test, SingleCharLoop){
    vector<string> input = {"a", "aa", "aaa", "aaaa"};
    vector<string> results;
    vector<string> expected = { "aaaa", "aaa", "aa", "a" };
    // 算法中有一个步骤是将开头和结尾相同的单词列按照长度倒序排列，因此结果如上所示
    int len = Core::gen_chain(input, results);
    ASSERT_EQ(len, 4);
    ASSERT_EQ(results, expected);
}
TEST(gen_chain_test, SingleCharBigLoop){
    vector<string> input = {"a","aaa","aa","aaaaaaaaaaaa","aaaaaaaaa",
    "aaaaaaaaaaaaaaaaaaaaaaa","aaaaa","aaaaaaaa", 
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaaaaaaaaa","aaaaaaaaaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","aaaaaaa","aaaaaaaa",
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaaaaaaaaaaa"};
    vector<string> results;
    vector<string> expected = { "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaa",
    "aaaaaaaaaaaa", "aaaaaaaaa", "aaaaaaaa", "aaaaaaaa", "aaaaaaa", "aaaaa", "aaa", "aa", "a" };
    int len = Core::gen_chain(input, results);
    ASSERT_EQ(len, 19);
    ASSERT_EQ(results, expected);
}

TEST(gen_chain_char_test, NullTest){
    vector<string> words;
    vector<string> results;
    int len = Core::gen_chain_char(words, results);
    ASSERT_EQ(len, 0);
    ASSERT_TRUE(words.empty());
    ASSERT_TRUE(results.empty());
}

TEST(gen_chain_char_test, MostCharCount){
    vector<string> input = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", 
    "zbakjsdoifajsodjifasjofjksfoasfjoaisdfjaiosdjfosdfjodsajfoisadjfodsfosdjfosdfodsafiodsfioadsjfodsajfiodsj",
    "jlqkjweojojosfjoasjkfojsfosajfl;sjlfsjflsajflksajflsjflasjflasjflsadjflsdjfladsjfkdls"};
    // 测试其是否计算了字符数而不是单词数
    vector<string> results;
    vector<string> expected = 
    { "zbakjsdoifajsodjifasjofjksfoasfjoaisdfjaiosdjfosdfjodsajfoisadjfodsfosdjfosdfodsafiodsfioadsjfodsajfiodsj", "jlqkjweojojosfjoasjkfojsfosajfl;sjlfsjflsajflksajflsjflasjflasjflsadjflsdjfladsjfkdls" };
    int len = Core::gen_chain_char(input, results);
    ASSERT_EQ(len, 190);
    ASSERT_EQ(results, expected);
}

TEST(gen_chain_word_test, NullTest){
    vector<string> input;
    vector<string> results;
    int len = Core::gen_chain_word(input, results, '\0', '\0');
    ASSERT_TRUE(input.empty());
    ASSERT_TRUE(results.empty());
}

TEST(gen_chain_word_test, GivenNullChar){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef"};
    vector<string> results;
    vector<string> expected = { "da", "ab", "bc", "cd", "de", "ef" };
    int len = Core::gen_chain_word(input, results, '\0', '\0');
    ASSERT_EQ(len, 6);
    ASSERT_EQ(expected, results);
}

TEST(gen_chain_word_test, GivenHeadChar){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef", "fa"};
    vector<string> results;
    vector<string> expected = { "ef", "fa", "ab", "bc", "cd", "da" };
    int len = Core::gen_chain_word(input, results, 'e', '\0');
    ASSERT_EQ(len, 6);
    ASSERT_EQ(expected, results);
}

TEST(gen_chain_word_test, GivenTailChar){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef", "fa"};
    vector<string> results;
    vector<string> expected = { "da", "ab", "bc", "cd", "de", "ef" };
    int len = Core::gen_chain_word(input, results, '\0', 'f');
    ASSERT_EQ(len, 7);
    ASSERT_EQ(expected, results);
}

TEST(gen_chain_word_test, GivenBothChar){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef"};
    vector<string> results;
    vector<string> expected = { "ab", "bc", "cd", "da" };
    int len = Core::gen_chain_word(input, results, 'a', 'a');
    ASSERT_EQ(len, 5);
    ASSERT_EQ(expected, results);
}

TEST(gen_chain_n_word_test, NullTest){
    vector<string> input;
    ostringstream test_ostream;
    Core::gen_chain_n_word(input, 0, test_ostream);

    string result = test_ostream.str();
    string expected = "";
    ASSERT_EQ(result, expected);

}

TEST(gen_chain_n_word_test, Test1){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef", "fa"};
    ostringstream test_ostream;
    Core::gen_chain_n_word(input, 5, test_ostream);

    string result = test_ostream.str();
    string expected = string("ab bc cd de ef \nbc cd de ef fa \n") + 
    string("cd de ef fa ab \nda ab bc cd de \nde ef fa ab bc \n") +
    string("ef fa ab bc cd \nfa ab bc cd da \nfa ab bc cd de \nab bc cd de ef \n");
    ASSERT_EQ(result, expected);
}

TEST(gen_chain_n_word_test, Test2){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef", "fa"};
    ostringstream test_ostream;
    Core::gen_chain_n_word(input, 2, test_ostream);

    string result = test_ostream.str();
    string expected = "ab bc \nbc cd \ncd da \ncd de \nda ab \nde ef \nef fa \nfa ab \nab bc \n";
    ASSERT_EQ(result, expected);

}

TEST(gen_chain_n_word_test, Test3){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef", "fa"};
    ostringstream test_ostream;
    Core::gen_chain_n_word(input, 10, test_ostream);

    string result = test_ostream.str();
    string expected = "";
    ASSERT_EQ(result, expected);
}