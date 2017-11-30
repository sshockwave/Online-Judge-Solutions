#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <set>
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
const int N=110,M=10000010;
int prime[M],ps=0;
bool isp[M];
inline void gmath(int n){
	memset(isp,true,sizeof(isp));
	isp[1]=false;
	for(int i=2;i<=n;i++){
		if(isp[i]){
			prime[ps++]=i;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			isp[i*cur]=false;
			if(i%cur==0)break;
		}
	}
}
set<int>s;
typedef set<int>::iterator iter;
inline void flip(int x){
	iter it=s.find(x);
	if(it==s.end()){
		s.insert(x);
	}else{
		s.erase(x);
	}
}
int main(){
	int n=ni,mx=0;
	for(int i=1;i<=n;i++){
		int cur=ni;
		apmax(mx,cur);
		flip(cur),flip(cur+1);
	}
	gmath(mx);
	int ans=s.size(),cnt=0;
	for(iter i=s.begin(),j;i!=s.end();){
		for(j=i;++j!=s.end()&&!isp[*j-*i];);
		if(j==s.end()){
			i++;
		}else{
			cnt++;
			iter nxt=i;
			nxt++;
			if(nxt==j){
				nxt++;
			}
			s.erase(i),s.erase(j);
			i=nxt;
		}
	}
	printf("%d\n",ans+(cnt&1)-cnt);
	return 0;
}
