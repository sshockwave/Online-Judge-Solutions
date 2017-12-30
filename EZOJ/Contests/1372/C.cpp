#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=1000010,M=310,INF=0x7f7f7f7f;
int rest[M][M];
struct pii{
	int l,r;
	inline int len(){
		return l?r-l+1:INF;
	}
}intv[N],ban[M][M];
int mxrm[M][M],mnrm[M][M];
int val[N],lst[N];
inline bool lcmp(int a,int b){
	return val[a]<val[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("heike.in","r",stdin);
	freopen("heike.out","w",stdout);
#endif
	ni;
	int len=ni,n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		intv[i]=(pii){ni,ni};
		val[i]=ni;
		lst[i]=i;
	}
	sort(lst+1,lst+n+1,lcmp);
	memset(ban,0,sizeof(ban));
	memset(mxrm,0,sizeof(mxrm));
	memset(mnrm,127,sizeof(mnrm));
	memset(rest,0,sizeof(rest));
	for(int i=1;i<=len;i++){
		for(int j=i;j<=len;j++){
			rest[i][j]=j-i+1;
		}
	}
	int ans=0;
	for(int i=n;i>=1;i--){
		int x=lst[i];
		int l=intv[x].l,r=intv[x].r;
		if(ban[l][r].l){//insert fail
			apmax(mxrm[ban[l][r].l][ban[l][r].r],val[x]);
		}else{//insert success
			ans+=val[x];
			for(int a=1;a<=l;a++){
				for(int b=r;b<=len;b++){
					rest[a][b]--;
					mnrm[a][b]=val[x];
				}
			}
			{//gban
				for(int y=len;y>=1;y--){
					pii cur=(pii){0,0};
					for(int x=1;x<=y;x++){
						if(rest[x][y]==0){
							cur=(pii){x,y};
						}
						ban[x][y]=y<len&&ban[x][y+1].len()<cur.len()?ban[x][y+1]:cur;
					}
				}
			}
		}
	}
	for(int y=len;y>=1;y--){
		int cur=0;
		for(int x=1;x<=y;x++){
			apmax(mxrm[x][y],cur);
			cur=mxrm[x][y];
			if(y<len){
				apmax(mxrm[x][y],mxrm[x][y+1]);
			}
		}
	}
	printf("%d\n",ans);
	while(tot--){
		if(ni==1){//insert
			int l=ni,r=ni,v=ni;
			if(ban[l][r].l){
				int x=ban[l][r].l,y=ban[l][r].r;
				printf("%d\n",max(ans,ans-mnrm[x][y]+v));
			}else{
				printf("%d\n",ans+v);
			}
		}else{//delete
			int x=ni;
			int l=intv[x].l,r=intv[x].r;
			printf("%d\n",ans-val[x]+mxrm[l][r]);
		}
	}
	return 0;
}
