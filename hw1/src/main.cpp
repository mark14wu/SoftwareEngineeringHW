#include <fstream>

#include "cmdline.h"
#include "Core.cpp"
#include "ArgParser.cpp"

using namespace std;

int main(int argc, char *argv[]) {
	ofstream outfile;
	outfile.open("solution.txt");

	string filename;
	int head, tail;
	int num;
	bool word_flag = false,
		char_flag = false, 
		num_flag = false;
	
	ArgParser::parse(argc, argv, filename, head, tail, num, word_flag, char_flag, num_flag);

	WordNode WordMatrix[26][26];
	vector<string> WordChain;
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			WordMatrix[i][j].prefix = 'a' + i;
			WordMatrix[i][j].suffix = 'a' + j;
			WordMatrix[i][j].word_count = 0;
			WordMatrix[i][j].word_use = 0;
		}
	}
	ifstream infile;   
	
	char temp_char,start_char,end_char;
	int length = 0;
	int word_count = 0;
	start_char = 0;
	string temp_string=string();
	infile.open(filename, ios::in);

	if (!infile.is_open()) {
		cerr << "Open file " << filename << " failure!" << endl;
		outfile << "Open file " << filename << " failure!" << endl;
		return -1;
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
		outfile << "word not found!" << endl;
		return -1;
	}
	///////////////----preprocessing finished----////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	int length1 = 0;
	int max_length = 0;
	vector<int> result;
	vector<int> temp_result;
	vector<string> string_result;
	vector<string> new_result;
	int n; // n is the length of word chain
	int new_n;
	if (word_flag){
		if (!num_flag) {
			// n = most_word(1, 0, length1, max_length, head, tail, WordMatrix, result, temp_result);
			new_n = Core::gen_chain_word(WordChain, WordChain.size(), new_result,head_char,end_char);
			cout << "n1=" << n << endl;
			cout << "n2=" << new_n << endl;
		}
	}
	else if (char_flag){
		// n = most_char (1, 0, length1, max_length, head, tail, WordMatrix, result, temp_result);
		new_n = Core::gen_chain_char(WordChain, WordChain.size(), new_result);
	}
	else{
		cerr << "flag exception!" << endl;
		outfile << "flag exception!" << endl;
		return -1;
	}
	n = 0;
	if (num_flag == true)
		// n_word(1, 0, length1, num, n, WordMatrix, string_result, outfile);
		Core::gen_chain_n_word(WordChain, WordChain.size(), num, new_result, outfile);

	if (num_flag == false) {
		if (result.size() > 2) {
			for (vector<int>::iterator it = result.begin(); it != result.end() - 1; it++)
			{
				//outfile << *it << endl;
				outfile << WordMatrix[*it][*(it + 1)].wordlist[WordMatrix[*it][*(it + 1)].word_count - 1] << endl;
				WordMatrix[*it][*(it + 1)].word_count--;
			}
			for (vector<string>::iterator it = new_result.begin(); it != new_result.end(); it++) {
				outfile << *it << endl;
			}
		}
		else {
			//error 2
			cerr << "error: word chain not found !" << endl;
			outfile << "error: word chain not found !" << endl;
			return -1;
		}
	}
	else {
		outfile.seekp(0, ios::beg);
		outfile << n << endl;
	}
	infile.close(); 
	outfile.close();
}