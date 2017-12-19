#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
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
const int N=200010,O=370137601,INF=0x7f7f7f7f;
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
int statcnt[4]={0,2,4,9},scnt,m,k;
struct Mat{
	int *a[90];
	inline void init(){
		for(int i=0;i<scnt;i++){
			a[i]=new int[scnt];
		}
	}
	inline void clr(){
		for(int i=0;i<scnt;i++){
			memset(a[i],0,scnt<<2);
		}
	}
	inline void operator = (const Mat &b){
		for(int i=0;i<scnt;i++){
			memcpy(a[i],b.a[i],scnt<<2);
		}
	}
	inline void getmul(const Mat &x,const Mat &y){
		for(int i=0;i<scnt;i++){
			for(int j=0;j<scnt;j++){
				lint tmp=0;
				for(int k=0;k<scnt;k++){
					tmp+=(lint)x.a[i][k]*y.a[k][j]%O;
				}
				a[i][j]=tmp%O;
			}
		}
	}
	inline int eval(){
		lint ans=0;
		for(int i=0;i<statcnt[m];i++){
			ans+=a[i][0];
		}
		return ans%O;
	}
}trans,tmpmat;
int str[9][9];
inline void gtrans(Mat &trans,int prob[]){
	static int statprob[9];
	for(int i=0,ti=1<<m;i<ti;i++){
		lint tmp=1;
		for(int j=0;j<m;j++){
			(tmp*=(i>>j)&1?O+1-prob[j]:prob[j])%=O;
		}
		statprob[i]=tmp;
	}
	statprob[8]=statprob[5];
	trans.clr();
	int tmp=statcnt[m];
	for(int i=0;i<k;i++){
		for(int j=0;j<tmp;j++){//i*tmp+j
			for(int l=0;l<tmp;l++){//to->
				if(str[j][l]<INF){
					trans.a[(i+str[j][l]+k)%k*tmp+l][i*tmp+j]=statprob[l];
				}
			}
		}
	}
}
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
	for(int i=0;i<statcnt[m];i++){
		memset(mp,0,sizeof(mp));
		putstat(mp[0],i);
		int oldv=gcomp(i);
		for(int j=0;j<statcnt[m];j++){
			putstat(mp[1],j);
			int newv=gcomp(i);
			if(j==5&&bln[1][0]==bln[1][2]){
				str[i][j]=INF;
			}else if(j==8&&bln[1][0]!=bln[1][2]){
				str[i][j]=INF;
			}else{
				str[i][j]=newv-oldv;
			}
		}
	}
}
int prob[N][3];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		Mat mat;
		inline void up(){
			mat.getmul(rson->mat,lson->mat);
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->mat.init();
		if(l==r){
			x->mat=trans;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void alt(node x,int p){
		if(x->l==x->r){
			gtrans(x->mat,prob[p]);
		}else{
			alt(p<=x->m?x->lson:x->rson,p);
			x->up();
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("kami.in","r",stdin);
	freopen("kami.out","w",stdout);
#endif
	int n=ni;
	m=ni,k=ni;
	int tot=ni;
	gstr();
	scnt=statcnt[m]*k;
	trans.init();
	{
		int p=ni%O;
		p=(lint)p*inv(ni%O)%O;
		for(int i=1;i<=n;i++){
			for(int j=0;j<m;j++){
				prob[i][j]=p;
			}
		}
		gtrans(trans,prob[1]);
	}
	if(tot==0){
		assert((n^(n&-n))==0);
		tmpmat.init();
		for(;n>1;n>>=1){
			tmpmat.getmul(trans,trans);
			trans=tmpmat;
		}
		printf("%d\n",trans.eval());
		return 0;
	}
	seg::rt=seg::build(1,n);
	while(printf("%d\n",seg::rt->mat.eval()),tot--){
		int x=ni,y=ni-1;
		prob[x][y]=ni%O;
		prob[x][y]=(lint)prob[x][y]*inv(ni%O)%O;
		seg::alt(seg::rt,x);
	}
	return 0;
}
