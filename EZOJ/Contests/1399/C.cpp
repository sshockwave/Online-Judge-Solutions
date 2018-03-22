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
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=100010,B=320,INF=0x7f7f7f7f;
int rt,bs;//bs==n/rt
struct Blk{
	int val[B];
}pool[N],blkans[N];//[b,i)
struct Summer{
	Blk *id[B],sum;
	inline void ins(int x,Blk* nn){
		int b=x/rt;
		if(id[b]){
			*nn=*id[b];
		}
		id[b]=nn;
		for(int i=x%rt;i<rt;i++){
			id[b]->val[i]++;
		}
		for(int i=b+1;i<=bs;i++){
			sum.val[i]++;
		}
	}
	inline int ask(int p){
		return id[p/rt]->val[p%rt]+sum.val[p/rt];
	}
}atpos[N];
int lend[N],rend[N],eve[N];
int pos[N],mvp[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("board.in","r",stdin);
	freopen("board.out","w",stdout);
#endif
	int n=ni,m=ni,tot=ni,tp=ni;
	for(rt=1;rt*rt<=m;rt++);
	bs=m/rt;
	for(int i=1;i<=n;i++){
		lend[i]=ni,rend[i]=ni;
		eve[lend[i]]=i;
		eve[rend[i]]=-i;
		pos[i]=m+1;
	}
	set<int>s;
	memset(blkans,127,sizeof(blkans));
	for(int i=0;i<=bs;i++){
		atpos[m+1].id[i]=pool;
	}
	for(int i=m;i>=1;i--){
		if(eve[i]){
			int x=cabs(eve[i]);
			set<int>::iterator it=s.upper_bound(x);
			if(eve[i]<0){
				s.insert(x);
			}else{
				s.erase(x);
			}
			if(it!=s.end()){
				mvp[i]=*it;
				atpos[i]=atpos[pos[*it]],pos[*it]=i;
				atpos[i].ins(i,pool+i);
			}
		}
		if(i%rt==0){
			int ans=INF,b=i/rt;
			for(int j=m;j>=i;j--){
				int cur=ans;
				if(eve[j]){
					if(eve[j]<0&&lend[-eve[j]]<=i){
						apmin(ans,atpos[pos[-eve[j]]].ask(j));
						cur=ans;
					}
					if(mvp[j]&&lend[mvp[j]]<=i){
						int tmp=atpos[pos[mvp[j]]].ask(j);
						apmin(cur,tmp-(eve[j]<0));
						apmin(ans,tmp-1);
					}
				}
				blkans[j].val[b]=cur;
			}
		}
	}
	for(int lastans=0;tot--;){
		int l=ni,r=ni;
		if(tp){
			l^=lastans,r^=lastans;
		}
		int ans=blkans[r].val[l/rt];
		for(int i=l/rt*rt;i<=l;i++){
			if(eve[i]>0&&rend[eve[i]]>=r){
				apmin(ans,atpos[pos[eve[i]]].ask(r)-(eve[r]<0&&mvp[r]==eve[i]));
			}
			if(mvp[i]&&rend[mvp[i]]>=r){
				apmin(ans,atpos[i].ask(r)-(eve[i]>0||i<l)-(eve[r]<0&&mvp[r]==mvp[i]));
			}
		}
		if(ans<INF){
			lastans=ans;
		}else{
			ans=-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
