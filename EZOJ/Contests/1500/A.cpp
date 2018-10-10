#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1000010,INF=0x7f7f7f7f;
inline int sig(const int x){
	return x>0?1:x<0?-1:0;
}
int sum[N],f[N];
namespace qs{
	int pr[N*3],nx[N*3];
	//Base
	inline void init(int n){
		for(int i=-n;i<=n;i++){
			int x=i+N*2;
			pr[x]=nx[x]=x;
		}
	}
	inline void del(int x){
		nx[pr[x]]=nx[x],pr[nx[x]]=pr[x];
	}
	inline void ins(int u,int v){
		pr[v]=u,nx[v]=nx[u];
		nx[pr[v]]=pr[nx[v]]=v;
	}
	inline int front(int qid){
		qid+=N*2;
		return nx[qid];
	}
	inline int back(int qid){
		qid+=N*2;
		return pr[qid];
	}
	inline bool empty(int qid){
		qid+=N*2;
		return nx[qid]==qid;
	}
	//util
	inline void pop_until(int qid,int x){
		for(;!empty(qid)&&front(qid)<x;del(front(qid)));
	}
	inline void stk_ins(int qid,int x){
		for(;!empty(qid)&&sum[back(qid)]>=sum[x];del(back(qid)));
		ins(pr[qid+N*2],x);
	}
	inline void print(int qid){
		cout<<"que["<<qid<<"]:";
		qid+=N*2;
		for(int i=nx[qid];i!=qid;i=nx[i]){
			cout<<"{"<<i<<",sum="<<sum[i]<<"}";
		}
		cout<<endl;
	}
}
int que[N];
inline void upd(int i,int j){
	apmax(f[i],f[j]+sig(sum[i]-sum[j]));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("election.in","r",stdin);
	freopen("election.out","w",stdout);
#endif
	const int n=ni,lenl=ni,lenr=ni;
	qs::init(n+2);
	f[0]=0,sum[0]=0;
	int qh=0,qt=0;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+ni;
		const int liml=i-lenr;
		for(;qh<qt&&que[qh]<liml;qh++);
		if(i-lenl>=0&&f[i-lenl]>-INF){
			const int j=i-lenl;
			qs::stk_ins(f[j],j);
			for(;qh<qt&&f[que[qt-1]]<=f[j];qt--);
			que[qt++]=j;
		}
		f[i]=-INF;
		if(qh<qt){
			const int mxf=f[que[qh]];
			qs::pop_until(mxf,liml);
			assert(!qs::empty(mxf));
			upd(i,qs::front(mxf));
			qs::pop_until(mxf-1,liml);
			if(!qs::empty(mxf-1)){
				upd(i,qs::front(mxf-1));
			}
		}
	}
	if(f[n]==-INF){
		puts("Impossible");
	}else{
		printf("%d\n",f[n]);
	}
	return 0;
}
