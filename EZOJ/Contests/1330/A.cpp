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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=1010;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
struct Itsect{
	int u,v;
	int a,b;
	inline void sani(){
		int g=gcd(a,b);
		a/=g,b/=g;
	}
	inline friend bool operator < (const Itsect &a,const Itsect &b){
		return (lint)a.a*b.b<(lint)b.a*a.b;
	}
}lst[N*N];
int d[N],vc[N];
bool vis[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
#endif
	memset(vis,0,sizeof(vis));
	int n=ni,L=ni;
	if(n==1){
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++){
		d[i]=ni;
	}
	for(int i=1;i<=n;i++){
		vc[i]=ni;
	}
	int ss=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(vc[i]>vc[j]){
				lst[ss]=(Itsect){i,j,(d[j]-d[i]+L)%L,vc[i]-vc[j]};
				lst[ss++].sani();
			}
		}
	}
	sort(lst,lst+ss);
	int last=0;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<ss;i++){
		if(!vis[lst[i].u]&&!vis[lst[i].v]){
			vis[min(lst[i].u,lst[i].v)]=true;
			last=i;
		}
	}
	printf("%d/%d\n",lst[last].a,lst[last].b);
	return 0;
}
