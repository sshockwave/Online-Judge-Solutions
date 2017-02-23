#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x7f7f7f7f
#define N 500010
#define D 2000100
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
struct interval{
	int l,r;
}inv[N];
bool operator < (interval a,interval b){
	return a.r-a.l<b.r-b.l;
}
struct point{
	int x,*bln;
}pt[N*2];
bool operator < (point a,point b){
	return a.x<b.x;
}
int lson[D],rson[D],lend[D],rend[D],mid[D],val[D],delta[D],ntop=0;
int build(int l,int r){
	int x=ntop++;
	lend[x]=l,rend[x]=r,mid[x]=(l+r)>>1;
	if(l==r){
		return x;
	}
	lson[x]=build(l,mid[x]);
	rson[x]=build(mid[x]+1,r);
	return x;
}
inline void push_down(int x){
	if(delta[x]){
		val[lson[x]]+=delta[x];
		val[rson[x]]+=delta[x];
		delta[lson[x]]+=delta[x];
		delta[rson[x]]+=delta[x];
		delta[x]=0;
	}
}
inline void push_up(int x){
	val[x]=max(val[lson[x]],val[rson[x]]);
}
void alter(int x,int l,int r,int w){
	if(l==lend[x]&&r==rend[x]){
		val[x]+=w,delta[x]+=w;
		return;
	}
	push_down(x);
	if(r<=mid[x]){
		alter(lson[x],l,r,w);
	}else if(l>mid[x]){
		alter(rson[x],l,r,w);
	}else{
		alter(lson[x],l,mid[x],w);
		alter(rson[x],mid[x]+1,r,w);
	}
	push_up(x);
}
int main(){
//	freopen("4653.in","r",stdin);
	int n=next_int(),m=next_int(),maxx=-1,ans=INF;
	for(int i=0;i<n;i++){
		inv[i].l=next_int();
		inv[i].r=next_int();
	}
	sort(inv,inv+n);
	for(int i=0;i<n;i++){
		pt[i<<1].x=inv[i].l;
		pt[(i<<1)|1].x=inv[i].r;
		pt[i<<1].bln=&inv[i].l;
		pt[(i<<1)|1].bln=&inv[i].r;
	}
	sort(pt,pt+n*2);
	for(int i=0,last=-1;i<(n<<1);i++){
		if(pt[i].x!=last){
			last=pt[i].x;
			maxx++;
		}
		*(pt[i].bln)=maxx;
	}
	memset(delta,0,sizeof(delta));
	memset(val,0,sizeof(val));
	int root=build(0,maxx);
	for(int i=0,j=-1;i<n;i++){
		while(val[root]<m){
			if((++j)>=n){
				break;
			}
			alter(root,inv[j].l,inv[j].r,1);
		}
		if(j>=n){
			break;
		}
		apmin(ans,inv[j].r-inv[j].l-inv[i].r+inv[i].l);
		alter(root,inv[i].l,inv[i].r,-1);
	}
	printf("%d",ans==INF?-1:ans);
}
