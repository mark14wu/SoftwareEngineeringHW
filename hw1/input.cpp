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
			int best_i;
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
	int best_i;
	for (int i = 0; i < 26; i++) {
		if (num_matrix[start][i].word_count > 0) {
			num_matrix[start][i].word_count--;
			length++;
			temp_result.push_back(i);
			if (end_char == 0) {
				if (length > max_length) {
					max_length = length;
					printf("%d\n", max_length);
					result.clear();
					result.assign(temp_result.begin(), temp_result.end());
				}
			}
			else {
				if (length > max_length && i==end_char-1) {
					max_length = length;
					printf("%d\n", max_length);
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
			int best_i;
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
	int best_i;
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
					printf("%d %d\n", MaxCharNum, max_length);
					result.clear();
					result.assign(temp_result.begin(), temp_result.end());
				}
			}
			else {
				if (length > max_length && end_char-1==i) {
					max_length = length;
					printf("%d %d\n", MaxCharNum, max_length);
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

void n_word(int if_start, int start, int &length, int n_length, int &n, WordNode num_matrix[][26], vector<string> &temp_result) {
	if (if_start == 1) {
		for (int i = 0; i < 26; i++) {
			n_word(0, i, length, n_length, n, num_matrix, temp_result);
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
					cout << *it << " ";
				}
				cout << endl;
			}
			else {
				n_word(0, i, length, n_length, n, num_matrix, temp_result);
			}
			num_matrix[start][i].wordlist.push_back(temp_result.back());
			temp_result.pop_back();
			length--;
			num_matrix[start][i].word_count++;
		}
	}
}

void parse_args(){

}
int main(int argc, char *argv[]) {
	// parsing arguments
	cmdline::parser argparser;
	
	// counting word numbers, default = ""
	argparser.add<string>("word", 'w', "word count", false, "");

	// counting characters, default = ""
	argparser.add<string>("char", 'c', "character count", false, "");

	// given head character, default = ""
	argparser.add<string>("head", 'h', "head character", false, "");

	// given tail character, default = ""
	argparser.add<string>("tail", 't', "tail character", false, "");

	// given word counts, default = 0
	argparser.add<int>("num", 'n', "given word number", false, 0);

	// run parser
	argparser.parse_check(argc, argv);

	// get results
	string filename_word, filename_char, buffer;
	char head_char, tail_char;
	int head, tail;
	int num;
	bool word_flag = false, char_flag = false, num_flag = false;

	filename_word = argparser.get<string>("word");
	filename_char = argparser.get<string>("char");
	// getting head char
	// buffer is STRING, get first char of buffer
	buffer = argparser.get<string>("head");
	if (buffer.length() > 1){
		cerr << "首字母长度大于1!" << endl;
		return -1;
	}
	head_char = buffer[0];
	if ('a' <= head_char && head_char <= 'z'){
		head = head_char - 'a' + 1;
	}
	else if ('A' <= head_char && head_char <= 'Z'){
		head = head_char - 'A' + 1;
	}
	else{
		cerr << "头字母不在范围内！" << endl;
	}

	// getting tail char
	buffer = argparser.get<string>("tail");
	if (buffer.length() > 1){
		cerr << "尾字母长度大于1!" << endl;
		return -1;
	}
	tail_char = buffer[0];
		if ('a' <= tail_char && tail_char <= 'z'){
		tail = tail_char - 'a' + 1;
	}
	else if ('A' <= tail_char && tail_char <= 'Z'){
		tail = tail_char - 'A' + 1;
	}
	else{
		cerr << "头字母不在范围内！" << endl;
		return -1;
	}

	// getting word chain length
	num = argparser.get<int>("num");
	if (num >= 0){
		if (num > 0)
			num_flag = true;
	}
	else{
		cerr << "输入数字不能为负！" << endl;
		return -1;
	}
	
	cout << filename_word << filename_char << head << tail << num << endl;
	if (filename_word.length() != 0 && filename_char.length() != 0){
		cerr << "不支持同时使用 -w 和 -c！" << endl;
		return -1;
	}

	// judging work mode
	string filename;

	if (filename_word.length() != 0){
		filename = filename_word;
		word_flag = true;
	}
	else{
		filename = filename_char;
		char_flag = true;
	}

	if ((!word_flag) && (!char_flag)){
		cerr << "至少选择 -w 和 -c 中的一种！" << endl;
		return -1;
		}
	
	if (num_flag && char_flag){
		cerr << "暂不支持 -c 和 -n 同时使用！" << endl;
		return -1;
	}

	// argument parsing finished

	/*int num_matrix[26][26] = { 0 };
	vector<string> word_matrix[26][26];*/
	WordNode WordMatrix[26][26];
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			WordMatrix[i][j].prefix = 97 + i;
			WordMatrix[i][j].suffix = 97 + j;
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
	if (!infile.is_open())
		cout << "Open file " << filename << " failure" << endl;
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
				//cout << start_char << temp_string << end_char << endl;
				int start_index = start_char-97;
				int end_index = end_char-97;
				bool if_repeat=false;
				for (vector<string>::iterator it = WordMatrix[start_index][end_index].wordlist.begin(); it != WordMatrix[start_index][end_index].wordlist.end(); it++)
				{
					//cout << "test: " << temp_string << *it << temp_string.compare(*it)  << endl;
					if (temp_string.compare(*it) == 0)
						if_repeat = true;
				}
				if (!if_repeat) {
					//WordMatrix[start_index][end_index].wordlist.push_back(temp_string);
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

	if (word_count == 0) {
		//error1
	}

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			for (vector<string>::iterator it = WordMatrix[i][j].wordlist.begin(); it != WordMatrix[i][j].wordlist.end(); it++)
			 {
				cout << *it << endl;
			 }
		}
	}

	/*for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			cout << WordMatrix[i][j].word_count;
		}
		cout << endl;

	}*/
	///////////////----preprocessing finished----////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	int length1 = 0;
	int max_length = 0;
	vector<int> result;
	vector<int> temp_result;
	vector<string> string_result;

	int n; // n is the length of word chain
	if (word_flag){
		n = most_word(1, 0, length1, max_length , head, tail, WordMatrix, result, temp_result);	
	}
	else if (char_flag){
		n = most_char (1, 0, length1, max_length, head, tail, WordMatrix, result, temp_result);
	}
	else{
		cerr << "flag exception!" << endl;
		return -1;
	}

	n_word(1, 0, length1, num, n, WordMatrix, string_result);

	printf("ans:%d\n", max_length);
	printf("n:%d\n", n);
	if (result.empty() == 0) {
		for (vector<int>::iterator it = result.begin(); it != result.end() - 1; it++)
		{
			cout << *it << endl;
			cout << WordMatrix[*it][*(it + 1)].wordlist[WordMatrix[*it][*(it + 1)].word_count - 1] << endl;
			WordMatrix[*it][*(it + 1)].word_count--;
		}
	}
	else {
		//error 2
		cout << "error: word chain not found !" << endl;
	}
	infile.close(); 
	getchar();
}

