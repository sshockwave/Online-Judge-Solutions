#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <vector>
using namespace std;
typedef long long lint;
typedef double db;
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
typedef vector<int>vi;
const int N=12,SN=1<<N;
const db EPS=1e-8;
struct State{
	int n;
	struct state{
		int i,s;
		db v;
	};
	vector<state>vec;
	inline void add(int i,int s,db v){
		vec.push_back((state){i,s,v});
	}
	inline void putvec(db f[SN][N]){
		for(vector<state>::iterator it=vec.begin();it!=vec.end();it++){
			f[it->s][it->i]=it->v;
		}
	}
	inline db grabans(){
		vector<state>::iterator it=vec.begin();
		for(;it->i;it++);
		return it->v;
	}
};
int n,sn;
int bitcnt[SN];
db f1[SN][N],f2[SN][N];
vector<int>subset[SN][N];
int a[N];
namespace T{
	const int N=::N<<2;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
	}pool[N],*ps;
	inline State dp(node x){
		if(x->lson==pool&&x->rson==pool){
			State s;
			s.n=1;
			for(int i=0;i<n;i++){
				s.add(i,0,1);
			}
			return s;
		}
		State ls=dp(x->lson),rs=dp(x->rson);
		ls.putvec(f1),rs.putvec(f2);
		State st;
		st.n=ls.n+rs.n;
		vi &vec=subset[sn-1][st.n-1];
		for(vi::iterator it=vec.begin();it!=vec.end();it++){
			int s=*it;
			for(int x=0;x<n;x++){//winner
				if((s>>x)&1)continue;
				vi &subvec=subset[s][ls.n-1];
				db ans=0;
				for(vi::iterator it2=subvec.begin();it2!=subvec.end();it2++){
					int s1=*it2;
					for(int y=0;y<n;y++){//loser
						if((((s^s1)>>y)&1)==0)continue;
						int s2=s^s1^(1<<y);
						ans+=(f1[s1][x]*f2[s2][y]+f1[s1][y]*f2[s2][x])*((db)a[x]/(a[x]+a[y]));
					}
				}
				st.add(x,s,ans);
			}
		}
		return st;
	}
	inline node gen_rnd(int sz){
		node x=++ps;
		if(sz==1)return x->lson=x->rson=pool,x;
		int lsize=rand()%(sz-1)+1,rsize=sz-lsize;
		x->lson=gen_rnd(lsize),x->rson=gen_rnd(rsize);
		return x;
	}
	inline node gen_seg(int n){
		node x=++ps;
		if(n==1)return x->lson=x->rson=pool,x;
		x->lson=gen_seg(n>>1);
		x->rson=gen_seg(n-(n>>1));
		return x;
	}
	inline node gen_cha(int n){
		node x=++ps;
		if(n==1)return x->lson=x->rson=pool,x;
		x->lson=gen_cha(n-1);
		x->rson=gen_cha(1);
		return x;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	n=ni,sn=1<<n;
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	for(int s=0;s<sn;s++){
		bitcnt[s]=s?bitcnt[s^(s&-s)]+1:0;
		for(int t=s;t;t=(t-1)&s){
			subset[s][bitcnt[t]].push_back(t);
		}
		subset[s][0].push_back(0);
	}
	using T::node;
	T::ps=T::pool;
	node seg=T::gen_seg(n),cha=T::gen_cha(n);
	for(int l=1,r=1000,&m=a[0];m=(l+r)>>1,l<r;){
		db segv=T::dp(seg).grabans(),chav=T::dp(cha).grabans();
		if(segv>chav){
			r=m;
		}else if(segv<chav){
			l=m+1;
		}else break;
	}
	db mx=max(T::dp(seg).grabans(),T::dp(cha).grabans());
	node res;
	while(T::ps=T::pool,T::dp(res=T::gen_rnd(n)).grabans()<mx+EPS);
	puts("1");
	printf("1 %d\n",a[0]);
	for(int i=1;i<=T::ps-T::pool;i++){
		printf("%ld %ld\n",T::pool[i].lson-T::pool,T::pool[i].rson-T::pool);
	}
	return 0;
}
