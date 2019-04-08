#include <fstream>
#include <system_error>
#include <tuple>

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

	infile.open(filename, ios::in);
	if (infile.fail()){
		throw system_error(errno, std::generic_category());
	}

	WordChain = PreProcessing::process(infile);

	int length1 = 0;
	int max_length = 0;
	vector<string> result;

	int n; // n is the length of word chain
	if (word_flag){
		if (!num_flag) {
			tie(n, result) = Core::gen_chain_word(WordChain, head, tail);
			cout << "word chain length = " << n << endl;
		}
	}
	else if (char_flag){
		tie(n, result) = Core::gen_chain_char(WordChain, head, tail);
		cout << "word chain char number = " << n << endl;
	}
	else{
		throw invalid_argument("!-w and !-c!");
	}

	if (num_flag == true)
		Core::gen_chain_n_word(WordChain, num, outfile);

	if (num_flag == false) {
		for (vector<string>::iterator it = result.begin(); it != result.end(); it++)
			outfile << *it << endl;
	}
	else {
		outfile.seekp(0, ios::beg);
		outfile << n << endl;
	}
	infile.close(); 
	outfile.close();
}