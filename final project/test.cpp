#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<map>

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

		for(auto child = word.begin(); child != word.end(); ++child){
			if(cur->children[(*child)-'a'] == nullptr){
				struct TrieNode* new_child = new TrieNode();
				cur->children[(*child) - 'a'] = new_child;
			}
			cur = cur->children[(*child)-'a'];
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
		for(auto child : word){
			if(cur->children[child-'a'] == nullptr){
				return false;
			}
			cur = cur->children[child-'a'];
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
		//bool inverse_end;
		vector<TrieNode*> children;
		//vector<TrieNode*> inverse_children;


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

int main()
{
    Trie* now = new Trie;

    now->insert("string");
}