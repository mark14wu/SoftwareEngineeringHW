#include <fstream>

#include "cmdline.h"
#include "Core.cpp"
#include "ArgParser.cpp"
#include "PreProcessing.cpp"

using namespace std;

int main(int argc, char *argv[]) {
	ofstream outfile;
	outfile.open("solution.txt");

	string filename;
	char head, tail;
	int num;
	bool word_flag = false,
		char_flag = false, 
		num_flag = false;
	
	ArgParser::parse(argc, argv, filename, head, tail, num, word_flag, char_flag, num_flag);

	vector<string> WordChain;

	ifstream infile;
	PreProcessing::process(infile, filename, WordChain);

	int length1 = 0;
	int max_length = 0;
	vector<int> result;
	vector<int> temp_result;
	vector<string> string_result;
	vector<string> new_result;
	// int n; // n is the length of word chain
	int new_n;
	if (word_flag){
		if (!num_flag) {
			// n = most_word(1, 0, length1, max_length, head, tail, WordMatrix, result, temp_result);
			new_n = Core::gen_chain_word(WordChain, new_result, head, tail);
			// cout << "n1=" << n << endl;
			cout << "n=" << new_n << endl;
		}
	}
	else if (char_flag){
		// n = most_char (1, 0, length1, max_length, head, tail, WordMatrix, result, temp_result);
		new_n = Core::gen_chain_char(WordChain, new_result);
	}
	else{
		cerr << "flag exception!" << endl;
		// outfile << "flag exception!" << endl;
		return -1;
	}
	// n = 0;
	if (num_flag == true)
		// n_word(1, 0, length1, num, n, WordMatrix, string_result, outfile);
		Core::gen_chain_n_word(WordChain, num, outfile);

	if (num_flag == false) {
		if (result.size() > 2) {
			/*
			for (vector<int>::iterator it = result.begin(); it != result.end() - 1; it++)
			{
				//outfile << *it << endl;
				outfile << WordMatrix[*it][*(it + 1)].wordlist[WordMatrix[*it][*(it + 1)].word_count - 1] << endl;
				WordMatrix[*it][*(it + 1)].word_count--;
			}
			*/
			for (vector<string>::iterator it = new_result.begin(); it != new_result.end(); it++) {
				outfile << *it << endl;
			}
		}
		else {
			//error 2
			cerr << "error: word chain not found !" << endl;
			// outfile << "error: word chain not found !" << endl;
			return -1;
		}
	}
	else {
		outfile.seekp(0, ios::beg);
		outfile << new_n << endl;
	}
	infile.close(); 
	outfile.close();
}