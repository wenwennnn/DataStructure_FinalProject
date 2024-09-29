#define FILE_EXTENSION ".txt"
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<unordered_map>
#include<iostream>

using namespace std;

class trie{
public:
	class node{
	public:
		node();
		node(int);
		~node();
		int depth;
		bool isword;
		unordered_map<char, node*> child;
	};
	
	trie();
	void insert(string);
	bool search(string);
	void remove(string);
	void remove_start_with(string);
	//vector<string> list_start_with(string);

private:
	node* root;
};

trie::node::node(){
	depth=0;
	isword=false;
	child=unordered_map<char, node*>();
}
trie::node::node(int depth): depth(depth) {
    isword = false;
    child = unordered_map<char, node*>();
}
trie::node::~node() {
    for (std::pair<char, node*> pair : child) {
        delete pair.second;
    }
}
trie::trie() {
    root = new node();
}
void trie::insert(string word){
	node* n=root;
	for(char c:word){
		if(n->child.find(c)==n->child.end()){
			n->child[c]=new node(n->depth+1);
		}
		n=n->child[c];
	}
	n->isword=true;
}
bool trie::search(string word){
	node* n=root;
	for(char c:word){
		if(n->child.find(c)==n->child.end()){
			return false;
		}
		n=n->child[c];
	}
	return n->isword;
}
void trie::remove(string word){
	node* n=root;
	for(char c:word){
		if(n->child.find(c)==n->child.end()){
			return;
		}
		n=n->child[c];
	}
	n->isword=false;
}
void trie::remove_start_with(string word){
	node* n=root;
	for(char c:word){
		if(n->child.find(c)==n->child.end()){
			return;
		}
		n=n->child[c];
	}
	for(pair<char, node*> pair:n->child){
		delete pair.second;
	}
	n->child=unordered_map<char, node*>();
	n->isword=false;
}
// vector<string> trie::list_start_with(string word){
// 	node* n=root;
// 	vector<string> list;
// 	for(char c:word){
// 		if(n->child.find(c)==n->child.end()){
// 			return list;
// 		}
// 		n=n->child[c];
// 	}
	
// }

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
	//先將要切割的字串從string型別轉換為char*型別
	char * strs = new char[str.length() + 1] ; //不要忘了
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p; //分割得到的字串轉換為string型別
		res.push_back(s); //存入結果陣列
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

    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);

	// Read File & Parser Example

	string file, title_name, tmp;
	fstream fi;
	fstream fo;
	fstream fq;
	vector<string> tmp_string;
	int num=0;
	vector<string> title;
	
	// fq.open(query,ios::in);
	// while(getline(fq, tmp)){
	// 	vector<string> command = split(tmp, " ");

	// 	//vector<string> qword = word_parse(tmp_string);
	// }
	
	vector<trie> Tnor;
	vector<trie> *Trev;
	//fo.open(output,ios::out);
	cout<<"start:"<<num<<endl;
	while(1){
		trie tn,tr;
		file=data_dir+to_string(num)+".txt";
		//fi.open("data/0.txt", ios::in);
		fi.open(file,ios::in);
		if(!fi.is_open()){
			break;
		}
		// GET TITLENAME
		getline(fi, title_name);

		// GET TITLENAME WORD ARRAY
		tmp_string = split(title_name, " ");

		vector<string> title = word_parse(tmp_string);
		
		// for(auto &word : title){
		// 	//fo<<word<<" ";
		// 	//cout << word << endl;
		// }

		// GET CONTENT LINE BY LINE
		while(getline(fi, tmp)){

			// GET CONTENT WORD VECTOR
			tmp_string = split(tmp, " ");

			// PARSE CONTENT
			vector<string> content = word_parse(tmp_string);
			for(auto &word : content){
				//fo<<word<<"\n";
				tn.insert(word);
				//Tnor.insert(word);
			}
		}

		Tnor.push_back(tn);
        cout << "here\n";
		// CLOSE FILE
		fi.close();
		//fo.close();
		// fq.close();
		cout<<num<<"\n";
		num++;
	}//build trie
	//fo.close();



	// fq.open(query,ios::in);
	// while(getline(fq, tmp)){
	// 	vector<string> command = split(tmp, " ");
		
	// 	//vector<string> qword = word_parse(tmp_string);
	// }
	// fq.close();
	//
}

//./main.exe data query.txt test.txt
// 1. UPPERCASE CHARACTER & LOWERCASE CHARACTER ARE SEEN AS SAME.
// 2. FOR SPECIAL CHARACTER OR DIGITS IN CONTENT OR TITLE -> PLEASE JUST IGNORE, YOU WONT NEED TO CONSIDER IT.
//    EG : "AB?AB" WILL BE SEEN AS "ABAB", "I AM SO SURPRISE!" WILL BE SEEN AS WORD ARRAY AS ["I", "AM", "SO", "SURPRISE"].
// 3. THE OPERATOR IN "QUERY.TXT" IS LEFT ASSOCIATIVE
//    EG : A + B / C == (A + B) / C

//

//////////////////////////////////////////////////////////
// from data_dir get file ....
		// eg : use 0.txt in data directory
		// fq.open(query,ios::in);
		// while(getline(fi, tmp)){

		// 	// GET CONTENT WORD VECTOR
		// 	tmp_string = split(tmp, " ");

		// 	// PARSE CONTENT
		// 	vector<string> qword = word_parse(tmp_string);
		// 	for(auto &word : qword){
		// 		fo<<word<<" ";
		// 	}
		// 	fo<<"\n";
		// }