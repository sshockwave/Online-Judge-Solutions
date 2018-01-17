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
const int N=10000010,D=100;
namespace H{
	const int O=998244353;
	inline int fpow(int x,int n){
		int a=1;
		for(;n;n>>=1,x=(lint)x*x%O){
			if(n&1){
				a=(lint)a*x%O;
			}
		}
		return a;
	}
	inline int inv(int x){
		return fpow(x,O-2);
	}
	const int invnum=inv(100);
	inline int shift(int x,char c){
		return (lint)(x+O-c)*invnum%O;
	}
	inline int revsh(int x,char c){
		return ((lint)x*100+c)%O;
	}
	inline int push(int x,char c,int pw){
		return (x+(lint)pw*c)%O;
	}
	inline int pop(int x,char c,int pw){
		return (x+O-(lint)pw*invnum%O*c%O)%O;
	}
}
char str[N<<1];
struct state{
	int l,r,ans,pw;
	int l1,l2,r1,r2;
	inline state ins_left(char c)const{
		str[l-1]=c;
		state nxt=(state){l-1,r,ans};
		if(l+ans<=r&&str[l-1]==str[l+ans]&&l1==l2){//check ans
			nxt.ans=ans+2;
			nxt.pw=(lint)pw*10000%H::O;
			nxt.l1=nxt.l2=H::revsh(H::push(l1,c,pw),c);
			nxt.r1=H::revsh(H::revsh(r1,str[r-ans]),str[r-ans-1]);
			nxt.r2=H::push(H::push(r2,str[r-ans],pw),str[r-ans-1],(lint)pw*100%H::O);
		}
		if(nxt.ans==ans&&str[l-1]==str[l+ans-1]&&H::pop(l1,c,pw)==H::shift(l2,c)){//check ans-1
			nxt.ans=ans+1;
			nxt.pw=(lint)pw*100%H::O;
			nxt.l1=nxt.l2=H::revsh(l1,c);
			nxt.r1=H::revsh(r1,str[r-ans]);
			nxt.r2=H::push(r2,str[r-ans],pw);
		}
		if(nxt.ans==ans){//nothing changed
			nxt.pw=pw;
			nxt.l1=H::revsh(H::pop(l1,str[l+ans-1],pw),c);
			nxt.l2=H::shift(H::push(l2,c,pw),str[l+ans-1]);
			nxt.r1=r1;
			nxt.r2=r2;
		}
		return nxt;
	}
	inline state ins_right(char c)const{
		str[r+1]=c;
		state nxt=(state){l,r+1,ans};
		if(r-ans>=l&&str[r-ans]==str[r+1]&&r1==r2){//check ans
			nxt.ans=ans+2;
			nxt.pw=(lint)pw*10000%H::O;
			nxt.r1=nxt.r2=H::revsh(H::push(r1,c,pw),c);
			nxt.l1=H::push(H::push(l1,str[l+ans],pw),str[l+ans+1],(lint)pw*100%H::O);
			nxt.l2=H::revsh(H::revsh(l2,str[l+ans]),str[l+ans+1]);
		}
		if(nxt.ans==ans&&str[r-ans+1]==str[r+1]&&H::pop(r2,c,pw)==H::shift(r1,c)){//check ans-1
			nxt.ans=ans+1;
			nxt.pw=(lint)pw*100%H::O;
			nxt.r1=nxt.r2=H::revsh(r2,c);
			nxt.l1=H::push(l1,str[l+ans],pw);
			nxt.l2=H::revsh(l2,str[l+ans]);
		}
		if(nxt.ans==ans){//nothing changed
			nxt.pw=pw;
			nxt.l1=l1;
			nxt.l2=l2;
			nxt.r1=H::shift(H::push(r1,c,pw),str[r-ans+1]);
			nxt.r2=H::revsh(H::pop(r2,str[r-ans+1],pw),c);
		}
		return nxt;
	}
}stk[N];
int ss=0;
char s[N*3];
int main(){
#ifndef ONLINE_JUDGE
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
#endif
	int tot=ni;
	fread(s,1,N*3,stdin);
	stk[ss]=(state){N,N-1,0,1,0,0,0,0};
	lint ans=0;
	for(int i=0,j=0;i<tot;i++,j+=3){
		int op=s[j]-'0';
		int num=((s[j+1]-'0')*10+(s[j+2]-'0')+stk[ss].ans)%100;
		if(op==3){
			ss-=num;
		}else{
			stk[ss+1]=op==1?stk[ss].ins_left(num):stk[ss].ins_right(num);
			ss++;
		}
		ans+=stk[ss].ans;
	}
	printf("%lld\n",ans);
	return 0;
}
