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
const int N=200010,O=370137601,INF=0x7f7f7f7f,K=10;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int statcnt[4]={0,2,4,9},m,k,sm;
int str[9][9];
struct Mat{
	int a[9][9];
	inline void clr(){
		for(int i=0;i<sm;i++){
			memset(a[i],0,sm<<2);
		}
	}
	inline void getmul(const Mat &x,const Mat &y){
		for(int i=0;i<sm;i++){
			for(int j=0;j<sm;j++){
				lint tmp=0;
				for(int k=0;k<sm;k++){
					tmp+=(lint)x.a[i][k]*y.a[k][j]%O;
				}
				a[i][j]=tmp%O;
			}
		}
	}
	inline int eval(){
		lint ans=0;
		for(int i=0;i<sm;i++){
			ans+=a[i][0];
		}
		return ans%O;
	}
	inline void gtrans(int prob[],int w[K]){
		static int statprob[9];
		for(int i=0,ti=1<<m;i<ti;i++){
			lint tmp=1;
			for(int j=0;j<m;j++){
				(tmp*=(i>>j)&1?O+1-prob[j]:prob[j])%=O;
			}
			statprob[i]=tmp;
		}
		statprob[8]=statprob[5];
		clr();
		for(int j=0;j<sm;j++){
			for(int l=0;l<sm;l++){
				if(str[j][l]<INF){
					a[l][j]=(lint)statprob[l]*w[str[j][l]]%O;
				}
			}
		}
	}
}trans[19][K];
bool mp[2][3];
int bln[2][3];
void dfs(int x,int y,bool flag){
	const static int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
	for(int d=0;d<4;d++){
		int tx=x+dx[d],ty=y+dy[d];
		if(tx>=0&&tx<=1&&ty>=0&&ty<m&&mp[tx][ty]&&bln[tx][ty]==0){
			bln[tx][ty]=bln[x][y];
			dfs(tx,ty,flag);
		}
	}
	if(flag&&x==0&&(y==0||y==2)&&bln[0][2-y]==0){
		assert(m==3);
		bln[0][2-y]=bln[x][y];
		dfs(0,2-y,true);
	}
}
inline int gcomp(int s){
	memset(bln,0,sizeof(bln));
	int tim=0;
	for(int i=0;i<2;i++){
		for(int j=0;j<m;j++){
			if(mp[i][j]&&bln[i][j]==0){
				bln[i][j]=++tim;
				dfs(i,j,s==8);
			}
		}
	}
	return tim;
}
inline void putstat(bool mp[],int s){
	if(s==8){
		mp[0]=1,mp[1]=0,mp[2]=1;
	}else for(int i=0;i<m;i++){
		mp[i]=(s>>i)&1;
	}
}
inline void gstr(){
	for(int i=0;i<sm;i++){
		memset(mp,0,sizeof(mp));
		putstat(mp[0],i);
		int oldv=gcomp(i);
		for(int j=0;j<sm;j++){
			putstat(mp[1],j);
			int newv=gcomp(i);
			if(j==5&&bln[1][0]==bln[1][2]){
				str[i][j]=INF;
			}else if(j==8&&bln[1][0]!=bln[1][2]){
				str[i][j]=INF;
			}else{
				str[i][j]=(newv-oldv+k)%k;
			}
		}
	}
}
int prob[N][3];
int om[K][K],io[K];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		Mat *mat[K];
		int sh;
		bool vis;
		inline Mat& gmat(int i){
			return vis?*mat[i]:trans[sh][i];
		}
		inline void up(){
			assert(vis);
			for(int i=0;i<k;i++){
				mat[i]->getmul(lson->gmat(i),rson->gmat(i));
			}
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->vis=false;
		if(l==r){
			x->sh=1;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			assert(x->lson->sh==x->rson->sh);
			x->sh=x->lson->sh+1;
		}
		return x;
	}
	void alt(node x,int p){
		if(!x->vis){
			x->vis=true;
			for(int i=0;i<k;i++){
				x->mat[i]=new Mat;
			}
		}
		if(x->l<x->r){
			alt(p<=x->m?x->lson:x->rson,p);
			x->up();
		}else for(int i=0;i<k;i++){
			x->mat[i]->gtrans(prob[p],om[i]);
		}
	}
}
inline void idft(int a[],int n){
	static int b[K];
	for(int i=0;i<n;i++){
		int w=1,wn=io[i];
		lint tmp=0;
		for(int j=0;j<n;j++,w=(lint)w*wn%O){
			tmp+=(lint)a[j]*w%O;
		}
		b[i]=tmp%O;
	}
	int iv=inv(n);
	for(int i=0;i<n;i++){
		a[i]=(lint)b[i]*iv%O;
	}
}
inline int work(){
	static int a[K];
	for(int i=0;i<k;i++){
		a[i]=seg::rt->gmat(i).eval();
	}
	idft(a,k);
	return a[0];
}
inline int nextfrac(){
	int p=ni,q=ni;
	return (lint)p*inv(q)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("kami.in","r",stdin);
	freopen("kami.out","w",stdout);
#endif
	int n=ni;
	m=ni,k=ni,sm=statcnt[m];
	int tot=ni;
	gstr();
	for(int i=0,w=1,wn=fpow(37,(O-1)/k);i<k;i++,w=(lint)w*wn%O){
		om[i][0]=1,io[i]=inv(w);
		for(int j=1;j<k;j++){
			om[i][j]=(lint)om[i][j-1]*w%O;
		}
	}
	{
		int p=nextfrac();
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				prob[i][j]=p;
			}
		}
	}
	for(int i=0;i<k;i++){
		trans[1][i].gtrans(prob[0],om[i]);
		for(int j=2;j<=18;j++){
			trans[j][i].getmul(trans[j-1][i],trans[j-1][i]);
		}
	}
	seg::rt=seg::build(0,n-1);
	while(printf("%d\n",work()),tot--){
		int x=ni-1,y=ni-1;
		prob[x][y]=nextfrac();
		seg::alt(seg::rt,x);
	}
	return 0;
}
