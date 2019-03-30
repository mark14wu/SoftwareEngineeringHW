#include <fstream>

#include "cmdline.h"

using namespace std;

class ArgParser{
    public:
        static void parse(int argc, char *argv[],
        string &filename, int &head, int &tail, int &num, bool &word_flag, bool &char_flag, bool &num_flag){
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
            char head_char, tail_char;

            // getting head char
            // buffer is STRING, get first char of buffer
            buffer = argparser.get<string>("head");
            if (buffer.length() > 1){
                cerr << "length of head character is greater than 1!" << endl;
                // outfile << "length of head character is greater than 1!" << endl;
                exit(-1);
            }
            head_char = buffer[0];
            if (head_char != '\0'){
                if ('a' <= head_char && head_char <= 'z'){
                    head = head_char - 'a' + 1;
                }
                else if ('A' <= head_char && head_char <= 'Z'){
                    head = head_char - 'A' + 1;
                }
                else{
                    cerr << "head character is not in the range(a-z, A-Z)!" << endl;
                    // outfile << "head character is not in the range(a-z, A-Z)!" << endl;
                }
            }
            else{
                head = 0;
            }

            // getting tail char
            buffer = argparser.get<string>("tail");
            if (buffer.length() > 1){
                cerr << "length of tail character is greater than 1!" << endl;
                // outfile << "length of tail character is greater than 1!" << endl;
                exit(-1);
            }
            tail_char = buffer[0];
            if (tail_char != '\0'){
                if ('a' <= tail_char && tail_char <= 'z'){
                    tail = tail_char - 'a' + 1;
                }
                else if ('A' <= tail_char && tail_char <= 'Z'){
                    tail = tail_char - 'A' + 1;
                }
                else{
                    cerr << "head character is not in the range(a-z, A-Z)!" << endl;
                    // outfile << "head character is not in the range(a-z, A-Z)!" << endl;
                    exit(-1);
                }
            }
            else{
                tail = 0;
            }

            // getting word chain length
            num = argparser.get<int>("num");
            if (num != 2147483647)
                num_flag = true;
            
            if (!argparser.exist("word") &&!argparser.exist("char")){
                cerr << "Either -w or -c must be selected!" << endl;
                // outfile << "Either -w or -c must be selected!" << endl;
                exit(-1);
            }
            else if (argparser.exist("word") && argparser.exist("char")){
                cerr << "-w and -c cannot be used together!(Not Implemented!)" << endl;
                // outfile << "-w and -c cannot be used together!(Not Implemented!)" << endl;
                exit(-1);
            }
            
            // judging work mode

            if (argparser.exist("word")){
                word_flag = true;
            }
            else if (argparser.exist("char")){
                char_flag = true;
            }
            
            if (num_flag && char_flag){
                cerr << "Using -c and -n together is not implemented!" << endl;
                // outfile << "Using -c and -n together is not implemented!" << endl;
                exit(-1);
            }
            filename = argparser.rest()[0];
        }
};