#include <vector>
#include <string>
#include "WordNode.cpp"
using namespace std;

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