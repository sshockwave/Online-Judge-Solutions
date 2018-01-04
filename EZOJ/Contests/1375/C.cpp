#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
template<class T>T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=9,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
typedef vector<lint>vi;
typedef vi::iterator iter;
int gans(vi &org){
	if(org.empty())return 1;
	{
		int sh=0;
		lint g=0;
		for(iter it=org.begin();it!=org.end();it++){
			if(*it==0)return 0;
			g=gcd(g,*it);
		}
		assert(g);
		for(;(g&1)==0;g>>=1,sh++);
		if(sh){
			vi coor;
			for(iter it=org.begin();it!=org.end();it++){
				lint val=*it>>sh;
				if(val!=1){
					coor.push_back(val);
				}
			}
			return (lint)gans(coor)*fpow(org.size()+1,sh)%O;
		}
	}
	{
		bool flag=false;
		for(iter it=org.begin();it!=org.end();it++){
			if(*it==1){
				flag=true;
				break;
			}
		}
		if(flag){
			vi coor;
			for(iter it=org.begin();it!=org.end();it++){
				if(*it!=1){
					coor.push_back(*it);
				}
			}
			return gans(coor);
		}
	}
	int sh;
	vi coor=org;
	//no more org
	if(coor.size()==1)return coor[0]%O;
	if(coor.size()==2){
		lint a=coor[0],b=coor[1];
		if(a>b){
			swap(a,b);
		}
		for(sh=0;(1ll<<(sh+1))<=a;sh++);
		lint len=1ll<<sh;
		lint cnt=b/len;
		lint ans=cnt*fpow(3,sh)%O;
		if(b%len){
			vi nxt;
			nxt.push_back(len),nxt.push_back(b%len);
			ans+=gans(nxt);
			if((cnt&1)==0&&a>len){
				vi nxt;
				nxt.push_back(b%len),nxt.push_back(a-len);
				ans+=gans(nxt);
			}
		}
		if(a>len){
			vi nxt;
			nxt.push_back(a-len),nxt.push_back(len);
			ans+=((cnt+1)>>1)*gans(nxt)%O;
		}
		return ans%O;
	}
	/*
	if(cnt==1){
		iter pt;
		for(pt=coor.begin();(*pt&1)==0;pt++);
		g=0;
		for(iter it=coor.begin();it!=coor.end();it++){
			if(it!=pt){
				g=gcd(g,*it);
			}
		}
		assert(g&&(g&1)==0);
		for(sh=0;(g&1)==0&&(1ll<<(sh+1))<*pt;g>>=1,sh++);
		lint oldval=*pt;
		for(iter it=coor.begin();it!=coor.end();it++){
			*it>>=sh;
		}
		int ans1=gans(coor);
		*pt++;
		int ans2=gans(coor);
		vi nxt;
		for(int i=0,ti=coor.size()-1;i<ti;i++){
			nxt.push_back(1ll<<sh);
		}
		nxt.push_back(oldval%(1ll<<sh));
		ans2=(lint)(ans2-ans1+O)%O*gans(nxt)%O;
		ans1=((lint)ans1*fpow(coor.size()+1,sh)%O+ans2)%O;
		return (lint)ans1*fact%O;
	}*/
	lint mn=coor[0];
	for(iter it=coor.begin()+1;it!=coor.end();it++){
		apmin(mn,*it);
	}
	for(;(1ll<<(sh+1))<=mn;sh++);
	lint ans=0;
	for(int s=1,ts=1<<coor.size();s<ts;s++){
		vi nxt;
		int cnt=0;
		for(int i=0,ti=coor.size();i<ti;i++){
			if((s>>i)&1){
				cnt++;
				nxt.push_back(mn);
			}else{
				nxt.push_back(coor[i]);
			}
		}
		if(cnt&1){
			ans+=gans(nxt);
		}else{
			ans-=gans(nxt);
		}
	}
	return (ans%O+O)%O;
}
int a[N][2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("village.in","r",stdin);
	freopen("village.out","w",stdout);
#endif
	int k=ni;
	for(int i=0;i<k;i++){
		a[i][1]=next_num<lint>()-1;
		a[i][0]=next_num<lint>();
	}
	lint ans=0;
	for(int s=0,ts=1<<k;s<ts;s++){
		vi coor;
		int cnt=0;
		for(int i=0;i<k;i++){
			cnt+=(s>>i)&1;
			coor.push_back(a[i][(s>>i)&1]);
		}
		if(cnt&1){
			ans-=gans(coor);
		}else{
			ans+=gans(coor);
		}
	}
	printf("%lld\n",(ans%O+O)%O);
	return 0;
}
