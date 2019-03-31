#include "gmock/gmock.h"
#include "../src/ArgParser.cpp"
#include <string>
#include <vector>

extern int main(int, char **);

using namespace std;

TEST(word_test, WordSwitch){
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

TEST(char_test, CharSwitch){
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

TEST(word_test, WithCount){
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

TEST(word_test, WithHead){
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

TEST(word_test, WithUpperCaseHead){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-h", "A"};
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
    ASSERT_EQ(head, 'A');
    ASSERT_EQ(tail, '\0');
    ASSERT_EQ(num, 2147483647);
    ASSERT_TRUE(word_flag);
    ASSERT_FALSE(char_flag);
    ASSERT_FALSE(num_flag);
}

TEST(word_test, WithTail){
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

TEST(word_test, WithUpperCaseTail){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-t", "A"};
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
    ASSERT_EQ(tail, 'A');
    ASSERT_EQ(num, 2147483647);
    ASSERT_TRUE(word_flag);
    ASSERT_FALSE(char_flag);
    ASSERT_FALSE(num_flag);
}

TEST(word_test, WithBothHeadAndTail){
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

TEST(word_test, WithBothHeadAndTailAndCount){
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

TEST(exception_test, HeadCharLengthError){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-h", "aa"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    try{
        ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
        FAIL(); // Exception should be caught!
    }
    catch(length_error const & err){
        EXPECT_EQ(err.what(), string("head character length error!"));
    }
    catch(...){
        FAIL(); // Caught wrong type of Exception
    }
}

TEST(exception_test, TailCharLengthError){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-t", "aa"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    try{
        ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
        FAIL(); // Exception should be caught!
    }
    catch(length_error const & err){
        EXPECT_EQ(err.what(), string("tail character length error!"));
    }
    catch(...){
        FAIL(); // Caught wrong type of Exception
    }
}

TEST(exception_test, HeadCharOutOfRange){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-h","3"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    try{
        ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
        FAIL(); // Exception should be caught!
    }
    catch(out_of_range const & err){
        EXPECT_EQ(err.what(), string("head character is not in the range(a-z, A-Z)!"));
    }
    catch(...){
        FAIL(); // Caught wrong type of Exception
    }
}

TEST(exception_test, TailCharOutOfRange){
    vector<string> arguments = {"./a.out", "-w", "test.txt", "-t","3"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    try{
        ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
        FAIL(); // Exception should be caught!
    }
    catch(out_of_range const & err){
        EXPECT_EQ(err.what(), string("tail character is not in the range(a-z, A-Z)!"));
    }
    catch(...){
        FAIL(); // Caught wrong type of Exception
    }
}

TEST(exception_test, NeitherWordNorChar){
    vector<string> arguments = {"./a.out", "test.txt"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    try{
        ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
        FAIL(); // Exception should be caught!
    }
    catch(invalid_argument const & err){
        EXPECT_EQ(err.what(), string("Either -w or -c must be selected!"));
    }
    catch(...){
        FAIL(); // Caught wrong type of Exception
    }
}

TEST(exception_test, BothWordAndChar){
    vector<string> arguments = {"./a.out", "test.txt", "-w", "-c"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    try{
        ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
        FAIL(); // Exception should be caught!
    }
    catch(invalid_argument const & err){
        EXPECT_EQ(err.what(), string("-w and -c cannot be used together!(Not Implemented!)"));
    }
    catch(...){
        FAIL(); // Caught wrong type of Exception
    }
}

TEST(exception_test, UsingCharWithCount){
    vector<string> arguments = {"./a.out", "test.txt", "-c", "-n", "114514"};
    vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);
    
    string filename;
    char head, tail;
    int num;
    bool word_flag, char_flag, num_flag;
    try{
        ArgParser::parse(argv.size() - 1, argv.data(), filename, head, tail, num,
                word_flag, char_flag, num_flag);
        FAIL(); // Exception should be caught!
    }
    catch(invalid_argument const & err){
        EXPECT_EQ(err.what(), string("Using -c and -n together is not implemented!"));
    }
    catch(...){
        FAIL(); // Caught wrong type of Exception
    }
}