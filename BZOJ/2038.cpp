#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
const int N=50010;
int color[N],rt;
struct query{
	int l,r,id;
}q[N];
struct Answer{
	lint up,down;
	inline void set(lint u,lint d){
		if(u==0){
			up=0,down=1;
		}else{
			int g=gcd(u,d);
			up=u/g,down=d/g;
		}
	}
}ans[N];
inline bool operator < (const query &a,const query &b){
	if(a.l/rt==b.l/rt){
		return a.r<b.r;
	}
	return a.l<b.l;
}
int ccnt[N];
int main(){
	int n=ni(),tot=ni();
	for(int i=0;i<n;i++){
		color[i]=ni();
		if(i*i<=n){
			rt=i;
		}
	}
	for(int toti=0;toti<tot;toti++){
		q[toti]=(query){ni()-1,ni()-1,toti};
	}
	sort(q,q+tot);
	lint sum=1,up=0;
	memset(ccnt,0,sizeof(ccnt));
	int l=0,r=0;
	ccnt[color[0]]=1;
	for(int i=0;i<tot;i++){
		for(;l<q[i].l;l++){
			sum--,ccnt[color[l]]--,up-=ccnt[color[l]];
		}
		while(l>q[i].l){
			l--;
			sum++,up+=ccnt[color[l]],ccnt[color[l]]++;
		}
		for(;r>q[i].r;r--){
			sum--,ccnt[color[r]]--,up-=ccnt[color[r]];
		}
		while(r<q[i].r){
			r++;
			sum++,up+=ccnt[color[r]],ccnt[color[r]]++;
		}
		ans[q[i].id].set(up,sum*(sum-1)/2);
	}
	for(int i=0;i<tot;i++){
		printf("%lld/%lld\n",ans[i].up,ans[i].down);
	}
}
