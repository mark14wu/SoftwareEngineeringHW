#include <fstream>
#include "cmdline.h"

using namespace std;

class WordNode{
    public:
        char prefix;
        char suffix;
        vector <string> wordlist;
        int word_count;
		int word_use;
};

int most_word(int if_start, int start, int &length ,int &max_length, int start_char, int end_char, WordNode num_matrix[][26], vector<int> &result, vector<int> &temp_result) {
	if (if_start == 1) {
		if (start_char == 0) {
			int n = 0;
			for (int i = 0; i < 26; i++) {
				temp_result.clear();
				temp_result.push_back(i);
				int temp = most_word(0, i, length, max_length, start_char, end_char, num_matrix, result, temp_result);
				if (temp > n) {
					n = temp;
				}
			}
			return n;
		}
		else {
			temp_result.clear();
			temp_result.push_back(start_char - 1);
			return most_word(0, start_char - 1, length, max_length, start_char, end_char, num_matrix, result, temp_result);
		}
	}
	int n = 0;
	for (int i = 0; i < 26; i++) {
		if (num_matrix[start][i].word_count > 0) {
			num_matrix[start][i].word_count--;
			length++;
			temp_result.push_back(i);
			if (end_char == 0) {
				if (length > max_length) {
					max_length = length;
					//printf("%d\n", max_length);
					result.clear();
					result.assign(temp_result.begin(), temp_result.end());
				}
			}
			else {
				if (length > max_length && i==end_char-1) {
					max_length = length;
					//printf("%d\n", max_length);
					result.clear();
					result.assign(temp_result.begin(), temp_result.end());
				}
			}
			int temp = most_word(0, i, length, max_length, start_char, end_char, num_matrix, result, temp_result)+1;
			if (temp > n) {
				n = temp;
			}
			temp_result.pop_back();
			length--;
			num_matrix[start][i].word_count++;
		}
	}
	return n;
}

int most_char(int if_start, int start, int &length, int &max_length, int start_char, int end_char, WordNode num_matrix[][26], vector<int> &result, vector<int> &temp_result) {
	if (if_start == 1) {
		if (start_char == 0) {
			int n = 0;
			for (int i = 0; i < 26; i++) {
				temp_result.clear();
				temp_result.push_back(i);
				int temp = most_char(0, i, length, max_length, start_char, end_char, num_matrix, result, temp_result);
				if (temp > n) {
					n = temp;
				}
			}
			return n;
		}
		else {
			temp_result.clear();
			temp_result.push_back(start_char - 1);
			return most_char(0, start_char - 1, length, max_length, start_char, end_char, num_matrix, result, temp_result);
		}
	}
	int n = 0;
	for (int i = 0; i < 26; i++) {
		if (num_matrix[start][i].word_count > 0) {
			num_matrix[start][i].word_count--;
			num_matrix[start][i].word_use++;
			vector<string>::iterator it = num_matrix[start][i].wordlist.end();
			int MaxCharNum = (*(it - num_matrix[start][i].word_use)).length();
			length+= MaxCharNum;
			temp_result.push_back(i);
			if (end_char == 0) {
				if (length > max_length) {
					max_length = length;
					//printf("%d %d\n", MaxCharNum, max_length);
					result.clear();
					result.assign(temp_result.begin(), temp_result.end());
				}
			}
			else {
				if (length > max_length && end_char-1==i) {
					max_length = length;
					//printf("%d %d\n", MaxCharNum, max_length);
					result.clear();
					result.assign(temp_result.begin(), temp_result.end());
				}
			}
			int temp = most_char(0, i, length, max_length, start_char, end_char, num_matrix, result, temp_result) + MaxCharNum;
			if (temp > n) {
				n = temp;
			}
			temp_result.pop_back();
			length-= MaxCharNum;
			num_matrix[start][i].word_use--;
			num_matrix[start][i].word_count++;
		}
	}
	return n;
}

