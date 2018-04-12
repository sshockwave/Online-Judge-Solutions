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
const int N=610,O=1000000007;
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
int n;
int lval[N],rval[N];
char tp[N];
namespace solve1{
	const int S=100010;
	int f[S];
	inline int main(){
		memset(f,0,sizeof(f));
		int mx=0;
		for(int i=1;i<=n;i++){
			apmax(mx,rval[i]);
			if(tp[i]=='>'){
				lint sum=1;
				for(int j=0;j<lval[i];j++){
					sum+=f[j];
				}
				sum%=O;
				for(int j=lval[i];j<=rval[i];j++){
					sum=f[j]=(f[j]+sum)%O;
				}
			}else if(tp[i]=='<'){
				lint sum=1;
				for(int j=mx;j>rval[i];j--){
					sum+=f[j];
				}
				sum%=O;
				for(int j=rval[i];j>=lval[i];j--){
					sum=f[j]=(f[j]+sum)%O;
				}
			}else{
				for(int j=lval[i];j<=rval[i];j++){
					f[j]=((f[j]<<1)+1)%O;
				}
			}
		}
		lint ans=0;
		for(int i=0;i<=mx;i++){
			ans+=f[i];
		}
		return ans%O;
	}
}
const int S=N*2;
int m=0;
int lend[S],rend[S];
int vlst[S];
namespace solveeq{
	int f[S];
	inline int main(){
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m&&rend[j]<=rval[i];j++){
				if(lval[i]<=lend[j]){
					f[j]=((f[j]<<1)+1)%O;
				}
			}
		}
		int ans=0;
		for(int i=1;i<=m;i++){
			ans=(ans+(lint)f[i]*(rend[i]-lend[i]+1))%O;
		}
		return ans;
	}
}
namespace solvegeq{
	int invnum[N];
	struct info{
		typedef vector<int>vi;
		typedef vi::iterator iter;
		vi sum,val;
		inline int eval(){
			int ans=0;
			for(iter it1=sum.begin(),it2=val.begin();it2!=val.end();it1++,it2++){
				ans=(ans+(lint)*it1**it2)%O;
			}
			return ans;
		}
		int lend,rend,n;
		inline void init(){
			n=rend-lend+1;
			lint curv=1;
			int tn=n+1;
			val.push_back(0);
			val.push_back(0);
			for(int i=0;i<=tn;i++){
				sum.push_back(curv);
				curv=curv*(n+i+1)%O*invnum[i+1]%O;
			}
		}
		inline void mul2(){
			for(iter it=val.begin();it!=val.end();it++){
				*it=(*it<<1)%O;
			}
		}
		inline void sh(){
			int sz=val.size();
			val.push_back(0);
			for(int i=sz;i>=1;i--){
				val[i]=val[i-1];
			}
			val[0]=0;
		}
	}f[S];
	inline int main(){
		invnum[1]=1;
		for(int i=2;i<=n+2;i++){
			invnum[i]=(O-(lint)O/i*invnum[O%i])%O;
			assert((lint)invnum[i]*i%O);
		}
		for(int i=1;i<=m;i++){
			f[i].lend=lend[i];
			f[i].rend=rend[i];
			f[i].init();
		}
		for(int i=1;i<=n;i++){
			if(tp[i]=='>'){
				lint sum=1;
				int j=1;
				for(;lend[j]<=lval[i];j++){
					sum+=f[j].eval();
				}
				sum%=O;
				for(;rend[j]<=rval[i];j++){
					f[j].sh();
					(f[j].val[1]+=sum)%=O;
				}
			}else for(int j=1;j<=m&&rend[j]<=rval[i];j++){
				if(lval[i]<=lend[j]){
					f[j].mul2();
					++f[j].val[1];
				}
			}
		}
		lint ans=0;
		for(int i=1;i<=m;i++){
			ans+=f[i].eval();
		}
		return ans%O;
	}
}
namespace solveleq{
	inline int main(){
		reverse(lval+1,lval+n+1);
		reverse(rval+1,rval+n+1);
		reverse(tp+1,tp+n+1);
		for(int i=1;i<=n;i++){
			if(tp[i]=='<'){
				tp[i]='>';
			}
		}
		return solvegeq::main();
	}
}
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("plane.in","r",stdin);
	freopen("plane.out","w",stdout);
#endif
	n=ni;
	char flag='=';
	int mx=0;
	for(int i=1;i<=n;i++){
		lval[i]=ni,rval[i]=ni;
		apmax(mx,rval[i]);
		char &c=tp[i];
		while(c=getchar(),c!='<'&&c!='>'&&c!='=');
		if(c!='='){
			if(flag=='='||flag==c){
				flag=c;
			}else{
				flag=0;
			}
		}
	}
	if(mx<=200000||flag==0){
		printf("%d\n",solve1::main());
		return 0;
	}
	{
		int ls=0;
		for(int i=1;i<=n;i++){
			vlst[++ls]=lval[i]-1;
			vlst[++ls]=rval[i];
		}
		sort(vlst+1,vlst+ls+1);
		for(int i=2;i<=ls;i++){
			if(vlst[i-1]==vlst[i])continue;
			++m,lend[m]=vlst[i-1]+1,rend[m]=vlst[i];
		}
	}
	if(flag=='<'){
		printf("%d\n",solveleq::main());
	}else if(flag=='>'){
		printf("%d\n",solvegeq::main());
	}else{
		printf("%d\n",solveeq::main());
	}
	return 0;
}
