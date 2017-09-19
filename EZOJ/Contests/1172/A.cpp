#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=22,T=210,INF=0x7f7f7f7f;
struct state{
	int a,b,c;
	inline friend bool operator < (const state &a,const state &b){
		return a.a!=b.a?a.a<b.a:a.b!=b.b?a.b<b.b:a.c<b.c;
	}
};
map<state,int>m[N];
int mx;
inline void pushstate(map<state,int>&m,int i,int j,int k,int v){
	if(i>mx){
		return;
	}
	apmin(j,mx+1),apmin(k,mx+1);
	map<state,int>::iterator it=m.find((state){i,j,k});
	if(it!=m.end()){
		apmin(it->second,v);
	}else{
		m[((state){i,j,k})]=v;
	}
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("puzzle.in","r",stdin);
	freopen("puzzle.out","w",stdout);
#endif
	for(;scanf("%s%d",s,&mx),mx>=0;){
		pushstate(m[1],0,1,s[0]-'0',0);
		int n=strlen(s);
		for(int i=1;i<n;i++){
			int d=s[i]-'0';
			for(map<state,int>::iterator it;m[i].begin()!=m[i].end();m[i].erase(it)){
				it=m[i].begin();
				int a=it->first.a,b=it->first.b,c=it->first.c;
				//do nothing
				pushstate(m[i+1],a,b,c*10+b*d,it->second);
				//*
				pushstate(m[i+1],a,c,c*d,it->second+1);
				//+
				pushstate(m[i+1],a+c,1,d,it->second+1);
			}
		}
		int ans=INF;
		for(map<state,int>::iterator it;m[n].begin()!=m[n].end();m[n].erase(it)){
			it=m[n].begin();
			if(it->first.a+it->first.c==mx){
				apmin(ans,it->second);
			}
		}
		printf("%d\n",ans==INF?-1:ans);
	}
	return 0;
}
