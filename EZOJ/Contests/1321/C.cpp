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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010;
int n,m,a[N];
struct Query{
	int op,l,r,x;
}q[N];
namespace brute{
	int tag[N*2],tim=0,ans;
	inline void upd(int x){
		if(tag[x]<tim){
			ans++;
			tag[x]=tim;
		}
	}
	inline int cntans(int l,int r){
		tim++,ans=0;
		for(int i=l;i<=r;i++){
			upd(a[i]);
		}
		return ans;
	}
	inline void work(){
		for(int i=1;i<=m;i++){
			if(q[i].op==1){
				for(int j=q[i].l;j<=q[i].r;j++){
					a[j]=q[i].x;
				}
			}else{
				printf("%d\n",cntans(q[i].l,q[i].r));
			}
		}
	}
}
namespace task2{
	int rt;
	int ql[N];
	inline bool qcmp(const int &a,const int &b){
		int x=q[a].l/rt,y=q[b].l/rt;
		return x==y?q[a].r<q[b].r:x<y;
	}
	int cnt[N*2],ans=0;
	inline void inc(int x){
		if(cnt[x]==0){
			ans++;
		}
		cnt[x]++;
	}
	inline void dec(int x){
		cnt[x]--;
		if(cnt[x]==0){
			ans--;
		}
	}
	int qans[N];
	inline void work(){
		for(rt=0;rt*rt<n;rt++);
		for(int i=1;i<=m;i++){
			ql[i]=i;
		}
		sort(ql+1,ql+m+1,qcmp);
		memset(cnt,0,sizeof(cnt));
		int l=1,r=1;
		inc(a[1]);
		for(int i=1;i<=m;i++){
			int x=ql[i];
			for(;l<q[x].l;dec(a[l++]));
			for(;l>q[x].l;inc(a[--l]));
			for(;r<q[x].r;inc(a[++r]));
			for(;r>q[x].r;dec(a[r--]));
			qans[x]=ans;
		}
		for(int i=1;i<=m;i++){
			printf("%d\n",qans[i]);
		}
	}
}
int *num[N*2],ns=0;
inline bool numcmp(int* a,int* b){
	return *a<*b;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
#endif
	n=ni,m=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		num[ns++]=a+i;
	}
	bool noc=true;
	for(int i=1;i<=m;i++){
		q[i]=(Query){ni,ni,ni};
		if(q[i].op==1){
			q[i].x=ni;
			num[ns++]=&q[i].x;
			noc=false;
		}
	}
	sort(num,num+ns,numcmp);
	for(int i=0,j=0,v=-1;i<ns;i++){
		if(v!=*num[i]){
			v=*num[i];
			j++;
		}
		*num[i]=j;
	}
	if(n<=2000&&m<=2000){
		brute::work();
	}else if(noc){
		task2::work();
	}
}
