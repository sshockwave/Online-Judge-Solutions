#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
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
const int N=610,S=N*2,O=1000000007;
template<class T1,class T2>inline void apadd(T1 &a,const T2 &b){
	a=(a+b)%O;
}
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
namespace gmath{
	int invnum[S];
	inline void main(int n){
		invnum[1]=1;
		for(int i=2;i<=n;i++){
			invnum[i]=O-(lint)O/i*invnum[O%i]%O;
			assert((lint)invnum[i]*i%O==1);
		}
	}
}
struct Info:vector<int>{
	typedef vector<int>vi;
	typedef iterator iter;
	vi sum;
	int cache;
	inline void calc(){
		cache=0;
		for(iter it1=sum.begin()+1,it2=begin();it2!=end();it1++,it2++){
			apadd(cache,(lint)*it1**it2);
		}
	}
	int lend,rend,n;
	inline void init(int tn){
		n=rend-lend+1;
		lint curv=1;
		push_back(0);
		for(int i=0;i<=tn;i++){
			sum.push_back(curv);
			curv=curv*(n+i)%O*gmath::invnum[i+1]%O;
		}
	}
	inline void mul2(){
		for(iter it=begin();it!=end();it++){
			*it=(*it<<1)%O;
		}
	}
	inline void add(int v){
		apadd(at(0),v);
	}
	inline void pre_int(){
		insert(begin(),0);
	}
	inline void suf_int(){
		int s=0;
		for(int i=0,ti=size();i<ti;i++){
			int &f=at(i);
			apadd(s,(lint)f*sum[i+1]);
			if(i){
				apadd(at(i-1),f);
			}else{
				apadd(s,f);
			}
			f=O-f;
		}
		insert(begin(),s);
	}
}f[S];
int lval[N],rval[N];
char tp[N];
int vlst[S];
int main(){
#ifndef ONLINE_JUDGE
	freopen("plane.in","r",stdin);
	freopen("plane.out","w",stdout);
#endif
	int n=ni,m=0;
	gmath::main(n+2);
	{
		int ls=0;
		for(int i=1;i<=n;i++){
			lval[i]=ni,rval[i]=ni;
			char &c=tp[i];
			while(c=getchar(),c!='<'&&c!='>'&&c!='=');
			vlst[++ls]=lval[i]-1;
			vlst[++ls]=rval[i];
		}
		sort(vlst+1,vlst+ls+1);
		for(int i=2;i<=ls;i++){
			if(vlst[i-1]==vlst[i])continue;
			++m,f[m].lend=vlst[i-1]+1,f[m].rend=vlst[i],f[m].init(n+1);
		}
	}
	for(int i=1;i<=n;i++){
		if(tp[i]=='>'){
			lint sum=1;
			int j=1;
			for(;f[j].rend<lval[i];j++){
				sum+=f[j].cache;
			}
			sum%=O;
			for(;j<=m&&f[j].rend<=rval[i];j++){
				f[j].pre_int(),f[j].add(sum);
				apadd(sum,f[j].cache),f[j].calc();
			}
		}else if(tp[i]=='<'){
			lint sum=1;
			int j=m;
			for(;f[j].lend>rval[i];j--){
				sum+=f[j].cache;
			}
			sum%=O;
			for(;j>=1&&f[j].lend>=lval[i];j--){
				f[j].suf_int(),f[j].add(sum);
				apadd(sum,f[j].cache),f[j].calc();
			}
		}else for(int j=1;j<=m&&f[j].rend<=rval[i];j++){
			if(lval[i]<=f[j].lend){
				f[j].mul2(),f[j].add(1),f[j].calc();
			}
		}
	}
	lint ans=0;
	for(int i=1;i<=m;i++){
		ans+=f[i].cache;
	}
	printf("%lld\n",ans%O);
}
