#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010,D=4;
namespace pam{
	struct Node;
	typedef Node* node;
	struct Node{
		node lnk,go[D];
		int len,dep;
	}pool[N];
	node rt;
	inline node nn(node x=pool){
		static node n=pool;
		*n=*x;
		n->lnk=pool;
		for(int i=0;i<D;i++){
			n->go[i]=pool;
		}
		return n++;
	}
	inline void init(){
		rt=nn();
		rt->len=rt->dep=0;
		rt->lnk=nn();
		rt->lnk->len=-1;
	}
}
int s[N<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("algebra.in","r",stdin);
	freopen("algebra.out","w",stdout);
#endif
	pam::init();
	int l=N,r=N-1;
	pam::node lend=pam::rt->lnk,rend=pam::rt->lnk;
	lint cnt=0,uniqcnt=0;
	memset(s,-1,sizeof(s));
	for(int tot=ni;tot--;){
		static char tmp[20];
		scanf("%s",tmp);
		int c;
		while(!isalpha(c=getchar()));
		c-='a';
		if(tmp[0]=='l'){//insert left
			s[--l]=c;
			for(;c!=s[l+lend->len+1];lend=lend->lnk);
			if(lend->go[c]==pam::rt){
				++uniqcnt;
				pam::node x=pam::nn();
				x->len=lend->len+2;
				pam::node y=lend->lnk;
				for(;c!=s[l+y->len+1];y=y->lnk);
				x->lnk=y->go[c];
				x->dep=x->lnk->dep+1;
				lend->go[c]=x;
			}
			lend=lend->go[c];
			cnt+=lend->dep;
			if(lend->len==r-l+1){
				rend=lend;
			}
		}else{//insert right
			s[++r]=c;
			for(;c!=s[r-rend->len-1];rend=rend->lnk);
			if(rend->go[c]==pam::rt){
				++uniqcnt;
				pam::node x=pam::nn();
				x->len=rend->len+2;
				pam::node y=rend->lnk;
				for(;c!=s[r-y->len-1];y=y->lnk);
				x->lnk=y->go[c];
				x->dep=x->lnk->dep+1;
				rend->go[c]=x;
			}
			rend=rend->go[c];
			cnt+=rend->dep;
			if(rend->len==r-l+1){
				lend=rend;
			}
		}
		printf("%lld %lld\n",cnt,uniqcnt);
	}
	return 0;
}
