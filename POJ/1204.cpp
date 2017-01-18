#include <iostream>
#include <cstring>
#include <cstdio>
#include <cassert>
#define L 1010
using namespace std;
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
inline int nextInt(){
	int i=0;char c;
	while(!isNum(c=getchar()));
	for(;isNum(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int ans[L][3];
char mat[L][L],word[L*2];
struct trie{
	int length,ansfor;
	bool end;
	trie *son[26],*fail;
	trie(int depth){
		length=depth;
		for(int i=0;i<26;i++){
			son[i]=this;
		}
	}
	*trie insert(char *s){
		if(s[0]==0){
			end=true;
			return this;
		}
		trie*&to=son[s[0]-'A'];
		if(to==this){
			to=new trie(length+1);
		}
		return to->insert(s+1);
	}
}root(0);
void build(trie* x){
	trie *cur;
	for(int i=0;i<26;i++){
		cur=x->son[i];
		if(cur!=this){
			cur->fail=x->fail;
			while((cur->fail!=&root)&&(cur->fail->son[i]==cur->fail)){
				cur->fail=cur->fail->fail;
			}
			if(cur->fail->son[i]!=cur){
				cur->fail=cur->fail->son[i];
			}
			build(cur);
		}
	}
}
int main(){
	int r=nextInt(),c=nextInt(),w=nextInt();
	for(int i=0;i<r;i++){
		scanf("%s",mat[i]);
	}
	for(int i=0;i<w;i++){
		scanf("%s",word);
		root.insert(word)->ansfor=i;
	}
	root.fail=&root;
	build(&root);
}
