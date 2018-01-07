#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=210,logN=20;
typedef multiset<int>ms;
ms own[N][N];
inline int gans1(ms &s){
	if(s.empty())return 1;
	int last=0;
	for(ms::iterator it=s.begin();it!=s.end();it++){
		if(*it>last+1)return last+1;
		last=*it;
	}
	return (*--s.end())+1;
}
inline int gans2(ms &s){
	int mex=1;
	for(ms::iterator it=s.begin();it!=s.end();it++){
		if(*it>mex)return mex;
		mex+=*it;
	}
	return mex;
}
int n,lastans=0;
inline int gni(){
	return (ni+lastans-1)%n+1;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("forgive.in","r",stdin);
	freopen("forgive.out","w",stdout);
#endif
	n=ni;
	int tot=ni;
	for(int ts=1;ts<=tot;ts++){
		for(int i=1;i<=n;i++){
			own[ts][i]=own[ts-1][i];
		}
		switch(ni){
			case 1:
				{
					int u=gni(),g=ni;
					own[ts][u].insert(g);
					break;
				}
			case 2:
				{
					int u=gni(),g=ni;
					ms::iterator it=own[ts][u].find(g);
					if(it!=own[ts][u].end()){
						own[ts][u].erase(it);
					}
					break;
				}
			case 3:
				{
					int u=gni(),v=gni();
					if(u!=v){
						for(ms::iterator it=own[ts][v].begin();it!=own[ts][v].end();it++){
							own[ts][u].insert(*it);
						}
						own[ts][v].clear();
					}
					break;
				}
			case 4:
				{
					int u=gni();
					printf("%d %d\n",lastans=gans1(own[ts][u]),gans2(own[ts][u]));
					break;
				}
			case 5:
				{
					int u=gni(),t=ni-1;
					printf("%d %d\n",lastans=gans1(own[t][u]),gans2(own[t][u]));
					break;
				}
		}
	}
	for(int i=1;i<=n;i++){
		for(ms::iterator it=own[tot][i].begin();it!=own[tot][i].end();it++){
			printf("%d ",*it);
		}
		puts("0");
	}
	return 0;
}
