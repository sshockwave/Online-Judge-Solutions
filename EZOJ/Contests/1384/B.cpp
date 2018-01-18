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
const int N=200010;//TODO::check all []
namespace B{
	int c[N],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void set(int x,int v){
		for(;x<=n;apmax(c[x],v),x+=x&-x);
	}
	inline int ask(int x){
		int ans=0;
		for(;x;apmax(ans,c[x]),x^=x&-x);
		return ans;
	}
}
struct Card{
	int d1,d2,u1,u2,f;
}card[N];
int* lst1[N],ls1=0;
int* lst2[N],ls2=0;
inline bool lcmp(int* a,int* b){
	return *a<*b;
}
int pid[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("remove.in","r",stdin);
	freopen("remove.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		card[i]=(Card){ni,ni,ni,ni};
		lst1[++ls1]=&card[i].d1;
		lst1[++ls1]=&card[i].d2;
		lst2[++ls2]=&card[i].u1;
		lst2[++ls2]=&card[i].u2;
	}
	sort(lst1+1,lst1+ls1+1,lcmp);
	sort(lst2+1,lst2+ls2+1,lcmp);
	for(int i=1;i<=ls1;i++){
		*lst1[i]=i;
	}
	for(int i=1;i<=ls2;i++){
		*lst2[i]=i;
	}
	B::init(ls2);
	memset(pid,0,sizeof(pid));
	for(int i=1;i<=n;i++){
		pid[card[i].u1]=i;
		pid[card[i].u2]=-i;
	}
	int ans=0;
	for(int i=1;i<=ls2;i++){
		int t=pid[i];
		if(t<0){
			t=-t;
			B::set(card[t].d2,card[t].f);
		}else{
			apmax(ans,card[t].f=B::ask(card[t].d1)+1);
		}
	}
	printf("%d\n",ans);
	return 0;
}
