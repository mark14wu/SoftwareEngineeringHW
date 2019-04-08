#include "gmock/gmock.h"

// 为了方便测试私有成员
#define private public
#include "../src/Core.cpp"

#include <string>
#include <vector>
#include <sstream>
#include <tuple>

extern int main(int, char **);

using namespace std;


TEST(exception_test, check_words){
    vector<string> words = {"apple", "26"};
    vector<string> result;
    try{
        Core::check_words(words);
        FAIL();
    }
    catch(out_of_range const& err){
        ASSERT_EQ(err.what(), string("char '2' out of range in word \"26\""));
    }
    catch(...){
        FAIL();
    }
}

TEST(convert_char_test, CaseInsensitive){
    ASSERT_EQ(Core::convert_char('a'), 1);
    ASSERT_EQ(Core::convert_char('A'), 1);
}

TEST(exception_test, convert_char){
    try{
        Core::convert_char(23);
        FAIL();
    }
    catch(out_of_range const& err){
        ASSERT_EQ(err.what(), string("char " + string(1, 23) + " is not in the range(a-z, A-Z)!"));
    }
    catch(...){
        FAIL();
    }
}

TEST(gen_chain_test, NullTest){
    vector<string> words;
    vector<string> result;
    int len;
    tie(len, result) = Core::gen_chain(words);
    ASSERT_EQ(len, 0);
    ASSERT_TRUE(words.empty());
    ASSERT_TRUE(result.empty());
}

TEST(gen_chain_test, LoopTest){
    vector<string> input = {"aab", "bbc", "ccd", "dda"};
    vector<string> results;
    vector<string> expected = {"aab", "bbc", "ccd", "dda"};
    int len;
    tie(len ,results)= Core::gen_chain(input);
    ASSERT_EQ(len, 4);
    ASSERT_EQ(results, expected);
}

TEST(gen_chain_test, SingleCharLoop){
    vector<string> input = {"a", "aa", "aaa", "aaaa"};
    vector<string> results;
    vector<string> expected = { "aaaa", "aaa", "aa", "a" };
    // 算法中有一个步骤是将开头和结尾相同的单词列按照长度倒序排列，因此结果如上所示
    int len;
    tie(len, results) = Core::gen_chain(input);
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
    int len;
    tie(len, results) = Core::gen_chain(input);
    ASSERT_EQ(len, 19);
    ASSERT_EQ(results, expected);
}

TEST(gen_chain_char_test, NullTest){
    vector<string> words;
    vector<string> results;
    int len;
    tie(len, results) = Core::gen_chain_char(words, '\0', '\0');
    ASSERT_EQ(len, 0);
    ASSERT_TRUE(words.empty());
    ASSERT_TRUE(results.empty());
}

TEST(gen_chain_char_test, MostCharCount){
    vector<string> input = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", 
    "zbakjsdoifajsodjifasjofjksfoasfjoaisdfjaiosdjfosdfjodsajfoisadjfodsfosdjfosdfodsafiodsfioadsjfodsajfiodsj",
    "jlqkjweojojosfjoasjkfojsfosajflsjlfsjflsajflksajflsjflasjflasjflsadjflsdjfladsjfkdls"};
    // 测试其是否计算了字符数而不是单词数
    vector<string> results;
    vector<string> expected = 
    { "zbakjsdoifajsodjifasjofjksfoasfjoaisdfjaiosdjfosdfjodsajfoisadjfodsfosdjfosdfodsafiodsfioadsjfodsajfiodsj", "jlqkjweojojosfjoasjkfojsfosajflsjlfsjflsajflksajflsjflasjflasjflsadjflsdjfladsjfkdls" };
    int len;
    tie(len, results) = Core::gen_chain_char(input, '\0', '\0');
    ASSERT_EQ(len, 189);
    ASSERT_EQ(results, expected);
}

TEST(gen_chain_char_test, HeadTest){
    vector<string> input = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", 
    "zbakjsdoifajsodjifasjofjksfoasfjoaisdfjaiosdjfosdfjodsajfoisadjfodsfosdjfosdfodsafiodsfioadsjfodsajfiodsj",
    "jlqkjweojojosfjoasjkfojsfosajflsjlfsjflsajflksajflsjflasjflasjflsadjflsdjfladsjfkdls"};
    // 测试其是否计算了字符数而不是单词数
    vector<string> results;
    vector<string> expected = 
    { "jlqkjweojojosfjoasjkfojsfosajflsjlfsjflsajflksajflsjflasjflasjflsadjflsdjfladsjfkdls" };
    int len;
    tie(len, results) = Core::gen_chain_char(input, 'j', '\0');
    ASSERT_EQ(len, 84);
    ASSERT_EQ(results, expected);
}

