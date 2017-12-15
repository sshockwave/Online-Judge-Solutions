#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=100010,M=1000010,INF=0x7f7f7f7f;
int mx;
int pos[M];
int f[M],cnt[M][22];
vector<int>fact[M];
void addv(int x,int fv,int v){
	int oldv=f[x];
	apmax(f[x],fv);
	cnt[x][fv]+=v;
	for(;cnt[x][f[x]]==0;f[x]--);
	if(x&&oldv!=f[x]){
		addv(0,f[x],1),addv(0,oldv,-1);
	}
}
int que[N*3],qh=N,qt=N;
inline void ins_l(int x,int p){
	pos[x]=p;
	addv(x,1,1),addv(x,0,-1);
	for(int i=x<<1;i<=mx;i+=x){
		if(f[i]){
			addv(x,f[i]+1,1);
		}
	}
}
inline void reset(int x){
	memset(cnt[x],0,sizeof(cnt[x]));
	cnt[x][f[x]=0]=1;
	pos[x]=INF;
}
void alt(int x,int fr,int to,int av,int bv){
	int oldf=f[x];
	addv(x,fr,av),addv(x,to,bv);
	if(f[x]!=oldf){
		for(int i=0,ti=fact[x].size();i<ti;i++){
			if(pos[fact[x][i]]<pos[x]){
				alt(fact[x][i],oldf+1,f[x]+1,oldf?-1:0,f[x]?1:0);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dsa.in","r",stdin);
	freopen("dsa.out","w",stdout);
#endif
	int n=ni;
	mx=ni;
	int tot=ni;
	memset(pos,127,sizeof(pos));
	for(int i=1;i<=n;i++){
		que[qt++]=ni;
	}
	memset(cnt,0,sizeof(cnt));
	f[0]=0;
	for(int i=1;i<=mx;i++){
		reset(i);
		for(int j=i<<1;j<=mx;j+=i){
			fact[j].push_back(i);
		}
	}
	for(int i=qt-1;i>=qh;i--){
		ins_l(que[i],i);
	}
	while(printf("%d %d\n",f[0],cnt[0][f[0]]),tot--){
		switch(ni){
			case 0:
				que[--qh]=ni;
				ins_l(que[qh],qh);
				break;
			case 1:
				pos[que[qt]=ni]=qt;
				alt(que[qt++],0,1,-1,1);
				break;
			case 2:
				addv(0,f[que[qh]],-1);
				reset(que[qh++]);
				break;
			case 3:
				alt(que[--qt],1,0,-1,1);
				reset(que[qt]);
				break;
		}
	}
	return 0;
}
