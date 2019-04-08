#include <fstream>

#include "cmdline.h"

using namespace std;

class ArgParser{
    public:
        static void parse(int argc, char *argv[],
        string &filename, char &head, char &tail, int &num, bool &word_flag, bool &char_flag, bool &num_flag){
            // parsing arguments
            cmdline::parser argparser;
            
            // counting word numbers, "-w"
            argparser.add("word", 'w', "word count");

            // counting characters, "-c"
            argparser.add("char", 'c', "character count");

            // given head character, default = ""
            argparser.add<string>("head", 'h', "head character", false, "");

            // given tail character, default = ""
            argparser.add<string>("tail", 't', "tail character", false, "");

            // given word counts, default = 0
            argparser.add<int>("num", 'n', "given word number", false, 2147483647, cmdline::range(2, 2147483647));

            // run parser
            argparser.parse_check(argc, argv);

            // get results
            string buffer;
            char head_char, tail_char;  // raw head and tail chars without checking

            // getting head char
            // buffer is STRING, get first char of buffer
            buffer = argparser.get<string>("head");
            if (buffer.length() > 1){
                throw length_error("head character length error!");
            }
            head_char = buffer[0];
            if (head_char != '\0'){
                if ('a' <= head_char && head_char <= 'z'){
                    head = head_char;
                }
                else if ('A' <= head_char && head_char <= 'Z'){
                    head = head_char - 'A' + 'a';
                }
                else{
                    throw out_of_range("head character is not in the range(a-z, A-Z)!");
                }
            }
            else{
                head = 0;
            }

            // getting tail char
            buffer = argparser.get<string>("tail");
            if (buffer.length() > 1){
                throw length_error("tail character length error!");
            }
            tail_char = buffer[0];
            if (tail_char != '\0'){
                if ('a' <= tail_char && tail_char <= 'z'){
                    tail = tail_char;
                }
                else if ('A' <= tail_char && tail_char <= 'Z'){
                    tail = tail_char - 'A' + 'a';
                }
                else{
                    throw out_of_range("tail character is not in the range(a-z, A-Z)!");
                }
            }
            else{
                tail = 0;
            }

            // getting word chain length
            num = argparser.get<int>("num");
            if (num != 2147483647) num_flag = true;
            else num_flag = false;

            
            if (!argparser.exist("word") &&!argparser.exist("char")){
                throw invalid_argument("Either -w or -c must be selected!");
            }
            else if (argparser.exist("word") && argparser.exist("char")){
                throw invalid_argument("-w and -c cannot be used together!(Not Implemented!)");
            }
            
            // judging work mode

            if (argparser.exist("word")) word_flag = true;
            else word_flag = false;
            
            if (argparser.exist("char")) char_flag = true;
            else char_flag = false;
            
            if (num_flag && char_flag){
                throw invalid_argument("Using -c and -n together is not implemented!");
            }
            filename = argparser.rest()[0];
        }
};