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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=1000010;
namespace uniq{
	int pos[N],tag[N],tim=0;
	inline void init(){
		memset(tag,0,sizeof(tag));
	}
	inline int gpos(int x){
		return tag[x]<tim?tag[x]=tim,pos[x]=0:pos[x];
	}
	inline void main(int a[],const int n){
		++tim;
		for(int i=1;i<=n;i++){
			int t=gpos(a[i]);
			pos[a[i]]=i;
			a[i]=i-t;
		}
	}
}
int fail[N];
inline void get_fail(const int s[],const int n){
	fail[0]=-1;
	for(int i=0,j=-1;i<n;){
		if(j==-1||min(s[i+1],j+1)==s[j+1]){
			fail[++i]=++j;
		}else{
			j=fail[j];
		}
	}
}
int s[N],t[N];
int lst[N];
inline void Main(){
	int n=ni,m=ni;
	generate_n(s+1,n,next_num<int>),uniq::main(s,n);
	generate_n(t+1,m,next_num<int>),uniq::main(t,m);
	get_fail(t,m);
	int ls=0;
	for(int i=0,j=0;i<n;){
		if(j==-1||min(s[i+1],j+1)==t[j+1]){
			++i,++j;
			if(j==m){
				lst[++ls]=i-m+1;
				j=fail[j];
			}
		}else{
			j=fail[j];
		}
	}
	printf("%d\n",ls);
	for(int i=1;i<=ls;i++){
		printf("%d ",lst[i]);
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("xiz.in","r",stdin);
	freopen("xiz.out","w",stdout);
#endif
	int tot=ni;
	ni;
	uniq::init();
	for(;tot--;Main());
	return 0;
}