void n_word(int if_start, int start, int &length, int n_length, int &n, WordNode num_matrix[][26], vector<string> &temp_result, ofstream &outfile) {
	for (vector<string>::iterator it = temp_result.begin(); it != temp_result.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
	if (if_start == 1) {
		for (int i = 0; i < 26; i++) {
			n_word(0, i, length, n_length, n, num_matrix, temp_result, outfile);
		}
	}
	for (int i = 0; i < 26; i++) {
		if (num_matrix[start][i].word_count > 0) {
			num_matrix[start][i].word_count--;
			length++;
			temp_result.push_back(num_matrix[start][i].wordlist[num_matrix[start][i].word_count]);
			num_matrix[start][i].wordlist.pop_back();
			if (length == n_length) {
				n++;
				for (vector<string>::iterator it = temp_result.begin(); it != temp_result.end(); it++) {
					outfile << *it << " ";
					cout << *it << " ";
				}
				outfile << endl;
				cout << endl;
			}
			else {
				n_word(0, i, length, n_length, n, num_matrix, temp_result, outfile);
			}
			num_matrix[start][i].wordlist.push_back(temp_result.back());
			temp_result.pop_back();
			length--;
			num_matrix[start][i].word_count++;
		}
	}
}

class Core {
public:
	static int gen_chain(vector<string> &words, int len, vector<string> &result) {
		result.clear();
		WordNode WordMatrix[26][26];
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				WordMatrix[i][j].prefix = 'a' + i;
				WordMatrix[i][j].suffix = 'a' + j;
				WordMatrix[i][j].word_count = 0;
				WordMatrix[i][j].word_use = 0;
			}
		}
		for (vector<string>::iterator it1 = words.begin(); it1 != words.end(); it1++) {
			string temp_string(*it1);
			int start_index, end_index;
			start_index = temp_string.at(0) - 97;
			end_index = temp_string.at(temp_string.length() - 1)-97;
			vector<string>::iterator it = WordMatrix[start_index][end_index].wordlist.begin();
			while (it != WordMatrix[start_index][end_index].wordlist.end()) {
				if ((*it).length() <= temp_string.length())
					it++;
				else
					break;
			}
			WordMatrix[start_index][end_index].wordlist.insert(it, temp_string);
			WordMatrix[start_index][end_index].word_count++;
		}
		int head = 0;
		int tail = 0;
		int length = 0;
		int max_length = 0;
		vector<int> int_result;
		vector<int> temp_result;
		int n = most_word(1, 0, length, max_length, head, tail, WordMatrix, int_result, temp_result);
		for (vector<int>::iterator it = int_result.begin(); it != int_result.end() - 1; it++)
		{
			result.push_back(WordMatrix[*it][*(it + 1)].wordlist[WordMatrix[*it][*(it + 1)].word_count - 1]);
			WordMatrix[*it][*(it + 1)].word_count--;
		}
		return n;
	}

	static int gen_chain_char(vector<string> &words, int len, vector<string> &result) {
		result.clear();
		WordNode WordMatrix[26][26];
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				WordMatrix[i][j].prefix = 'a' + i;
				WordMatrix[i][j].suffix = 'a' + j;
				WordMatrix[i][j].word_count = 0;
				WordMatrix[i][j].word_use = 0;
			}
		}
		for (vector<string>::iterator it1 = words.begin(); it1 != words.end(); it1++) {
			string temp_string(*it1);
			int start_index, end_index;
			start_index = temp_string.at(0) - 97;
			end_index = temp_string.at(temp_string.length() - 1) - 97;
			vector<string>::iterator it = WordMatrix[start_index][end_index].wordlist.begin();
			while (it != WordMatrix[start_index][end_index].wordlist.end()) {
				if ((*it).length() <= temp_string.length())
					it++;
				else
					break;
			}
			WordMatrix[start_index][end_index].wordlist.insert(it, temp_string);
			WordMatrix[start_index][end_index].word_count++;
		}
		int head = 0;
		int tail = 0;
		int length = 0;
		int max_length = 0;
		vector<int> int_result;
		vector<int> temp_result;
		int n = most_char(1, 0, length, max_length, head, tail, WordMatrix, int_result, temp_result);
		for (vector<int>::iterator it = int_result.begin(); it != int_result.end() - 1; it++)
		{
			result.push_back(WordMatrix[*it][*(it + 1)].wordlist[WordMatrix[*it][*(it + 1)].word_count - 1]);
			WordMatrix[*it][*(it + 1)].word_count--;
		}
		return n;
	}

	static int gen_chain_word(vector<string> &words, int len, vector<string> &result, char head, char tail) {
		result.clear();
		WordNode WordMatrix[26][26];
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				WordMatrix[i][j].prefix = 'a' + i;
				WordMatrix[i][j].suffix = 'a' + j;
				WordMatrix[i][j].word_count = 0;
				WordMatrix[i][j].word_use = 0;
			}
		}
		for (vector<string>::iterator it1 = words.begin(); it1 != words.end(); it1++) {
			string temp_string(*it1);
			int start_index, end_index;
			start_index = temp_string.at(0) - 97;
			end_index = temp_string.at(temp_string.length() - 1) - 97;
			vector<string>::iterator it = WordMatrix[start_index][end_index].wordlist.begin();
			while (it != WordMatrix[start_index][end_index].wordlist.end()) {
				if ((*it).length() <= temp_string.length())
					it++;
				else
					break;
			}
			WordMatrix[start_index][end_index].wordlist.insert(it, temp_string);
			WordMatrix[start_index][end_index].word_count++;
		}
		int head_int = head- 'a' + 1;
		int tail_int = tail- 'a' + 1;
		int length = 0;
		int max_length = 0;
		vector<int> int_result;
		vector<int> temp_result;
		int n = most_word(1, 0, length, max_length, head_int, tail_int, WordMatrix, int_result, temp_result);
		for (vector<int>::iterator it = int_result.begin(); it != int_result.end() - 1; it++)
		{
			result.push_back(WordMatrix[*it][*(it + 1)].wordlist[WordMatrix[*it][*(it + 1)].word_count - 1]);
			WordMatrix[*it][*(it + 1)].word_count--;
		}
		return n;
	}

	static void gen_chain_n_word(vector<string> &words, int len, int num, vector<string> &result, ofstream &outfile) {
		result.clear();
		WordNode WordMatrix[26][26];
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				WordMatrix[i][j].prefix = 'a' + i;
				WordMatrix[i][j].suffix = 'a' + j;
				WordMatrix[i][j].word_count = 0;
				WordMatrix[i][j].word_use = 0;
			}
		}
		for (vector<string>::iterator it1 = words.begin(); it1 != words.end(); it1++) {
			string temp_string(*it1);
			int start_index, end_index;
			start_index = temp_string.at(0) - 97;
			end_index = temp_string.at(temp_string.length() - 1) - 97;
			vector<string>::iterator it = WordMatrix[start_index][end_index].wordlist.begin();
			while (it != WordMatrix[start_index][end_index].wordlist.end()) {
				if ((*it).length() <= temp_string.length())
					it++;
				else
					break;
			}
			WordMatrix[start_index][end_index].wordlist.insert(it, temp_string);
			WordMatrix[start_index][end_index].word_count++;
		}
		int length = 0;
		int n = 0;
		vector<string> string_result;
		n_word(1, 0, length, num, n, WordMatrix, string_result, outfile);
	}
};

void parse_args(){

}
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
			n = most_word(1, 0, length1, max_length, head, tail, WordMatrix, result, temp_result);
			new_n = Core::gen_chain_word(WordChain, WordChain.size(), new_result,head_char,end_char);
			cout << "n1=" << n << endl;
			cout << "n2=" << new_n << endl;
		}
	}
	else if (char_flag){
		n = most_char (1, 0, length1, max_length, head, tail, WordMatrix, result, temp_result);
	}
	else{
		cerr << "flag exception!" << endl;
		outfile << "flag exception!" << endl;
		return -1;
	}
	n = 0;
	if (num_flag == true)
		n_word(1, 0, length1, num, n, WordMatrix, string_result, outfile);

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


