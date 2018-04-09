#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int D=4,N=50010,sqrtN=250;
int tim=0;
namespace PAM{
	const int N=::N;
	struct Node;
	typedef Node* node;
	struct Node{
		node lnk,go[D],go2[D];
		int len,tag;
		inline node ins(int);
	}pool[N],Null,mir[N];
	node null=&Null,pol;
	inline node nn(node x=null){
		static node &n=pol;
		return *n=*x,n++;
	}
	inline node gmir(node x){
		if(x->tag==-1)return x;
		node y=x-pool+mir;
		if(x->tag<tim){
			x->tag=tim;
			*y=x<pol?*x:Null,y->tag=-1;
		}
		return y;
	}
	inline void reset(){
		pol=pool+2;
		pool[0]=pool[1]=Null;
		pool[0].lnk=pool+1;
		pool[0].len=0,pool[1].len=-1;
		for(int i=0;i<D;i++){
			pool[0].go2[i]=pool+1;
		}
	}
	inline void init(){
		Null.lnk=pool;
		for(int i=0;i<D;i++){
			Null.go[i]=Null.go2[i]=pool;
		}
	}
}
inline int charmap(char c){
	switch(c){
		case 'A':return 0;
		case 'T':return 1;
		case 'C':return 2;
		case 'G':return 3;
	}
	return -1;
}
char s[N];
inline PAM::node ins_right(int i,PAM::node x,int lend){
	using namespace PAM;
	int c=charmap(s[i]);
	x=i-x->len-1>=lend&&s[i-x->len-1]==s[i]?x:x->go2[c];
	if(x->go[c]==pool){
		node y=nn();
		y->len=x->len+2;
		y->lnk=x->go2[c]->go[c];
		int p=i+1-y->lnk->len-1;
		if(p>=lend){
			p=charmap(s[p]);
			for(int j=0;j<D;j++){
				y->go2[j]=p==j?y->lnk:y->lnk->go2[j];
			}
		}
		x->go[c]=y;
	}
	return x->go[c];
}
struct pii{
	int l,r,id;
	inline friend bool operator < (const pii &a,const pii &b){
		return a.r<b.r;
	}
};
vector<pii>qry[sqrtN];
int rt;
int ans[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("palin.in","r",stdin);
	freopen("palin.out","w",stdout);
#endif
	int n=ni,tot=ni;
	rt=sqrt(n);
	scanf("%s",s+1);
	PAM::init();
	for(int i=1;i<=tot;i++){
		pii a=(pii){ni,ni,i};
		int bl=a.l/rt,br=a.r/rt;
		if(bl==br){
			using namespace PAM;
			reset();
			node x=pool;
			for(int j=a.l;j<=a.r;j++){
				x=ins_right(j,x,a.l);
			}
			ans[i]=pol-pool-2;
		}else{
			qry[bl].push_back(a);
		}
	}
	for(int b=0,tb=n/rt;b<=tb;b++){
		if(qry[b].empty())continue;
		sort(qry[b].begin(),qry[b].end());
		using namespace PAM;
		reset();
		int bl=b*rt,br=bl+rt;
		node lnd=pool,rnd=pool;
		int curr=br;
		for(vector<pii>::iterator it=qry[b].begin(),ti=qry[b].end();it!=ti;it++){
			if(curr<=it->r){
				node &x=rnd;
				for(int &i=curr;i<=it->r;i++){
					x=ins_right(i,x,br);
					if(x->len==curr-br+1){
						lnd=x;
					}
				}
			}
			{
				tim++;
				node pol2=pol,x=gmir(lnd);
				for(int i=br-1;i>=it->l;i--){
					int c=charmap(s[i]);
					x=gmir(i+x->len+1<curr&&s[i+x->len+1]==s[i]?x:x->go2[c]);
					if(x->go[c]==pool){
						node y=gmir(pol2++);
						y->len=x->len+2;
						y->lnk=gmir(gmir(x->go2[c])->go[c]);
						int p=i-1+y->lnk->len+1;
						if(p<curr){
							p=charmap(s[p]);
							for(int j=0;j<D;j++){
								y->go2[j]=gmir(p==j?y->lnk:y->lnk->go2[j]);
							}
						}
						x->go[c]=y;
					}
					x=gmir(x->go[c]);
				}
				ans[it->id]=pol2-pool-2;
			}
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
