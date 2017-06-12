#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cctype>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=110,C=100000010,INF=0x7f7f7f7f;
struct HashMap{
	const static int E=1000000,MOD=10000019;
	lint to[E];
	int val[E],bro[E],head[MOD],e;
	HashMap():e(0){
		memset(head,-1,sizeof(head));
	}
	inline bool add(lint u,int v){
		int x=u%MOD;
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]==u){
				return false;
			}
		}
		to[e]=u,val[e]=v,bro[e]=head[x],head[x]=e++;
		return true;
	}
}H,B;
namespace M{
	const int E=HashMap::E;
	struct pii{
		int f,n;
		inline friend bool operator < (const pii &a,const pii &b){
			return a.f<b.f;
		}
	}p[E];
	inline void init(){
		int n=H.e;
		for(int i=0;i<n;i++){
			p[i]=(pii){(int)H.to[i],H.val[i]};
		}
		sort(p,p+n);
		p[0].n=0;
	}
	inline int lb(int c){
		int l=0,r=H.e-1;
		while(l<r){
			int mid=((l+r)>>1)+1;
			if(p[mid].f>c){
				r=mid-1;
			}else{
				l=mid;
			}
		}
		return l;
	}
	inline bool one(int n,int c){
		return false;
	}
	inline bool work(int n,int c){
		if(n>=c){
			return true;
		}
		for(int i=lb(c);i>=0&&c-p[i].f<=n;i--){
			if(p[i].n<n&&c-p[i].f<n-p[i].n){
				return true;
			}
		}
		for(int i=0,j=lb(c);i<=j&&p[i].f<=c;i++){
			for(;i<=j&&p[i].f+p[j].f>c;j--);
			if(p[i].n<=n-2){
				for(int k=j;i<=k&&c-p[i].f-p[k].f<=n-p[i].n-2;k--){
					if(p[i].n+p[k].n<=n-2&&c-p[i].f-p[k].f<=n-p[i].n-p[k].n-2){
						return true;
					}
				}
			}
		}
		return false;
	}
}
struct pti{
	int n,f,l;
	pti(int _n,int _f,int _l):n(_n),f(_f),l(_l){}
	inline void spawn();
};
int lim;
queue<pti>q;
inline void pti::spawn(){
	if(!B.add((lint)f*N+l,n)){
		return;
	}
	H.add(f,n);
	if((lint)f*l<C){
		if(n+2<lim){
			q.push(pti(n+1,f,l+1));
		}
		if(l>1){
			q.push(pti(n+1,f*l,l));
		}
	}
}
int a[N],w[N],f[N][N];
int main(){
	srand(time(NULL));
	int n=ni,tot=ni,mxval=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		w[i]=ni;
	}
	memset(f,-1,sizeof(f));
	f[0][0]=mxval;
	lim=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			if(f[i-1][j]>=a[i]){
				f[i][j]=f[i-1][j]-a[i];
			}
			if(j&&f[i-1][j-1]>=a[i]){
				apmax(f[i][j],f[i-1][j-1]-a[i]+w[i]);
			}
			apmin(f[i][j],mxval);
		}
		int j=0;
		for(;j<=i&&f[i][j]==-1;j++);
		apmax(lim,i-j);
	}
	q.push(pti(0,1,0));
	for(;!q.empty()&&q.front().n<lim;q.front().spawn(),q.pop());
	M::init();
	for(;tot--;putchar('0'+M::work(lim,ni)),putchar('\n'));
}