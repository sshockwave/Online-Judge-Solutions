#include <iostream>
#include <cstdio>
#include <cstring>
//#define NDEBUG
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
const int N=100010,M=7000010,INF=0x7f7f7f7f;
int n,m,q,u,v,t;
namespace worm{
	int len[N],a[M],b[M],qa=0,qb=0,qh=0,qt=0,delta=0;
	inline bool lencmp(const int &a,const int &b){
		return a>b;
	}
	inline void get(){
		for(int i=0;i<n;i++){
			len[i]=ni;
		}
		sort(len,len+n,lencmp);
	}
	inline void add(int x){
		a[qt]=(lint)u*x/v,b[qt]=x-a[qt];
		a[qt]-=delta,b[qt]-=delta;
		qt++;
	}
	inline int pop(){
		if(qh<n&&(qa==qt||len[qh]>=a[qa])&&(qb==qt||len[qh]>=b[qb])){
			return len[qh++]+delta;
		}else if(qa<qt&&(qb==qt||a[qa]>=b[qb])){
			return a[qa++]+delta;
		}else{
			return b[qb++]+delta;
		}
	}
}
int main(){
	n=ni,m=ni,q=ni,u=ni,v=ni,t=ni;
	worm::get();
	for(int i=1,j=0;i<=m;i++){
		int len=worm::pop();
		worm::delta+=q;
		worm::add(len);
		if(++j==t){
			j=0;
			printf("%d",len);
			if(i+t<=m){
				putchar(' ');
			}
		}
	}
	putchar('\n');
	for(int i=1,j=0,ti=n+m;i<=ti;i++){
		int len=worm::pop();
		if(++j==t){
			j=0;
			printf("%d",len);
			if(i+t<=ti){
				putchar(' ');
			}
		}
	}
	return 0;
}
