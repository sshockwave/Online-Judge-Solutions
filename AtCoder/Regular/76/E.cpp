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
const int N=100010;
struct Node{
	int x,d;
	inline friend bool operator < (const Node &a,const Node &b){
		return a.d<b.d;
	}
}lst[N<<1];
int n,m,ls=0;
inline bool onedge(int x,int y){
	return x==0||x==n||y==0||y==m;
}
inline int makeid(int x,int y){
	if(x==0){
		return y;
	}else if(y==m){
		return x+m;
	}else if(x==n){
		return m+n+m-y;
	}else if(y==0){
		return m+n+m+n-x;
	}else assert(false);
}
int stk[N],ss=0;
int main(){
	n=ni,m=ni;
	for(int tot=ni;tot--;){
		int x1=ni,y1=ni,x2=ni,y2=ni;
		if(onedge(x1,y1)&&onedge(x2,y2)){
			int id=ls;
			lst[++ls]=(Node){id,makeid(x1,y1)};
			lst[++ls]=(Node){id,makeid(x2,y2)};
		}
	}
	sort(lst+1,lst+ls+1);
	for(int i=1;i<=ls;i++){
		if(ss&&stk[ss-1]==lst[i].x){
			ss--;
		}else{
			stk[ss++]=lst[i].x;
		}
	}
	puts(ss?"NO":"YES");
	return 0;
}