TEST(gen_chain_char_test, TailTest){
    vector<string> input = {"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", 
    "zbakjsdoifajsodjifasjofjksfoasfjoaisdfjaiosdjfosdfjodsajfoisadjfodsfosdjfosdfodsafiodsfioadsjfodsajfiodsj",
    "jlqkjweojojosfjoasjkfojsfosajflsjlfsjflsajflksajflsjflasjflasjflsadjflsdjfladsjfkdls"};
    // 测试其是否计算了字符数而不是单词数
    vector<string> results;
    vector<string> expected = 
    { "zbakjsdoifajsodjifasjofjksfoasfjoaisdfjaiosdjfosdfjodsajfoisadjfodsfosdjfosdfodsafiodsfioadsjfodsajfiodsj" };
    int len;
    tie(len, results)= Core::gen_chain_char(input, '\0', 'j');
    ASSERT_EQ(len, 105);
    ASSERT_EQ(results, expected);
}

TEST(gen_chain_char_test, MostCharCountWithMultipleWordInOneNode){
    vector<string> input = {"abb", "ab", "abbbbbb", "bc", "cd", "de", "ef", "fg", "gh", "hi", 
    "zbakjsdoifajsodjifasjofjksfoasfjoaisdfjaiosdjfosdfjodsajfoisadjfodsfosdjfosdfodsafiodsfioadsjfodsajfiodsj",
    "jlqkjweojojosfjoasjkfojsfosajflsjlfsjflsajflksajflsjflasjflasjflsadjflsdjfladsjfkdls"};
    // 测试其是否计算了字符数而不是单词数
    vector<string> results;
    vector<string> expected = 
    { "zbakjsdoifajsodjifasjofjksfoasfjoaisdfjaiosdjfosdfjodsajfoisadjfodsfosdjfosdfodsafiodsfioadsjfodsajfiodsj", "jlqkjweojojosfjoasjkfojsfosajflsjlfsjflsajflksajflsjflasjflasjflsadjflsdjfladsjfkdls" };
    int len;
    tie(len, results) = Core::gen_chain_char(input, '\0', '\0');
    ASSERT_EQ(len, 189);
    ASSERT_EQ(results, expected);
}

TEST(gen_chain_word_test, NullTest){
    vector<string> input;
    vector<string> results;
    int len;
    tie(len, results) = Core::gen_chain_word(input, '\0', '\0');
    ASSERT_TRUE(input.empty());
    ASSERT_TRUE(results.empty());
}

TEST(gen_chain_word_test, GivenNullChar){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef"};
    vector<string> results;
    vector<string> expected = { "da", "ab", "bc", "cd", "de", "ef" };
    int len;
    tie(len, results) = Core::gen_chain_word(input, '\0', '\0');
    ASSERT_EQ(len, 6);
    ASSERT_EQ(expected, results);
}

TEST(gen_chain_word_test, GivenHeadChar){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef", "fa"};
    vector<string> results;
    vector<string> expected = { "ef", "fa", "ab", "bc", "cd", "da" };
    int len;
    tie(len, results) = Core::gen_chain_word(input, 'e', '\0');
    ASSERT_EQ(len, 6);
    ASSERT_EQ(expected, results);
}

TEST(gen_chain_word_test, GivenTailChar){
    vector<string> input = {"ab", "bc", "cd", "de", "da", "ef", "fa"};
    vector<string> results;
    vector<string> expected = { "da", "ab", "bc", "cd", "de", "ef" };
    int len;
    tie(len, results) = Core::gen_chain_word(input, '\0', 'f');
    ASSERT_EQ(len, 7);
    ASSERT_EQ(expected, results);
}

TEST(gen_chain_word_test, GivenBothCharWithMultipleWordInOneNode){
    vector<string> input = {"abb", "ab", "abbb", "bc", "cd", "de", "da", "ef"};
    vector<string> results;
    vector<string> expected = { "abbb", "bc", "cd", "da" };
    int len;
    tie(len, results) = Core::gen_chain_word(input, 'a', 'a');
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

TEST(gen_chain_n_word_test, Test1WithMultipleWordInOneNode){
    vector<string> input = {"abb", "ab", "abbb", "bc", "cd", "de", "da", "ef", "fa"};
    ostringstream test_ostream;
    Core::gen_chain_n_word(input, 2, test_ostream);

    string result = test_ostream.str();
    string expected = "abbb bc \nbc cd \ncd da \ncd de \nda abbb \nde ef \nef fa \nfa abbb \nabbb bc \n";
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