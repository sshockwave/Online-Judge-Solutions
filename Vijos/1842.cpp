#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100010
#define MOD 99999997
using namespace std;
int a[N],b[N],posa[N],posb[N],c[N],num[N],n;
bool compa(const int &x,const int &y){
	return a[x]<a[y];
}
bool compb(const int &x,const int &y){
	return b[x]<b[y];
}
inline int lowbit(int x){
	return x&(-x);
}
inline void update(int x){
	for(;x<=n;x+=lowbit(x)){
		c[x]++;
	}
}
inline int getsum(int x){
	int sum=0;
	for(;x;x-=lowbit(x)){
		sum+=c[x];
	}
	return sum;//Forgot to return
}
int main(){
	int pos,cnt=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		posa[i]=i;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",b+i);
		posb[i]=i;
	}
	sort(posa+1,posa+n+1,compa);
	sort(posb+1,posb+n+1,compb);
	for(int i=1;i<=n;i++){
		num[posa[i]]=posb[i];
	}
	memset(c,0,sizeof(c));
	for(int i=n;i>0;i--){
		cnt+=getsum(num[i]);
		update(num[i]);
	}
	printf("%d",cnt);
}
