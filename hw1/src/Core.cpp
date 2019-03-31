#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "WordNode.cpp"
using namespace std;

class Core {
public:
	static int gen_chain(vector<string> words, vector<string> &result) {
		result.clear();
		if (words.empty()) return 0;	// if input is NULL
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

	static int gen_chain_char(vector<string> words, vector<string> &result) {
		result.clear();
		if (words.empty()) return 0;	// NULL input
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

	static int gen_chain_word(vector<string> words, vector<string> &result, char head, char tail) {
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
		int head_int;
		if (head) head_int = head - 'a' + 1;
		else head_int = 0;
		int tail_int;
		if (tail) tail_int = tail - 'a' + 1;
		else tail_int = 0;
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

	static void gen_chain_n_word(vector<string> words, int num, ofstream &outfile) {
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
		vector<string> temp_result;
		n_word(1, 0, length, num, n, WordMatrix, temp_result, outfile);
	}
private:	
	static int most_word(int if_start, int start, int &length ,int &max_length, int start_char, int end_char, WordNode num_matrix[][26], vector<int> &result, vector<int> &temp_result) {
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

	static int most_char(int if_start, int start, int &length, int &max_length, int start_char, int end_char, WordNode num_matrix[][26], vector<int> &result, vector<int> &temp_result) {
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

	
	static void n_word(int if_start, int start, int &length, int n_length, int &n, WordNode num_matrix[][26], vector<string> &temp_result, ofstream &outfile) {
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
						outfile << (*it) << " ";
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

};