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
const int N=410;
int val[N][N],n1,n2;
int lab1[N],lab2[N],lnk1[N],lnk2[N];
int sla[N]={-1},pre[N]={0};//n2
inline void km(int x){
	int y=0;
	lnk2[0]=x;
	memset(sla+1,127,n2<<2);
	do{
		y=0;
		for(int i=1;i<=n2;i++){
			if(~sla[i]){
				if(lab1[x]+lab2[i]-val[x][i]<sla[i]){
					sla[i]=lab1[x]+lab2[i]-val[x][i],pre[i]=x;
				}
				if(y==0||sla[i]<sla[y]){
					y=i;
				}
			}
		}
		assert(y);
		int dt=sla[y];
		for(int i=1;i<=n1;i++){
			if(sla[lnk1[i]]==-1){
				lab1[i]-=dt;
			}
		}
		for(int i=1;i<=n2;i++){
			if(sla[i]==-1){
				lab2[i]+=dt;
			}else{
				sla[i]-=dt;
				assert(sla[i]>=0);
			}
		}
		assert(sla[y]==0);
		sla[y]=-1;
	}while((x=lnk2[y]));
	while((x=pre[y])){
		lnk2[y]=x;
		swap(lnk1[x],y);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
#endif
	n1=ni,n2=max(ni,n1);
	memset(val,0,sizeof(val));
	memset(lab1,0,sizeof(lab1));
	memset(lab2,0,sizeof(lab2));
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		apmax(lab1[u],val[u][v]=ni);
	}
	memset(lnk1,0,sizeof(lnk1));
	memset(lnk2,0,sizeof(lnk2));
	for(int i=1;i<=n1;i++){
		km(i);
	}
	lint ans=0;
	for(int i=1;i<=n1;i++){
		ans+=lab1[i];
	}
	for(int i=1;i<=n2;i++){
		ans+=lab2[i];
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n1;i++){
		printf("%d ",val[i][lnk1[i]]?lnk1[i]:0);
	}
	putchar('\n');
	return 0;
}
