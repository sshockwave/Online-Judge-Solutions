#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=100010;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int pre[N],nxt[N];
int L,d[N],v[N];
struct icmp{
	int x,y,a,b;
	icmp(int _x){
		y=nxt[x=_x];
		if(v[x]<v[y]){
			a=(d[x]-d[y]+L)%L;
			b=v[y]-v[x];
		}else{
			a=(d[y]-d[x]+L)%L;
			b=v[x]-v[y];
		}
		int g=gcd(a,b);
		a/=g,b/=g;
	}
	inline friend bool operator < (const icmp &a,const icmp &b){
		return (lint)a.a*b.b>(lint)b.a*a.b;
	}
};
priority_queue<icmp>q;
int lst[N];
inline bool lcmp(int a,int b){
	return d[a]<d[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
#endif
	int n=ni;
	L=ni;
	if(n==1){
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++){
		d[i]=ni;
	}
	for(int i=1;i<=n;i++){
		v[i]=ni;
		lst[i-1]=i;
	}
	sort(lst,lst+n,lcmp);
	for(int i=0;i<n;i++){
		pre[nxt[lst[i]]=lst[(i+1)%n]]=lst[i];
	}
	for(int i=1;i<=n;i++){
		q.push(icmp(i));
	}
	for(int i=2;i<n;i++){
		for(;nxt[q.top().x]!=q.top().y;q.pop());
		int x=q.top().x,y=nxt[x];
		q.pop();
		if(x<y){
			nxt[pre[y]=pre[x]]=y;
			pre[x]=nxt[x]=0;
			q.push(icmp(pre[y]));
		}else{
			pre[nxt[x]=nxt[y]]=x;
			pre[y]=nxt[y]=0;
			q.push(icmp(x));
		}
	}
	for(;nxt[q.top().x]!=q.top().y;q.pop());
	printf("%d/%d\n",q.top().a,q.top().b);
	return 0;
}
