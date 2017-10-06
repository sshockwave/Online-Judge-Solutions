#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=1010,A=1<<13;
int hb[A+1];
bool sing[A+1];
queue<int>q[N];
int pre[N][A+1];
bool side[N][A+1],vis[N][A+1];
inline void psh(int i,int ov,int nv,bool d){
	q[i].push(nv);
	pre[i][nv]=ov,side[i][nv]=d,vis[i][nv]=false;
}
void putans(int x,int v){
	if(x){
		putans(x-1,pre[x][v]),putchar(side[x][v]?'r':'l');
	}
}
inline void Main(){
	int n=ni,sum=0;
	psh(0,0,0,0);
	for(int i=1;i<=n;i++){
		int a=ni;
		for(int j=i-1;!q[j].empty();q[j].pop()){
			int l=q[j].front(),r=sum-l;
			if(vis[j][l]){
				continue;
			}
			vis[j][l]=true;
			if(sing[l]&&a>l){
				psh(i,l,a,0);
			}
			if(a<=(l&-l)){
				psh(i,l,a+l,0);
			}
			assert((r&hb[l])==0);
			int nl=r|hb[l],nr=l^hb[l];
			if(sing[nl]&&a>nl){
				assert(r==0);
				psh(i,l,l|a,1);
			}
			if(a<=(nl&-nl)){
				int nnl=nl+a;
				psh(i,l,nr^hb[nnl],1);
			}
		}
		sum+=a;
	}
	bool flag=false;
	for(;!q[n].empty();q[n].pop()){
		if(q[n].front()==sum){
			flag=true;
		}
	}
	if(sing[sum]&&flag){
		putans(n,sum),putchar('\n');
	}else{
		puts("no");
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("2048.in","r",stdin);
	freopen("2048.out","w",stdout);
#endif
	memset(sing,0,sizeof(sing));
	sing[0]=true;
	for(int i=1;i<=A;i<<=1){
		sing[i]=true;
	}
	hb[0]=0,hb[1]=1;
	for(int i=2;i<=A;i++){
		hb[i]=hb[i>>1]<<1;
	}
	for(int tot=ni;tot--;Main());
	return 0;
}
