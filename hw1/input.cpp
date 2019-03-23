#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class WordNode{
    public:
        char prefix;
        char suffix;
        vector <string> wordlist;
        int wordcount;
        int wordmaxlength;

}

int most_word(int if_start, int start, int &length ,int &max_length, int num_matrix[][26], vector<int> &result, vector<int> &temp_result) {
	if (if_start == 1) {
		int n = 0;
		int best_i;
		for (int i = 0; i < 26; i++) {
			temp_result.clear();
			temp_result.push_back(i);
			int temp = most_word(0, i, length, max_length, num_matrix, result, temp_result);
			if (temp > n) {
				n = temp;
			}
		}
		return n;
	}
	int n = 0;
	int best_i;
	for (int i = 0; i < 26; i++) {
		if (num_matrix[start][i] > 0) {
			num_matrix[start][i]--;
			length++;
			temp_result.push_back(i);
			if (length > max_length) {
				max_length = length;
				printf("%d\n", max_length);
				result.clear();
				result.assign(temp_result.begin(), temp_result.end());
			}
			if (length > max_length);
			int temp = most_word(0, i, length, max_length, num_matrix, result, temp_result)+1;
			if (temp > n) {
				n = temp;
			}
			temp_result.pop_back();
			length--;
			num_matrix[start][i]++;
		}
	}
	return n;
}

int main() {

	int num_matrix[26][26] = { 0 };
	vector<string> word_matrix[26][26];

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
				for (vector<string>::iterator it = word_matrix[start_index][end_index].begin(); it != word_matrix[start_index][end_index].end(); it++)
				{
					//cout << "test: " << temp_string << *it << temp_string.compare(*it)  << endl;
					if (temp_string.compare(*it) == 0)
						if_repeat = true;
				}
				if (!if_repeat) {
					word_matrix[start_index][end_index].push_back(temp_string);
					word_count++;
					num_matrix[start_index][end_index]++;
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
			 for (vector<string>::iterator it = word_matrix[i][j].begin(); it != word_matrix[i][j].end(); it++)
			 {
				cout << *it << endl;
			 }
		}
	}

	//����1
	int length1 = 0;
	int max_length = 0;
	vector<int> result;
	vector<int> temp_result;

	int n = most_word(1, 0, length1, max_length , num_matrix, result, temp_result);

	printf("ans:%d\n", n);
	for (vector<int>::iterator it = result.begin(); it != result.end()-1; it++)
	{
		cout << *it << endl;
		cout << word_matrix[*it][*(it + 1)][num_matrix[*it][*(it + 1)] - 1] << endl;
		num_matrix[*it][*(it + 1)]--;
	}

	infile.close(); 
	getchar();
}

