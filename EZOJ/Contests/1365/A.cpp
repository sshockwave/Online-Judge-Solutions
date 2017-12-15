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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010,M=1000010;
int mx;
int f[N];
int longv=0,longcnt=0;
inline void ins(int x){//ins at front
	f[x]=0;
	for(int i=x<<1;i<=mx;i+=x){
		apmax(f[x],f[i]);
	}
	f[x]++;
	if(f[x]>longv){
		longv=f[x],longcnt=0;
	}
	if(f[x]==longv){
		longcnt++;
	}
}
int que[N*3],qh=N,qt=N;
inline void bd(){
	longv=longcnt=0;
	for(int i=qt-1;i>=qh;i--){
		ins(que[i]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dsa.in","r",stdin);
	freopen("dsa.out","w",stdout);
#endif
	int n=ni;
	mx=ni;
	int tot=ni;
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		que[qt++]=ni;
	}
	bd();
	while(printf("%d %d\n",longv,longcnt),tot--){
		int op=ni;
		if(op==0){
			que[--qh]=ni;
			ins(que[qh]);
		}else{
			for(int i=qh;i<qt;i++){
				f[que[i]]=0;
			}
			if(op==1){
				que[qt++]=ni;
			}else if(op==2){
				qh++;
			}else if(op==3){
				qt--;
			}else assert(false);
			bd();
		}
	}
	return 0;
}
