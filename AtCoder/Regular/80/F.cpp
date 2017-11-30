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
int x[N];
bool vis[N];
int main(){
	int n=ni,xs=0,cnt=0;
	for(int i=1;i<=n;i++){
		int cur=ni;
		if(cur==x[xs]){
			x[xs]++;
		}else{
			x[++xs]=cur,x[++xs]=cur+1;
		}
	}
	gmath(x[xs]);
	memset(vis,0,sizeof(vis));
	for(int i=1,j;i<=xs;i++){
		if(!vis[i]){
			for(j=i+1;j<=xs;j++){
				if(!vis[j]&&isp[x[j]-x[i]])break;
			}
			if(j<=xs){
				vis[i]=vis[j]=true;
				cnt++;
			}
		}
	}
	printf("%d\n",xs+(cnt&1)-cnt);
	return 0;
}
