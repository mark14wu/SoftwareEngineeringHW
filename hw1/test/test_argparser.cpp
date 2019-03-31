#include "gmock/gmock.h"
#include "../src/ArgParser.cpp"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv){
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(parse_test, WordSwitch){
    vector<string> arguments = {"./a.out", "-w", "test.txt"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
    
    ASSERT_EQ(filename, "test.txt");
    ASSERT_EQ(head, '\0');
    ASSERT_EQ(tail, '\0');
    ASSERT_EQ(num, 2147483647);
    ASSERT_TRUE(word_flag);
    ASSERT_FALSE(char_flag);
    ASSERT_FALSE(num_flag);
}

TEST(parse_test, CharSwitch){
    vector<string> arguments = {"./a.out", "-c", "test.txt"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
    
    ASSERT_EQ(filename, "test.txt");
    ASSERT_EQ(head, '\0');
    ASSERT_EQ(tail, '\0');
    ASSERT_EQ(num, 2147483647);
    ASSERT_TRUE(char_flag);
    ASSERT_FALSE(word_flag);
    ASSERT_FALSE(num_flag);
}

TEST(parse_test, WordSwitchWithCount){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-n", "114514"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
    
    ASSERT_EQ(filename, "test.txt");
    ASSERT_EQ(head, '\0');
    ASSERT_EQ(tail, '\0');
    ASSERT_EQ(num, 114514);
    ASSERT_TRUE(word_flag);
    ASSERT_FALSE(char_flag);
    ASSERT_TRUE(num_flag);
}

TEST(parse_test, WordSwitchWithHead){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-h", "a"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
    
    ASSERT_EQ(filename, "test.txt");
    ASSERT_EQ(head, 'a');
    ASSERT_EQ(tail, '\0');
    ASSERT_EQ(num, 2147483647);
    ASSERT_TRUE(word_flag);
    ASSERT_FALSE(char_flag);
    ASSERT_FALSE(num_flag);
}

TEST(parse_test, WordSwitchWithTail){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-t", "a"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
    
    ASSERT_EQ(filename, "test.txt");
    ASSERT_EQ(head, '\0');
    ASSERT_EQ(tail, 'a');
    ASSERT_EQ(num, 2147483647);
    ASSERT_TRUE(word_flag);
    ASSERT_FALSE(char_flag);
    ASSERT_FALSE(num_flag);
}

TEST(parse_test, WordSwitchWithBothHeadAndTail){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-h", "a", "-t", "a"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
    
    ASSERT_EQ(filename, "test.txt");
    ASSERT_EQ(head, 'a');
    ASSERT_EQ(tail, 'a');
    ASSERT_EQ(num, 2147483647);
    ASSERT_TRUE(word_flag);
    ASSERT_FALSE(char_flag);
    ASSERT_FALSE(num_flag);
}

TEST(parse_test, WordSwitchWithBothHeadAndTailAndCount){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-h", "a", "-t", "a", "-n", "114514"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
    
    ASSERT_EQ(filename, "test.txt");
    ASSERT_EQ(head, 'a');
    ASSERT_EQ(tail, 'a');
    ASSERT_EQ(num, 114514);
    ASSERT_TRUE(word_flag);
    ASSERT_FALSE(char_flag);
    ASSERT_TRUE(num_flag);
}