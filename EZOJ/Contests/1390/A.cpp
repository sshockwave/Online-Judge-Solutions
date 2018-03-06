#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T sgn(const T &x){return x>0?1:x<0?-1:0;}
const int N=1010;
struct Pt{
	int x,y;
	inline lint d2()const{return sqr<lint>(x)+sqr<lint>(y);}
	inline friend bool operator == (const Pt &a,const Pt &b){return a.x==b.x&&a.y==b.y;}
	inline friend Pt operator + (const Pt &a,const Pt &b){return (Pt){a.x+b.x,a.y+b.y};}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend lint dot(const Pt &a,const Pt &b){return (lint)a.x*b.x+(lint)a.y*b.y;}
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;}
	inline friend bool samedir(const Pt &a,const Pt &b){return crs(a,b)==0&&dot(a,b)>0;}
}pt[N<<1],base;
inline bool polarcmp(const Pt &a,const Pt &b){
	lint tmp=(lint)a.y*b.y;
	if(tmp<0)return a.y>0;
	if(tmp>0)return tmp=crs(a,b),tmp?tmp>0:a.d2()<b.d2();
	if(a.y==0){
		if(b.y==0)return a.x>0?b.x>a.x||b.x<0:b.x<a.x;
		return a.x>0?true:b.y<0;
	}else return b.x<0&&a.y>0;
}
inline bool polarcmpint(int a,int b){
	return polarcmp(pt[a]-base,pt[b]-base);
}
namespace conv{
	int stk[N],ss;
	inline void psh(int p){
		Pt w=pt[p];
		for(;ss>1;ss--){
			Pt u=pt[stk[ss-2]];
			Pt v=pt[stk[ss-1]];
			if(crs(v-u,w-v)<0)break;
		}
		stk[ss++]=p;
	}
	int pre[N],nxt[N],bln[N];
	inline void init(){
		memset(pre,0,sizeof(pre));
		memset(nxt,0,sizeof(nxt));
		memset(bln,0,sizeof(bln));
	}
	inline void build(){
		for(int i=0;i<ss-1;i++){
			nxt[stk[i]]=stk[i+1];
			pre[stk[i+1]]=stk[i];
		}
	}
}
int n;
inline bool judge(int i,int j){
	if(conv::bln[i]==0)return true;
	Pt a=pt[conv::pre[i]]-base,b=pt[conv::nxt[i]]-base,t=pt[j]-base;
	lint at=crs(a,t),bt=crs(b,t);
	if(a==b)return at>0||(at==0&&dot(a,t)<0);
	if(bt==0)return false;
	if(at==0)return dot(a,t)<0;
	return at>0&&bt>0;
}
int lst[N<<1],rnk[N<<1];
int tag[N],tim=0;
int nxtdiff[N<<1];
int b[N<<1];
inline int work(int x){
	if(conv::bln[x]&&conv::pre[x]==0)return 0;
	base=pt[x];
	int ls=0;
	for(int i=1;i<=n;i++){
		if(i!=x){
			lst[++ls]=i;
			lst[++ls]=i+n;
			pt[i+n]=base+base-pt[i];
		}
	}
	sort(lst+1,lst+ls+1,polarcmpint);
	for(int i=ls;i>=1;i--){
		rnk[lst[i]]=i;
		if(i==ls){
			nxtdiff[i]=ls+1;
		}else{
			nxtdiff[i]=samedir(pt[lst[i]]-base,pt[lst[i+1]]-base)?nxtdiff[i+1]:(i+1);
		}
	}
	memset(b+1,0,ls*sizeof(b[0]));
	tag[x]=++tim;
	for(int i=1;i<=n;i++){
		if(tag[i]==tim)continue;
		if(conv::bln[i]==0){
			b[rnk[i]+1]++,b[nxtdiff[rnk[i]]]--;
		}else if(conv::pre[i]&&conv::bln[i]!=conv::bln[x]){
			bool flag=false;
			int l=i,r=i;
			for(int j=i;tag[j]<tim;j=conv::nxt[j]){
				tag[j]=tim;
				flag|=crs(pt[j]-base,pt[conv::pre[j]]-base)<0;
				lint tmp=crs(pt[r]-base,pt[j]-base);
				if(tmp>0){
					r=j;
				}else if(tmp==0&&(pt[r]-base).d2()<(pt[j]-base).d2()){
					r=j;
				}
				tmp=crs(pt[l]-base,pt[j]-base);
				if(tmp<0){
					l=j;
				}else if(tmp==0&&(pt[l]-base).d2()>(pt[j]-base).d2()){
					l=j;
				}
			}
			if(conv::pre[i]==conv::nxt[i]){
				int a=conv::pre[i],b=i;
				if(crs(pt[a]-base,pt[b]-base)==0&&dot(pt[a]-base,pt[b]-base)<0)return 0;
			}else if(!flag)return 0;
			b[rnk[l]+1]++,b[nxtdiff[rnk[r]]]--;
			if(rnk[l]>rnk[r]){
				b[1]++;
			}
			l+=n,r+=n;
			b[nxtdiff[rnk[l]]]++,b[nxtdiff[rnk[r]]]--;
			if(rnk[l]>rnk[r]){
				b[1]++;
			}
		}
	}
	int ans=0,sum=0;
	for(int i=1;i<=ls;i++){
		sum+=b[i];
		ans+=sum==0&&lst[i]<=n&&judge(x,lst[i]);
	}
	return ans;
}
inline bool xcmp(int a,int b){
	return pt[a].x!=pt[b].x?pt[a].x<pt[b].x:pt[a].y<pt[b].y;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("inherit.in","r",stdin);
	freopen("inherit.out","w",stdout);
#endif
	conv::init();
	n=ni;
	int m=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	for(int i=1;i<=m;i++){
		int k=ni;
		for(int j=1;j<=k;j++){
			lst[j]=ni;
			conv::bln[lst[j]]=i;
		}
		if(k==1){
			conv::bln[lst[1]]=0;
			continue;
		}
		sort(lst+1,lst+k+1,xcmp);
		conv::ss=0;
		for(int j=1;j<=k;j++){
			conv::psh(lst[j]);
		}
		conv::build();
		conv::ss=0;
		for(int j=k;j>=1;j--){
			conv::psh(lst[j]);
		}
		conv::build();
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=work(i);
	}
	assert((ans&1)==0);
	printf("%d\n",ans>>1);
	return 0;
}
