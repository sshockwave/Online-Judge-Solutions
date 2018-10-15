#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int>vi;
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
const int N=10,L=1010,INF=0x7f7f7f7f,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv_pow(int x){
	return fpow(x,O-2);
}
char stk[L];
int ss;
int val[N],curn;
void pshstk(char x){
	//0/1:value
	if(ss==0||x=='('||x=='<'||x=='&'||x=='|'){
		stk[ss++]=x;
	}else if(x==')'){
		//(t|t|f|t|t)
		for(;stk[ss-2]=='|';stk[ss-3]|=stk[ss-1],ss-=2);
		assert(stk[ss-2]=='(');
		assert(stk[ss-1]<=1);
		char tmp=stk[ss-1];
		ss-=2;
		pshstk(tmp);
	}else if(x==0||x==1){
		//t&??
		if(stk[ss-1]=='&'){
			assert(stk[ss-2]<=1);
			stk[ss-2]&=x,ss--;
		}else{
			stk[ss++]=x;
		}
	}else if(isalpha(x)){
		assert(x>='a'&&x<='g');
		if(stk[ss-1]=='<'){
			assert(isalpha(stk[ss-2]));
			const int a=stk[ss-2]-'a'+1;
			const int b=x-'a'+1;
			ss-=2;
			pshstk(a>curn||b>curn||val[a]<val[b]);
		}else{
			stk[ss++]=x;
		}
	}else{
		assert(false);
	}
}
int c[N];
lint ans=0;
const int n=7;
int lst[N];
char expr[L];
inline bool valid(int n){
	ss=0;
	curn=n;
	pshstk('(');
	for(int i=0;expr[i];i++){
		if(expr[i]!=' '){
			pshstk(expr[i]);
		}
	}
	pshstk(')');
	assert(ss==1);
	assert(stk[0]==0||stk[0]==1);
	return stk[0];
}
void dfs(int x){
	vi vec(val+1,val+x);
	sort(vec.begin(),vec.end());
	if(x>n){
		int cnt=0;
		for(int i=0;i<(int)vec.size();i++){
			cnt+=i==0||vec[i-1]!=vec[i];
		}
		ans+=c[cnt];
		return;
	}
	int ls=0;
	lst[++ls]=0;
	for(int i=0;i<(int)vec.size();i++){
		if(vec[i]!=lst[ls]){
			lst[++ls]=vec[i];
		}
	}
	lst[++ls]=INF;
	vec.clear();
	for(int i=2;i<=ls;i++){
		vec.push_back(((lint)lst[i-1]+lst[i])>>1);
		if(i<ls){
			vec.push_back(lst[i]);
		}
	}
	for(int i=0;i<(int)vec.size();i++){
		val[x]=vec[i];
		if(valid(x)){
			dfs(x+1);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("exp.in","r",stdin);
	freopen("exp.out","w",stdout);
#endif
	cin.getline(expr,L);
	const int lim=ni;
	c[0]=1;
	for(int i=1;i<=n;i++){
		c[i]=(lint)c[i-1]*(lim-i+1)%O*inv_pow(i)%O;
	}
	dfs(1);
	printf("%lld\n",ans%O);
	return 0;
}
