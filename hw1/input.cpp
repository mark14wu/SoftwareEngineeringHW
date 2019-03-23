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

void parse_args(){

}
int main(int argc, char *argv[]) {
	// parsing arguments
	cmdline::parser argparser;
	
	// counting word numbers, default = ""
	argparser.add<string>("word", 'w', "word count", false, "");

	// counting characters, default = ""
	argparser.add<string>("char", 'c', "character count", false, "");

	// given head character, default = '\0'
	argparser.add<char>("head", 'h', "head character", false, '\0');

	// given tail character, default = '\0'
	argparser.add<char>("tail", 't', "tail character", false, '\0');

	// given word counts, default = 0
	argparser.add<int>("num", 'n', "given word number", false, 0);

	// run parser
	argparser.parse_check(argc, argv);

	// get results
	cout << argparser.get<string>("word");
	cout << argparser.get<string>("char");
	cout << argparser.get<char>("head");
	cout << argparser.get<char>("tail");
	cout << argparser.get<int>("num");
	// argument parsing finished
	//volatil11

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
	int word_count = 0;;
	start_char = 0;
	string temp_string=string();
	infile.open("test.txt", ios::in);
	if (!infile.is_open())
		cout << "Open file failure" << endl;
	infile >> noskipws;
	while (!infile.eof())   
	{
		infile >> temp_char;
		if (temp_char >= 65 && temp_char <= 90)
			temp_char = temp_char + 32;
		if (temp_char >= 97 && temp_char <= 122) {
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
	//����1
	int length1 = 0;
	int max_length = 0;
	vector<int> result;
	vector<int> temp_result;

	//int n = most_word(1, 0, length1, max_length , 0, 0, WordMatrix, result, temp_result);
	int n = most_char (1, 0, length1, max_length, 1, 14, WordMatrix, result, temp_result);

	printf("ans:%d\n", max_length);
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

