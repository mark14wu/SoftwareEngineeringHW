#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "WordNode.cpp"

using namespace std;

class PreProcessing{
    public:
        static void process(ifstream &infile, string filename, vector<string> &WordChain){
            WordNode WordMatrix[26][26];
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    WordMatrix[i][j].prefix = 'a' + i;
                    WordMatrix[i][j].suffix = 'a' + j;
                    WordMatrix[i][j].word_count = 0;
                    WordMatrix[i][j].word_use = 0;
                }
            }
            char temp_char,start_char,end_char;
            int length = 0;
            int word_count = 0;
            start_char = 0;
            string temp_string=string();
            infile.open(filename, ios::in);

            if (!infile.is_open()) {
                cerr << "Open file " << filename << " failure!" << endl;
                // outfile << "Open file " << filename << " failure!" << endl;
                exit(-1);
            }
            infile >> noskipws;
            while (!infile.eof())   
            {
                infile >> temp_char;
                if (temp_char >= 'A' && temp_char <= 'Z')
                    temp_char = temp_char + 'a' - 'A';
                if (temp_char >= 'a' && temp_char <= 'z') {
                    length++;
                    if (start_char == 0)
                        start_char = temp_char;
                    end_char = temp_char;
                    temp_string.append(1, temp_char);
                }
                else {
                    if (length > 1) {
                        int start_index = start_char-97;
                        int end_index = end_char-97;
                        bool if_repeat=false;
                        for (vector<string>::iterator it = WordMatrix[start_index][end_index].wordlist.begin(); it != WordMatrix[start_index][end_index].wordlist.end(); it++)
                        {
                            if (temp_string.compare(*it) == 0)
                                if_repeat = true;
                        }
                        if (!if_repeat) {
                            //cout << temp_string << endl;
                            WordChain.push_back(temp_string);
                            vector<string>::iterator it = WordMatrix[start_index][end_index].wordlist.begin();
                            while (it != WordMatrix[start_index][end_index].wordlist.end()) {
                                if ((*it).length() <= temp_string.length())
                                    it++;
                                else
                                    break;
                            }
                            WordMatrix[start_index][end_index].wordlist.insert(it, temp_string);
                            word_count++;
                            WordMatrix[start_index][end_index].word_count++;
                        }
                    }
                    temp_string = string();
                    length = 0;
                    start_char = 0;
                }
            }
            cout << word_count << endl;
            if (word_count == 0) {
                //error1
                cerr << "word not found!" << endl;
                // outfile << "word not found!" << endl;
                exit(-1);
            }
        }
}