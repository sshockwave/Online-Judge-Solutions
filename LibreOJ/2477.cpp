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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=210;
int b[N];
typedef vector<int>vi;
vi team[N];
int que[N];
int lnk[N];
int preman[N],preteam[N];
inline void bfs(bool vis[],int m){
	int qh=0,qt=0;
	memset(vis+1,0,m*sizeof(vis[0]));
	for(int i=1;i<=m;i++){
		if(b[i]){
			que[qt++]=i,vis[i]=true;
			preman[i]=preteam[i]=0;
		}
	}
	while(qh<qt){
		int x=que[qh++];
		for(vi::iterator it=team[x].begin();it!=team[x].end();++it){
			int v=lnk[*it];
			if(!vis[v]){
				que[qt++]=v,vis[v]=true;
				preman[v]=*it,preteam[v]=x;
			}
		}
	}
}
bool vac[N][N];
vi mat[N][N];
inline void Main(){
	int n=ni,m=ni;
	for(int i=1;i<=m;i++){
		b[i]=ni;
		team[i].clear();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			mat[i][j].clear();
		}
		for(int j=1;j<=m;j++){
			mat[i][ni].push_back(j);
		}
		bfs(vac[i],m);
		int lev=1;
		lnk[i]=0;
		for(int &j=lev;j<=m;j++){
			for(vi::iterator it=mat[i][j].begin();it!=mat[i][j].end();++it){
				if(vac[i][*it]){
					lnk[i]=*it;
					break;
				}
			}
			if(lnk[i])break;
		}
		printf("%d ",lev);
		if(lev>m)continue;
		for(vi::iterator it=mat[i][lev].begin();it!=mat[i][lev].end();++it){
			team[*it].push_back(i);
		}
		b[lnk[i]]--;
		for(int j=lnk[i];preteam[j];j=preteam[j]){
			b[j]++,lnk[preman[j]]=preteam[j],b[preteam[j]]--;
		}
	}
	putchar('\n');
	for(int i=1;i<=n;i++){
		int j=i;
		int s=ni;
		for(;j>=1;j--){
			bool flag=false;
			for(int k=1;k<=s;k++){
				for(vi::iterator it=mat[i][k].begin();it!=mat[i][k].end();++it){
					if(vac[j][*it]){
						flag=true;
						break;
					}
				}
				if(flag)break;
			}
			if(flag)break;
		}
		printf("%d ",i-j);
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("mentor.in","r",stdin);
	freopen("mentor.out","w",stdout);
#endif
	int tot=ni;
	ni;
	for(;tot--;Main());
	return 0;
}
