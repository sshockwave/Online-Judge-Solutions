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
const int N=310,M=110,INF=0x7f7f7f7f;
int lst[N],ls=0;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	bool dfs(int x,int fa,int t){
		lst[++ls]=x;
		if(x==t)return true;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa&&dfs(v,x,t))return true;
		}
		--ls;
		return false;
	}
}
typedef int(*arr)[M][M];
int tim=0;
inline void upd(arr f,arr tag,int a,int b,int c,int v,int tim=::tim){
	if(tag[a][b][c]<tim){
		tag[a][b][c]=tim;
		f[a][b][c]=v;
	}else{
		apmin(f[a][b][c],v);
	}
}
int pol[6][M][M][M];
arr f=pol[0],nf=pol[1],tag=pol[2],ntag=pol[3],g=pol[4],gtag=pol[5];
char str[N];
int que[N],dep[N],dlst[N];
bool vis[N];
int nxt[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("difficult.in","r",stdin);
	freopen("difficult.out","w",stdout);
#endif
	int n=ni,s=ni,t=ni;
	scanf("%s",str+1);
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs(s,0,t);
	str[0]='.';
	lst[0]=lst[ls+1]=0;
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=ls;i++){
		vis[lst[i]]=true;
	}
	nxt[ls+1]=ls+1;
	for(int i=ls;i>=1;i--){
		nxt[i]=str[lst[i+1]]=='X'?i+1:nxt[i+1];
	}
	memset(pol,-1,sizeof(pol));
	tim=0,upd(f,tag,1,0,0,0);
	for(int t=0;t<=ls;t++,swap(f,nf),swap(tag,ntag)){
		int ds=0;
		dlst[0]=0;
		bool vac=false;
		if(t){
			int qh=0,qt=0;
			que[qt++]=lst[t],dep[lst[t]]=0;
			while(qh<qt){
				int x=que[qh++];
				vis[x]=true;
				if(dep[x]>1){
					dlst[++ds]=dep[x];
				}
				using namespace T;
				for(int i=head[x],v;~i;i=bro[i]){
					if(!vis[v=to[i]]){
						que[qt]=v,dep[v]=dep[x]+1,qt++;
					}
				}
			}
			vac=qt>1;
		}
		tim=t+1;
		for(int l=1;l<=t+!t;l++){
			for(int r=t;r<=ls;r++){
				for(int k=0;k<=ls;k++){
					if(tag[l][r][k]<t&&gtag[l][r][k]<=t)continue;
					int &F=f[l][r][k];
					if(vac){
						int &G=g[l][r][k];
						if(tag[l][r][k]==t){
							upd(g,gtag,l,r,k,F+2);
						}
						upd(f,tag,l,r,k,G,t);
						if(l<t&&r<ls){
							if(str[lst[r+1]]=='X'){
								upd(g,gtag,l+1,r+1,k,G+(r+1-l));
							}else if(k){
								upd(g,gtag,l+1,r+1,k-1,G+((r+1-t)<<1)+(t-l));
							}
						}
						if(l<t){
							upd(g,gtag,l+1,r,k,G);
						}
						if(r<ls&&str[lst[r+1]]!='X'){
							upd(g,gtag,l,r+1,k,G);
						}
					}
					if(l<t){
						upd(f,tag,l+1,r,k,F,t);
					}
					if(r<ls&&str[lst[r+1]]!='X'){
						upd(f,tag,l,r+1,k,F,t);
					}
					int sum=F,tk=k,tr=r;
					upd(nf,ntag,l,tr,tk,sum+tk);
					if(t==r&&str[lst[r+1]]=='X'){
						upd(nf,ntag,l,r+1,k+1,F+k);
					}
					for(int c=1;c<=ds&&(tk||tr<=ls);c++){//move c nodes into tree
						sum+=dlst[c];
						if(tk){
							--tk;
						}else{
							tr=nxt[tr],sum+=tr-t;
						}
						upd(nf,ntag,l,tr,tk,sum+tk);
						if(t==tr&&str[lst[tr+1]]=='X'){
							upd(nf,ntag,l,tr+1,tk+1,sum+tk);
						}
					}
				}
			}
		}
	}
	printf("%d\n",tag[ls][ls][0]==ls+1?f[ls][ls][0]+ls:-1);
	return 0;
}
