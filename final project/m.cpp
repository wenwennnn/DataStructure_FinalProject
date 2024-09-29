#define FILE_EXTENSION ".txt"
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<ctime>

using namespace std;

class TrieNode {
 public:
  TrieNode() {
    is_end = false;
    for (int i = 0; i < 26; i++) {
      children[i] = nullptr;
    }
  }
  bool is_end;
  TrieNode* children[26];
};

class Trie {
 public:
  Trie() {
    root = new TrieNode();
    inv_root = new TrieNode(); 
  }

  void Insert(string word) {
    TrieNode* cur = root;
	TrieNode *inv = inv_root;
    for (int i = 0; i < word.size(); i++) {
      int index = word[i] - 'a';
      if (cur->children[index] == nullptr) {
        cur->children[index] = new TrieNode();
      }
      cur = cur->children[index];
    }
    cur->is_end = true;

	for (int i = word.size() - 1; i >= 0; i--) {
      int index = word[i] - 'a';
      if (inv->children[index] == nullptr) {
        inv->children[index] = new TrieNode();
      }
      inv = inv->children[index];
    }
    inv->is_end = true;
  }

//   void inv_Insert(string word) {
//     TrieNode* cur = inv_root;
// 	reverse(word.begin(), word.end());
//     for (int i = 0; i < word.size(); i++) {
//       int index = word[i] - 'a';
//       if (cur->children[index] == nullptr) {
//         cur->children[index] = new TrieNode();
//       }
//       cur = cur->children[index];
//     }
//     cur->is_end = true;
//   }
  
  bool Exact(string word){
  	TrieNode* cur = root;
    for (int i = 0; i < word.size(); i++) {
      int index = word[i] - 'a';
      if (cur->children[index]) {
        cur = cur->children[index];
      }
      else return 0;
    }
    if(cur->is_end){
    	return 1;
	}
	else return 0;
  }
  
  bool Prefix(string word){
  	TrieNode* cur = root;
    for (int i = 0; i < word.size(); i++) {
      int index = word[i] - 'a';
      if (cur->children[index]) {
        cur= cur->children[index];
      }
      else return 0;
    }
    return 1;
  }

  bool Suffix(string word){
  	TrieNode* cur = inv_root;
	reverse(word.begin(), word.end());
	cout << "search word:"<< word<<endl;
    for (int i = 0; i < word.size(); i++) {
      int index = word[i] - 'a';
	  //cout << "i: "<<i<<" <<   index  "<<index<<endl;
      if (cur->children[index]==nullptr) {
		return 0;
        //cur= cur->children[index];
      }
      cur= cur->children[index];
    }
    return 1;
  }
  
  TrieNode* root;
  TrieNode* inv_root;
};

//Trie construct
//	Trie tree;
//	tree.root = r;
vector<Trie> tree;
vector<string> title_str;

// Utility Func

// string parser : output vector of strings (words) after parsing
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
	//嚙踝蕭嚙瞇嚙緯嚙踝蕭嚙諄迎蕭嚙緝嚙踝蕭qstring嚙踝蕭嚙瞌嚙賞換嚙踝蕭char*嚙踝蕭嚙瞌
	char * strs = new char[str.length() + 1] ; //嚙踝蕭嚙緯嚙諸了
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p; //嚙踝蕭嚙諄得嚙趣的嚙緝嚙踝蕭嚙賞換嚙踝蕭string嚙踝蕭嚙瞌
		res.push_back(s); //嚙編嚙皚嚙踝蕭嚙瘦嚙罷嚙瘠
		p = strtok(NULL, d);
	}

	return res;
}




