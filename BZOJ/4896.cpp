#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
inline int abs(int x){
	return x>=0?x:-x;
}
const int L=65,SIGMA=26,N=100010;
char s[L];
struct Trie{
	typedef Trie* node;
	int val;
	vector<int>q;
	node son[SIGMA];
	Trie(){
		memset(son,0,sizeof(son));
		q.push_back(0);
		val=0;
	}
	inline void update(int id){
		val++;
		if(val==q.size()){
			q.push_back(id);
			assert(q[val]==id);
		}
	}
	inline node go(int c){
		c-='a';
		if(son[c]==0){
			son[c]=new Trie();
		}
		return son[c];
	}
	inline void insert(char *s,int id){
		for(node pt=this;pt->update(id),*s;pt=pt->go(*s),s++);
	}
	inline void del(char *s){
		for(node pt=this;pt->val--,*s;pt=pt->son[(*s)-'a'],s++);
	}
	inline node find(char *s){
		node pt=this;
		for(;*s;pt=pt->son[(*s)-'a'],s++);
		return pt;
	}
}trie;
inline int work(Trie *pt,int ans){
	lint a=nl,b=nl,c=nl;
	lint x=(a*abs(ans)+b)%c+1;
	if(pt->q.size()<=x){
		return -1;
	}
	return pt->q[x];
}
int main(){
	int ans=0;
	for(int i=1,n=ni;i<=n;i++){
		int k=ni;
		scanf("%s",s);
		if(k==1){
			trie.insert(s,i);
		}else if(k==2){
			trie.del(s);
		}else{
			assert(k==3);
			printf("%d\n",ans=work(trie.find(s),ans));
		}
	}
}
