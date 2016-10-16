#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char from[15][25],to[15][25],a[25],b[25],froml[15],tol[15];
int ttop=0;
struct trie{
	trie *son[26];
	int val;
	trie(){
		for(int i=0;i<26;i++){
			son[i]=this;
		}
		val=0;
	}
	void insert(char *s,int v){
		if((*s)==0){
			val=v;
			return;
		}
		if(son[(*s)-'a']==this){
			son[(*s)-'a']=new trie();
		}
		son[(*s)-'a']->insert(s+1,v);
	}
	int check(char *s){
		if((*s)==0){
			return val;
		}
		if(son[(*s)-'a']==this){
			return 0;
		}
		return son[(*s)-'a']->check(s+1);
	}
}root;
bool match(char *sub,char *tem){
	for(;(*sub)&&(*tem);sub++,tem++){
		if((*sub)!=(*tem)){
			return false;
		}
	}
	return (*tem)==0;
}
bool dfs(char *s,int rest){
	if(strcmp(s,b)==0){
		return true;
	}
	if(rest==0){
		return false;
	}
	if(root.check(s)>=rest){
		return false;
	}
	rest--;
	for(int i=0;s[i];i++){
		for(int j=0;j<ttop;j++){
			if(match(s+i,from[j])){
				char *c=new char[25];
				for(int k=0;k<i;k++){
					c[k]=s[k];
				}
				int k;
				for(k=0;to[j][k];k++){
					c[k+i]=to[j][k];
				}
				k+=i;
				for(int l=i+froml[j];s[l];l++,k++){
					c[k]=s[l];
				}
				c[k]=0;
				if(dfs(c,rest)){
					return true;
				}
				delete[] c;
			}
		}
	}
	root.insert(s,rest);
	return false;
}
int main(){
	cin>>a>>b;
	for(;cin>>from[ttop]>>to[ttop];ttop++){
		froml[ttop]=strlen(from[ttop]);
		tol[ttop]=strlen(to[ttop]);
	}
	for(int i=0;i<=10;i++){
		if(dfs(a,i)){
			cout<<i;
			return 0;
		}
	}
	cout<<"NO ANSWER!";
}
