#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=100,INF=0x7f7f7f7f;
bool con[N][N];
int lim;
void getcon(){
	cout<<endl;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=4;j++){
			cout<<con[i][j];
		}
		cout<<endl;
	}
}
namespace dlx{
	const int N2=::N*::N;
	struct Pt{
		int l,r,u,d;
		int row,col;
	}pt[N2];
	int n,m;
	int ncnt;
	inline int nn(int r,int c){
		++ncnt;
		pt[ncnt].row=r;
		pt[ncnt].col=c;
		return ncnt;
	}
	int nd[N][N];
	int vis[N];
	inline void del_h(int x){
		if(vis[x]++==0){
			x=nd[0][x];
			pt[pt[x].l].r=pt[x].r;
			pt[pt[x].r].l=pt[x].l;
		}
	}
	inline void ins_h(int x){
		if(--vis[x]==0){
			x=nd[0][x];
			pt[pt[x].l].r=x;
			pt[pt[x].r].l=x;
		}
	}
	inline void del_v(int x){
		pt[pt[x].d].u=pt[x].u;
		pt[pt[x].u].d=pt[x].d;
	}
	inline void ins_v(int x){
		pt[pt[x].d].u=x;
		pt[pt[x].u].d=x;
	}
	inline int est(){
		static bool cov[N];
		mset(cov+1,0,m);
		int ans=0;
		for(int i=pt[nd[0][0]].r;i!=nd[0][0];i=pt[i].r){
			if(!cov[pt[i].col]){
				++ans;
				cov[pt[i].col]=true;
				for(int j=pt[i].d;j!=i;j=pt[j].d){
					for(int k=pt[j].r;k!=j;k=pt[k].r){
						cov[pt[k].col]=true;
					}
				}
			}
		}
		return ans;
	}
	inline int getrt(){
		int p=-1,ps=INF;
		for(int i=pt[nd[0][0]].r;i!=nd[0][0];i=pt[i].r){
			int cnt=0;
			for(int j=pt[i].d;j!=i;j=pt[j].d){
				++cnt;
			}
			if(cnt<ps){
				p=i,ps=cnt;
			}
		}
		return p;
	}
	int ccnt=0;
	bool dfs(){
		if(pt[nd[0][0]].r==nd[0][0])return true;
		if(ccnt==lim)return false;
		if(ccnt+est()>lim)return false;
		++ccnt;
		int rt=getrt();
		vector<int>stk;
		for(int i=pt[rt].d;i!=rt;i=pt[i].d){
			stk.push_back(i);
			int j=i;
			do{
				del_h(pt[j].col);
				del_v(j);
			}while(j=pt[j].r,j!=i);
			if(dfs())return true;
			j=i;
			do{
				ins_h(pt[j].col);
			}while(j=pt[j].r,j!=i);
		}
		for(;!stk.empty();stk.pop_back()){
			const int i=stk.back();
			int j=i;
			do{
				ins_v(j);
			}while(j=pt[j].r,j!=i);
		}
		--ccnt;
		return false;
	}
	bool main(int _n,int _m){
		n=_n,m=_m;
		ncnt=0;
		for(int j=0;j<=m;j++){
			nd[0][j]=nn(0,j);
		}
		for(int j=0;j<=m;j++){
			pt[nd[0][j]].l=nd[0][j>0?j-1:m];
			pt[nd[0][j]].r=nd[0][j<m?j+1:0];
		}
		for(int i=1;i<=n;i++){
			int fir=0,last=0;
			for(int j=1;j<=m;j++){
				nd[i][j]=con[i][j]?nn(i,j):0;
				if(nd[i][j]){
					if(last){
						pt[last].r=nd[i][j];
						pt[nd[i][j]].l=last;
					}else{
						fir=nd[i][j];
					}
					last=nd[i][j];
				}
			}
			if(fir){
				pt[last].r=fir;
				pt[fir].l=last;
			}
		}
		for(int j=1;j<=m;j++){
			int last=nd[0][j];
			for(int i=1;i<=n;i++){
				if(nd[i][j]==0)continue;
				pt[last].d=nd[i][j];
				pt[nd[i][j]].u=last;
				last=nd[i][j];
			}
			pt[last].d=nd[0][j];
			pt[nd[0][j]].u=last;
		}
		mset(vis+1,0,m);
		ccnt=0;
		return dfs();
	}
}
int val[N];
char s1[N],s2[N],t[N];
inline int calc(char s[],int i,int j){
	return cabs(s[i]-t[j])+val[cabs(i-j)];
}
int n;
inline int Main(){
	n=ni;
	lim=ni;
	for(int i=0;i<n;i++){
		val[i]=ni;
	}
	scanf("%s%s%s",s1+1,s2+1,t+1);
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			apmax(r,calc(s1,i,j));
			apmax(r,calc(s2,i,j));
		}
	}
	for(;l<r;){
		const int m=(l+r)>>1;
		for(int j=1;j<=n;j++){
			for(int i=1;i<=n;i++){
				con[j][i]=calc(s1,i,j)<=m;
				con[j][i+n]=calc(s2,i,j)<=m;
			}
		}
		if(dlx::main(n,n<<1)){
			r=m;
		}else{
			l=m+1;
		}
	}
	return l;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
#endif
	for(int i=1,tot=ni;i<=tot;i++){
		printf("Case #%d: %d\n",i,Main());
	}
	return 0;
}
