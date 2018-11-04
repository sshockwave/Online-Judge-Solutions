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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=30,L=1.1e7+10;
int *pri,pri1[N],pri2[N],ps1=0,ps2=0;
lint *lst,lst1[L],lst2[L];
lint lim;
int ls,ls1,ls2;
void dfs(int x,lint num){
	if(x==0){
		lst[++ls]=num;
		return;
	}
	const int p=pri[x];
	for(const lint t=lim/p;;num*=p){
		dfs(x-1,num);
		if(num>t)break;
	}
}
int ppr[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
#endif
	int ps=ni;
	lim=next_num<lint>();
	for(int i=1;i<=ps;i++){
		ppr[i]=ni;
	}
	random_shuffle(ppr+1,ppr+ps+1);
	for(int i=1,j=ps;i<=j;i++,j--){
		pri1[++ps1]=ppr[i];
		if(i<j){
			pri2[++ps2]=ppr[j];
		}
	}
	ls=0,pri=pri1,lst=lst1,dfs(ps1,1),ls1=ls;
	ls=0,pri=pri2,lst=lst2,dfs(ps2,1),ls2=ls;
	sort(lst1+1,lst1+ls1+1);
	sort(lst2+1,lst2+ls2+1);
	lint mx=0,cnt=0;
	for(int i=1,j=ls2;i<=ls1;i++){
		for(lint t=lim/lst1[i];j>=1&&lst2[j]>t;j--);
		apmax(mx,lst1[i]*lst2[j]),cnt+=j;
	}
	printf("%lld\n%lld\n",mx,cnt);
	return 0;
}
