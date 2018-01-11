#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <vector>
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
const int rtN=65536,INF=0x7f7f7f7f;
int O;
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
namespace sqrt{
	int w2;
	struct num{
		int a,b;
		inline friend num operator * (const num &a,const num &b){
			num c;
			c.a=((lint)a.a*b.a%O+(lint)a.b*b.b%O*w2%O)%O;
			c.b=((lint)a.a*b.b%O+(lint)a.b*b.a%O)%O;
			return c;
		}
	};
	inline num fpow(num x,int n){
		num a=(num){1,0};
		for(;n;n>>=1,x=x*x){
			if(n&1){
				a=a*x;
			}
		}
		return a;
	}
	inline int dre(int x){
		return ::fpow(x,(O-1)>>1);
	}
	inline int cipolla(int x){//\sqrt x
		if(x==0)return 0;
		if(dre(x)==O-1)return -1;
		int a;
		do{
			a=rand();
			if(RAND_MAX==65536){
				a=a*65536|rand();
			}
			a%=O;
		}while(dre(w2=((lint)a*a%O+O-x)%O)==1);
		return fpow((num){a,1},(O+1)>>1).a;
	}
}
namespace logarithm{
	namespace H{
		const int M=65537,Magic=1353641090;
		struct node{
			int val,exp;
			inline friend bool operator < (const node &a,const node &b){
				return a.exp<b.exp;
			}
		};
		vector<node>vec[M];
		inline void init(){
			for(int i=0;i<M;i++){
				vec[i].clear();
			}
		}
		inline bool ae(lint val,int exp){
			vector<node>&v=vec[(val^Magic)%M];
			for(vector<node>::iterator it=v.begin();it!=v.end();it++){
				if(it->val==val)return false;
			}
			v.push_back((node){(int)val,exp});
			return true;
		}
		inline int ask(lint val,int ad){//does it exist? exp:INF;
			vector<node>&v=vec[(val^Magic)%M];
			for(vector<node>::iterator it=v.begin();it!=v.end();it++){
				if(it->val==val&&(it->exp&1)==ad)return it->exp;
			}
			return INF;
		}
	}
	int rtO,x;
	inline void init(int x){
		H::init();
		logarithm::x=x;
		for(rtO=0;rtO*rtO<O;rtO++);
		x=fpow(x,rtO);
		for(int i=0,w=1;i<=rtO;i++,w=(lint)w*x%O){
			if(!H::ae(w,i*rtO))break;
		}
		for(int i=0;i<H::M;i++){
			sort(H::vec[i].begin(),H::vec[i].end());
		}
	}
	inline int dlog(int n,int ad){//\log_x n & 2 == ad
		if(n==0)return INF;
		int ans=INF;
		for(int i=0;i<=rtO;i++,n=(lint)n*x%O){
			lint t=H::ask(n,(ad^i)&1);
			if(t<INF){
				apmin(ans,((t-i)%(O-1)+O-1)%(O-1));
			}
		}
		return ans;
	}
}
using sqrt::cipolla;
using logarithm::dlog;
inline int Main(){
	int c=ni;
	O=ni;
	int inv2=inv(2);
	int x=cipolla(5),y=(lint)(1+x)*inv2%O;
	assert((lint)x*x%O==5);
	c=(lint)c*x%O;
	int ans=INF;
	logarithm::init(y);
	{//odd
		int rt=cipolla(((lint)c*c%O+O-4)%O);
		if(rt!=-1){
			apmin(ans,dlog(((lint)c+rt)*inv2%O,1));
			apmin(ans,dlog(((lint)c+O-rt)*inv2%O,1));
		}
	}
	{//even
		int rt=cipolla(((lint)c*c%O+4)%O);
		if(rt!=-1){
			apmin(ans,dlog(((lint)c+rt)*inv2%O,0));
			apmin(ans,dlog(((lint)c+O-rt)*inv2%O,0));
		}
	}
	return ans!=INF?ans:-1;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fn.in","r",stdin);
	freopen("fn.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
