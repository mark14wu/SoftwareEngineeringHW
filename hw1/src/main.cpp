#include <fstream>
#include "cmdline.h"
#include "Core.cpp"

using namespace std;

int main(int argc, char *argv[]) {
	// parsing arguments
	cmdline::parser argparser;
	ofstream outfile;
	outfile.open("solution.txt");
	
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
	string filename, buffer;
	char head_char, tail_char;
	int head, tail;
	int num;
	bool word_flag = false, char_flag = false, num_flag = false;

	// getting head char
	// buffer is STRING, get first char of buffer
	buffer = argparser.get<string>("head");
	if (buffer.length() > 1){
		cerr << "length of head character is greater than 1!" << endl;
		outfile << "length of head character is greater than 1!" << endl;
		return -1;
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
			outfile << "head character is not in the range(a-z, A-Z)!" << endl;
		}
	}
	else{
		head = 0;
	}

	// getting tail char
	buffer = argparser.get<string>("tail");
	if (buffer.length() > 1){
		cerr << "length of tail character is greater than 1!" << endl;
		outfile << "length of tail character is greater than 1!" << endl;
		return -1;
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
			outfile << "head character is not in the range(a-z, A-Z)!" << endl;
			return -1;
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
		outfile << "Either -w or -c must be selected!" << endl;
		return -1;
	}
	else if (argparser.exist("word") && argparser.exist("char")){
		cerr << "-w and -c cannot be used together!(Not Implemented!)" << endl;
		outfile << "-w and -c cannot be used together!(Not Implemented!)" << endl;
		return -1;
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
		outfile << "Using -c and -n together is not implemented!" << endl;
		return -1;
	}

	filename = argparser.rest()[0];

	////////////////////////////
	// argument parsing finished
	////////////////////////////

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