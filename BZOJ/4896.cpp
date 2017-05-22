#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int L=65,TOT=100010,SIGMA=10,N=TOT*2;
struct Query{
	int type,a,b,c,end;
	char s[L];
}qs[TOT];
namespace trie{
	struct node{
		char *l,*r;//[l,r)
		int son[SIGMA];
	}pool[N];
	const int root=1;
	int ntop=1;
	typedef int info[N];
	inline int nn(){
		return ++ntop;
	}
	inline void init(){
		memset(pool,0,sizeof(pool));
		fa[1]=0;
	}
	inline char* endpt(char *s){
		for(;*s;s++);
		return s;
	}
	inline void build(char *s){
		for(int pt=root;;){
			node &cur=pool[pt];
			char *t=cur.l,*r=cur.r;
			assert(t==r||(*t)==(*s));
			for(;t!=r&&(*t)==(*s);t++,s++);
			if(t==r){
				if(*s){
					int &son=cur.son[(*s)-'a'];
					if(son){
						pt=son;
					}else{
						node &np=pool[son=nn()];
						np.l=s,np.r=endpt(s);
						return;
					}
				}else{
					return;
				}
			}else{
				assert((*t)!=(*s));
				int p=nn();
				node &np=pool[p];
				np=cur;
				np.l=t;
				memset(cur.son,0,sizeof(cur.son));
				cur.r=t,cur.son[(*t)-'a']=p;
				if(*s){
					node &np=pool[p=nn()];
					np.l=s,np.r=endpt(s);
				}
				return;
			}
		}
	}
	inline int match(char *s){
		int pt=root;
		for(;*s;pt=pool[pt].son[(*s)-'a'],s+=pool[pt].r-pool[pt].l);
		return pt;
	}
	inline int search(char *s){
		//todo
	}
}
int main(){
	int tot=ni;
	for(int i=1;i<=tot;i++){
		scanf("%d%s",&qs[i].type,qs[i].s);
		if(qs[i].type==3){
			qs[i].a=ni,qs[i].b=ni,qs[i].c=ni;
		}else if(qs[i].type==1){
			trie::build(qs[i].s);
		}
	}
	for(int i=1;i<=tot;i++){
		qs[i].end=qs[i].type==3?trie::search(qs[i].s):trie::match(qs[i].s);
	}
}