int main(int argc, char *argv[])
{

    // INPUT :
	// 1. data directory in data folder
	// 2. number of txt files
	// 3. output route
	clock_t start = clock();
    string data_dir = argv[1] + string("/");
	string query = string(argv[2]) + string("/") + string("query.txt");
	string output = string(argv[3]);

	// Read File & Parser Example


	string file, title_name, tmp;
	fstream fi;
	ofstream out_file;
	vector<string> tmp_string;
	int i = 0;
 

	// from data_dir get file ....
	while(1){
		string openstr;
		openstr = "data/"+to_string(i)+".txt";
		fi.open(openstr, ios::in);
		i++;
		// GET TITLENAME
		
		if(!getline(fi, title_name))break;
		
		title_str.push_back(title_name);
		
		// GET TITLENAME WORD ARRAY
    	tmp_string = split(title_name, " ");
		vector<string> title = word_parse(tmp_string);
		Trie new_trie;
		//construct title words in trie
		for(auto &word : title){
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			new_trie.Insert(word);
			//new_trie.inv_Insert(word);
		}

    	// GET CONTENT LINE BY LINE
		while(getline(fi, tmp)){

        	// GET CONTENT WORD VECTOR
			tmp_string = split(tmp, " ");

			// PARSE CONTENT
			vector<string> content = word_parse(tmp_string);
			for(auto &word : content){
				transform(word.begin(), word.end(), word.begin(), ::tolower);
				new_trie.Insert(word);
				//new_trie.inv_Insert(word);
			}
		}
    	// CLOSE FILE
		tree.push_back(new_trie);
		fi.close();
	}
	//cout<<"tree size:"<<tree.size()<<endl;

	///////////////////////////////嚙諍改蕭嚙瘠嚙篇嚙論文的Trie嚙璀嚙罷嚙締嚙篌嚙踝蕭query///////////////////////////////////////////////
	// vector<int> ans;
	fi.open("query.txt", ios::in);
	while(getline(fi,tmp)){
		vector<int> ans;
		cout << "tmp:"<<tmp<<endl;
		tmp_string = split(tmp, " ");
		int cnt = 0;
		
		for(auto &art : tree){
			int flag_and = 0;
			int flag_or = 0;
			int flag_isans = 0;
			for(auto &que : tmp_string){
				if(que[0]=='+'){
					flag_and = 1;
					flag_or = 0;
				}
				else if(que[0]=='/'){
					flag_and = 0;
					flag_or = 1;
				}

				else if(que[0] == '"'){
					que.erase(std::remove(que.begin(), que.end(), '"'), que.end());
					transform(que.begin(), que.end(), que.begin(), ::tolower);
					bool find_exact = art.Exact(que);
					if(flag_and)flag_isans = flag_isans && find_exact;
					else if(flag_or)flag_isans = flag_isans || find_exact;
					else flag_isans = find_exact;
				} 

				else if(que[0] == '*'){
					que.erase(std::remove(que.begin(), que.end(), '*'), que.end());
					transform(que.begin(), que.end(), que.begin(), ::tolower);
					bool find_exact = art.Suffix(que);
					if(flag_and)flag_isans = flag_isans && find_exact;
					else if(flag_or)flag_isans = flag_isans || find_exact;
					else flag_isans = find_exact;
				} 

				else if(isalpha(que[0])){
					transform(que.begin(), que.end(), que.begin(), ::tolower);
					bool find_prefix = art.Prefix(que);
					if(flag_and)flag_isans = flag_isans && find_prefix;
					else if(flag_or)flag_isans = flag_isans || find_prefix;
					else flag_isans = find_prefix;
				} 
			}

			if(flag_isans)ans.push_back(cnt);
			cnt++;
		}
		cout << "ans: "<<endl;
		out_file.open(output, std::ios::out);
		if(ans.size()==0){
			cout << "Not Found!"<<endl;
			out_file << "Not Found!"<<endl;
		}
		else{
			for(auto c : ans){
				//cout << c << endl;

				cout << title_str[c] << endl;
				out_file << title_str[c] << endl;
			}	
		}
    	out_file.close();
		cout << "ans finish" << endl;
		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	fi.close();	

	//time count
	clock_t stop = clock();
    double duration = (stop - start) / static_cast<double>(CLOCKS_PER_SEC);
    std::cout << "Duration: " << duration << " seconds" << std::endl;
}


// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C

//

//////////////////////////////////////////////////////////
