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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010,D=10,INF=0x7f7f7f7f;
struct State{
	int num[D];
}f_l1[N],f_l2[N],f_r2[N];
int tim_l1[N],tim_l[N],tim_r[N];//exit time
char s[N];
bool vani[N];
int prv[N],nxt[N];
inline void del(int x){
	vani[x]=true;
	if(tim_l[x]<INF&&tim_r[x]<INF){
		prv[nxt[x]]=prv[x],nxt[prv[x]]=nxt[x];
	}
}
inline bool ispt(int x){
	return s[x]=='<'||s[x]=='>';
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("program.in","r",stdin);
	freopen("program.out","w",stdout);
#endif
	int n=ni,q=ni;
	scanf("%s",s+1);
	nxt[0]=1,prv[n+1]=n;
	for(int i=1;i<=n;i++){
		prv[i]=i-1,nxt[i]=i+1;
	}
	mset(tim_l1+1,127,n);
	mset(tim_l+1,127,n);
	mset(tim_r+1,127,n);
	mset(vani+1,0,n);
	State cur;
	memset(cur.num,0,D);
	int dir=1,tim=0;
	int x=1;
	int last=0;
	for(;x<=n;x=dir==1?nxt[x]:prv[x]){
		if(x==0){
			if(ispt(last)){
				assert(s[last]=='<');
				del(last);
			}
			last=0;
			dir=1;
			continue;
		}
		if(vani[x]){
			if(dir==1){
				assert(tim_r[x]==INF);
				f_r2[x]=cur,tim_r[x]=tim;
			}else{
				assert(tim_l[x]==INF);
				f_l2[x]=cur,tim_l[x]=tim;
			}
			del(x);
			continue;
		}
		++tim;
		if(tim_l1[x]==INF){
			tim_l1[x]=tim;
			f_l1[x]=cur;
		}
		bool todel=false;
		if(ispt(x)){
			if(ispt(last)){
				assert(!vani[last]);
				del(last);
			}
			dir=s[x]=='<'?-1:1;
		}else{
			assert(isdigit(s[x]));
			++cur.num[s[x]---'0'];
			if(s[x]<'0'){
				todel=true;
			}
		}
		if(dir==1){
			if(tim_r[x]==INF){
				tim_r[x]=tim;
				f_r2[x]=cur;
			}
		}else{
			if(tim_l[x]==INF){
				tim_l[x]=tim;
				f_l2[x]=cur;
			}
		}
		if(todel){
			del(x);
		}
		last=x;
	}
	for(int tot=q;tot--;){
		int l=ni,r=ni;
		const State &a=f_l1[l];
		const State &b=tim_l[l]<tim_r[r]?f_l2[l]:f_r2[r];
		for(int i=0;i<D;i++){
			printf("%d ",b.num[i]-a.num[i]);
		}
		putchar('\n');
	}
	return 0;
}
