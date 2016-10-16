#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char from[15][25],to[15][25],a[25],b[25],froml[15],tol[15];
int ttop=0;
struct trie{
	struct chain{
		trie *son;
		chain *next;
		char c;
	};
	chain *head;
	int val;
	trie(){
		head=0;
		val=0;
	}
	chain* find(chain *&p,char c){
		if(p==0){
			p=new chain();
			p->c=c;
			p->next=0;
			p->son=new trie();
			return p;
		}
		if(p->c==c){
			return p;
		}else{
			return find(p->next,c);
		}
	}
	void insert(char *s,int v){
		if((*s)==0){
			val=v;
			return;
		}
		find(head,*s)->son->insert(s+1,v);
	}
	int check(char *s){
		if((*s)==0){
			return val;
		}
		return find(head,*s)->son->check(s+1);
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
