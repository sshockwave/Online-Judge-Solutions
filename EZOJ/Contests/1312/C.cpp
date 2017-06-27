#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=12,MOD=998244353;
int n=ni,k=ni,ans=0;
int a[N][N];
bool vis[N];
inline int med(int a,int b,int c){
	if(a>b){
		swap(a,b);
	}
	if(b>c){
		swap(b,c);
	}
	if(a>b){
		swap(a,b);
	}
	return b;
}
void dfs(int x){/*
	if(vis[k]&&a[x/2][1]!=k){
		return;
	}*/
	if(x==n){
		ans+=a[x/2][1]==k;
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=true;
			a[0][x+1]=i;
			for(int j=1;j<=n;j++){
				if(!vis[j]){
					vis[j]=true;
					a[0][x+2]=j;
					for(int k=0,p=x;k<(x+2)/2;k++,p-=2){
						a[k+1][p-1]=med(a[k][p-1],a[k][p],a[k][p+1]);
						a[k+1][p]=med(a[k][p],a[k][p+1],a[k][p+2]);
					}
					dfs(x+2);
					vis[j]=false;
				}
			}
			vis[i]=false;
		}
	}
}
inline int work(){
	if((n&1)==0){
		return 0;
	}
	if(k>=n||k<=1){
		return 0;
	}
	if(n==1){
		return 1;
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		vis[i]=true;
		a[0][1]=i;
		dfs(1);
		vis[i]=false;
	}
	return ans;
}
int main(){
	printf("%d\n",work());
}
