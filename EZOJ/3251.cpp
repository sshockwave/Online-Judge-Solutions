#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=1010;
struct Pt{
	char c;
	int to[4],d[4];
}pt[N*N];
inline void mv(int &x,int &d){
	const Pt &p=pt[x];
	x=p.to[d],d=(d+p.d[d])&3;
}
inline void loop(int &a,int &b,int &c,int &d){
	const int t=a;
	a=b,b=c,c=d,d=t;
}
inline int getid(int i,int j){
	return i*N+j;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
#endif
	const int n=ni;
	int tot=ni;
	memset(pt,0,sizeof(pt));
	for(int i=1;i<=n;i++){
		static char s[N];
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			pt[getid(i,j)].c=s[j];
		}
	}
	for(int i=0;i<=n+1;i++){
		for(int j=0;j<=n+1;j++){
			Pt &x=pt[getid(i,j)];
			if(i>0){
				x.to[0]=getid(i-1,j);
			}
			if(j<=n){
				x.to[1]=getid(i,j+1);
			}
			if(i<=n){
				x.to[2]=getid(i+1,j);
			}
			if(j>0){
				x.to[3]=getid(i,j-1);
			}
		}
	}
	for(;tot--;){
		int x[4],d[4];
		{//init 0
			x[0]=getid(0,0),d[0]=2;
			for(int tot=ni-1;tot--;mv(x[0],d[0]));
			d[0]=(d[0]+3)&3;
			for(int tot=ni-1;tot--;mv(x[0],d[0]));
		}
		const int len=ni;
		for(int i=1;i<4;i++){
			x[i]=x[i-1],d[i]=d[i-1];
			for(int tot=len+1;tot--;mv(x[i],d[i]));
			d[i]=(d[i]+1)&3;
		}
		for(int i=1;i<=len;i++){
			int to[4],td[4];
			for(int j=0;j<4;j++){
				mv(x[j],d[j]);
				to[j]=pt[x[j]].to[(d[j]+1)&3];
				td[j]=pt[x[j]].d[(d[j]+1)&3];
				assert(pt[to[j]].to[(d[j]+1+td[j]+2)&3]==x[j]);
			}
			for(int j=0;j<4;j++){
				Pt &a=pt[x[j]];
				const int d1=(d[j]+1)&3;
				a.to[d1]=to[(j+1)&3];
				a.d[d1]=(td[(j+1)&3]+d[(j+1)&3]+4-d[j])&3;
				Pt &b=pt[a.to[d1]];
				const int d2=(d1+a.d[d1]+2)&3;
				b.to[d2]=x[j];
				b.d[d2]=(4-a.d[d1])&3;
			}
		}
	}
	for(int i=1;i<=n;i++){
		int x=getid(i,0),d=1;
		for(int j=1;j<=n;j++){
			mv(x,d);
			putchar(pt[x].c);
		}
		putchar('\n');
	}
	return 0;
}
