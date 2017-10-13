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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=510;
int a[N],nxt[N],cur[N],n;
int to[N][N];
bool vis[N];
inline int work(int f0,int f1){
	vis[f0]=true,vis[f1]=true;
	int ans=2;
	while(to[f0][f1]){
		for(int &x=cur[to[f0][f1]];x<=n&&vis[x];x=nxt[x]);
		if(cur[to[f0][f1]]<=n){
			ans++;
			int t=to[f0][f1];
			f0=f1,f1=cur[t];
			vis[f1]=true;
		}else{
			break;
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
#endif
	n=ni;
	if(n<=2){
		printf("%d\n",n);
		return 0;
	}
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=n;i>=1;i--){
		nxt[i]=n+1;
		for(int j=i+1;j<=n;j++){
			if(a[i]==a[j]){
				nxt[i]=j;
				break;
			}
		}
	}
	memset(to,0,sizeof(to));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				if(a[i]+a[j]==a[k]){
					to[i][j]=k;
					break;
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j){
				for(int k=1;k<=n;k++){
					vis[k]=false,cur[k]=k;
				}
				apmax(ans,work(i,j));
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
