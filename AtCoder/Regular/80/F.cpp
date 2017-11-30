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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=210,M=10000010;
int prime[M],ps=0;
bool isp[M];
inline void gmath(int n){
	memset(isp,true,sizeof(isp));
	isp[1]=false;
	for(int i=2;i<=n;i++){
		if(isp[i]){
			prime[ps++]=i;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			isp[i*cur]=false;
			if(i%cur==0)break;
		}
	}
}
int pos[N];
int x[N],y[N];
int lcnt=0,rcnt=0;
bool vis[N];
int lnk[N];
bool dfs(int x){
	for(int v=1;v<=rcnt;v++){
		if(!vis[v]&&isp[cabs(::x[x]-y[v])]){
			vis[v]=true;
			if(lnk[v]==-1||dfs(lnk[v])){
				lnk[v]=x;
				return true;
			}
		}
	}
	return false;
}
int main(){
	int n=ni,xs=0,cnt=0;
	for(int i=1;i<=n;i++){
		int cur=ni;
		if(cur==pos[xs]){
			pos[xs]++;
		}else{
			pos[++xs]=cur,pos[++xs]=cur+1;
		}
	}
	gmath(pos[xs]);
	for(int i=1;i<=xs;i++){
		if(pos[i]&1){
			x[++lcnt]=pos[i];
		}else{
			y[++rcnt]=pos[i];
		}
	}
	memset(lnk,-1,sizeof(lnk));
	for(int i=1;i<=lcnt;i++){
		memset(vis+1,0,rcnt);
		cnt+=dfs(i);
	}
	printf("%d\n",xs+((lcnt^cnt)&1)-cnt);
	return 0;
}
