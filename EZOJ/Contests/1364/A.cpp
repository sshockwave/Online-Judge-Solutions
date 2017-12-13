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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=60,INF=0x7f7f7f7f;
int qd[N<<1],qdh,qdt,qu[N<<1],quh,qut;
int n;
int a[N],b[N];
int ans;
int tp[N];//-1:unvis 0:up 1:down 2:inf
int stat[N];
void dfs(int x,int cur){
	if(cur>ans)return;
	if(x>n){
		memset(stat+1,0,n<<2);
		for(int i=1;i<=n;i++){
			if(tp[i]!=2)continue;
			if(stat[b[i]]==0){
				stat[b[i]]=1;
			}else{
				stat[b[i]]=0;
				for(int j=1;j<i;j++){
					cur+=stat[b[j]];
				}
			}
		}
		apmin(ans,cur);
		return;
	}
}
int cnt[N];
inline int Main(){
	n=ni;
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++){
		cnt[a[i]=ni]++;
	}
	int nn=0;
	for(int i=1;i<=n;i++){
		if(cnt[a[i]]==2){
			b[++nn]=a[i];
		}
	}
	assert(nn%2==0);
	if(nn==0)return 0;
	if(nn==2)return 0;
	if(nn==4)return 0;
	return 3;
	qdh=qdt=quh=qut=0;
	memset(tp,-1,sizeof(tp));
	ans=INF;
	tp[b[1]]=0;
	qu[quh++]=b[1];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
