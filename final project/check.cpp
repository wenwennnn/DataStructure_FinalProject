#define FILE_EXTENSION ".txt"
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<map>
#include<ctime>

using namespace std;

class Trie{
	public : 

	Trie(){
		root = new TrieNode();
		inverse_root = new TrieNode();
	}

	void insert(string word){
		TrieNode* cur = root;
		TrieNode* re = inverse_root;
		//cout << "in\n";

		for(auto child : word){
			if(cur->children[child-'a'] == nullptr){
				struct TrieNode* new_child = new TrieNode();
				cur->children[child - 'a'] = new_child;
			}
			cur = cur->children[child-'a'];
		}
		cur->end = true;

		for (int i = word.length() - 1; i >= 0; i--) {
			if(re->children[word[i]-'a'] == nullptr){
				struct TrieNode* new_one = new TrieNode();
				re->children[word[i] - 'a'] = new_one;
			}
			re = re->children[word[i]-'a'];
		}
		re->end = true;

		//cout << "out\n";
	}

	bool suffix_search(string word){
		TrieNode* cur = inverse_root;
		for(int i = word.length()-1; i>= 0;i--){
			if(cur->children[word[i]-'a'] == nullptr){
				return false;
			}
			cur = cur->children[word[i]-'a'];
		}
		return true;
	}

	bool exact_search(string word){
		TrieNode* cur = root;
		for(auto child : word){
			if(cur->children[child-'a'] == nullptr){
				return false;
			}
			cur = cur->children[child-'a'];
		}
		return cur->end;
	}

	bool prefix_search(string word){
		TrieNode* cur = root;
		for(auto child : word){
			if(cur->children[child-'a'] == nullptr){
				return false;
			}
			cur = cur->children[child-'a'];
		}
		return true;
	}

	private : 

	struct TrieNode{
		bool end;
		vector<TrieNode*> children;

		TrieNode(){
			end = false;
			children = vector<TrieNode*>(26, nullptr);
			//inverse_children = vector<TrieNode*>(26, nullptr);
		}
		~TrieNode(){
			for(auto child:children){
				if(child) delete child;
			}
			// for(auto child:inverse_children){
			// 	if(child) delete child;
			// }
		}
	};
	struct TrieNode* root;
	struct TrieNode* inverse_root;
};

// Utility Func

// string parser : output vector of strings (words) after parsing
// 只保留字母 清除不必要元素
vector<string> word_parse(vector<string> tmp_string){
	vector<string> parse_string;
	for(auto& word : tmp_string){
		string new_str;
    	for(auto &ch : word){
			if(isalpha(ch))
				new_str.push_back(ch);
		}
		parse_string.emplace_back(new_str);
	}
	return parse_string;
}

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	//先將要切割的字串從string型別轉換為char*型別
	char * strs = new char[str.length() + 1] ; //不要忘了
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d); //將結果持續分割
	while(p) {
		string s = p; //分割得到的字串轉換為string型別
		
		transform(s.begin(), s.end(), s.begin(), ::tolower);

		res.push_back(s); //存入結果陣列
		p = strtok(NULL, d);
	}

	return res;
}


int main(int argc, char *argv[])
{
	clock_t start = clock();
    // INPUT :
	// 1. data directory in data folder
	// 2. number of txt files
	// 3. output route

    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);

	// Read File & Parser Example

	string file, title_name, tmp;
	fstream fi;
	vector<string> tmp_string;
	vector<Trie> all_file;
	vector<string> title;

	int j=0;

	while(1){
		//cout << i << "\n";
		//fstream fi;
		vector<string> tmp_string;

		stringstream ss;
    	ss << data_dir << j << ".txt";
	
    	string filename = ss.str();
		//cout << filename << endl;
    	ifstream fi;
    	fi.open(filename, ios::in);

		if(!fi.is_open()) break;

		Trie* now = new Trie;

		// from data_dir get file ....
		// eg : use 0.txt in data directory
		//fi.open("data/0.txt", ios::in);

		// GET TITLENAME
		getline(fi, title_name);

		//cout << title_name << endl;

		title.push_back(title_name);

		// GET TITLENAME WORD ARRAY
		tmp_string = split(title_name, " ");

		vector<string> title_tmp = word_parse(tmp_string);

		for(auto &word : title_tmp){
			//cout << word << endl;
			now->insert(word);
		}

		int integer = 0;
		// GET CONTENT LINE BY LINE
		while(getline(fi, tmp)){

			//cout << integer << "\n";
			integer ++;

			// GET CONTENT WORD VECTOR
			tmp_string = split(tmp, " ");

			// PARSE CONTENT
			vector<string> content = word_parse(tmp_string);

			for(auto &word : content){
				//cout << word << endl;
				now->insert(word);
			}
			//......
			//cout << "here\n";
		}

		// CLOSE FILE
		fi.close();
		all_file.push_back(*now);
		j++;
	}

	//ifstream fi;
	fi.open(query,ios::in);
	vector<string> ans;

	while(getline(fi,tmp)){

		//cout << "hihi" << endl;

		transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

		vector<string> content = split(tmp, " ");

		vector<string>::iterator it;
		//vector<string>::iterator tmp;

		int i=0;
		int have_ans = 0;
		for(auto &data : all_file){
			int isans = 1;
			int tmpans;
			int oper = 0; // 1 = +  // 2 = /
			for(it = content.begin(); it != content.end(); it++){
				//cout << (*it) << endl;
				if((*it)[0] == '*'){
					string tmp = *it;
					tmp.erase(0,1);
					tmp.erase(tmp.end()-1, tmp.end());
					tmpans = data.suffix_search(tmp);

					if(oper == 0) isans = tmpans;
					else if(oper == 1) isans = isans && tmpans;
					else isans = isans || tmpans;
				}
				else if((*it)[0] == '"'){
					string tmp = *it;
					tmp.erase(0,1);
					tmp.erase(tmp.end()-1, tmp.end());
					tmpans = data.exact_search(tmp);

					if(oper == 0) isans = tmpans;
					else if(oper == 1) isans = isans && tmpans;
					else isans = isans || tmpans;
				}
				else if((*it)[0] == '+'){
					oper = 1;
				}
				else if((*it)[0] == '/'){
					oper = 2;
				}
				else{
					tmpans = data.prefix_search((*it));

					if(oper == 0) isans = tmpans;
					else if(oper == 1) isans = isans && tmpans;
					else isans = isans || tmpans;
				}
			}

			if(isans){
				ans.push_back(title.at(i));
				have_ans = 1;
			}

			i++;
		}
		if(!have_ans) ans.push_back("Not Found!");
	}
	fi.close();

	// for(auto &a : ans){
	// 	cout << a << "\n";
	// }

	fstream out_f;
	out_f.open(output, ios::out);

	//cout << ans.size() << endl;

	if(ans.empty()) out_f << "Not Found!" << "\n";
	else{
		for(auto &a : ans){
			out_f << a << "\n";
		}
	}
	out_f.close();
    cout << "out\n";
    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;	
    cout << "time : " << duration << "s" << "\n";
 
}

// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C

//

//////////////////////////////////////////////////////////
