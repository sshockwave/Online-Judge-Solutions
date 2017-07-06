#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int MOD=15135121;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
inline void apmul(int &a,int b){
	a=mul(a,b);
}
int n,m,A,B,C,D;
int f[MOD],x[MOD*2];
void init()
{
	cin>>n>>A>>B>>C>>D;
	for(int i=0;i<n;i++)
	{
		f[i]=A;
		A=((lint)A*B+C)%D;
	}
	cin>>m>>A>>B>>C>>D;
	for(int i=0;i<m;i++)
	{
		x[i]=A;
		A=((lint)A*B+C)%D;
	}
}
int F(int x){
	int ans=0,prod=1;
	for(int i=0;i<n;i++){
		apadd(ans,mul(f[i],prod));
		apmul(prod,x);
	}
	return ans;
}
void work()
{
	int ans=0;
	for(int i=0;i<m;i++){
		ans^=F(x[i]);
	}
	cout<<ans<<endl;
}
int main(){
	freopen("thefall2.in","r",stdin);
	for(int tot=ni;tot--;){
		init();
		work();
	}
}
