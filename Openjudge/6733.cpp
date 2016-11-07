#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int n,len[105];
string words[105];
struct trie{
	trie* son[26];
	bool end;
	trie(){
		for(int i=0;i<26;i++){
			son[i]=this;
		}
		end=false;
	}
	void insert(const char* s){
		if(s[0]==0){
			end=true;
			return;
		}
		if(son[s[0]-'a']==this){
			son[s[0]-'a']=new trie();
		}
		son[s[0]-'a']->insert(s+1);
	}
	int match(const char* s);
}root;
int trie::match(const char* s){
	if(s[0]==0){
		return end;
	}
	int cnt=0;
	if(end){
		cnt+=root.match(s);
	}
	if(son[s[0]-'a']!=this){
		cnt+=son[s[0]-'a']->match(s+1);
	}
	return cnt;
}
queue<string>q;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>words[i];
		len[i]=words[i].length();
		root.insert(words[i].c_str());
	}
	sort(words,words+n);
	for(int i=0;i<n;i++){
		q.push(words[i]);
	}
	while(!q.empty()){
		string s=q.front();
		q.pop();
		if(root.match(s.c_str())>1){
			cout<<s;
			return 0;
		}
		for(int i=0;i<n;i++){
			q.push(s+words[i]);
		}
	}
}
