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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=100010;
const lint INF=1000000000000000000ll;
lint k,m,d,a,n;
lint t[N],f[N],add[N];
inline lint cost(int l,int r){
	int gap=r-l;
	return a*(gap/d+(gap%d!=0));
}
namespace task1{
	inline lint work(){
		for(int i=1,top=n+1;i<=top;i++){
			f[i]=-INF;
			for(int j=0;j<i;j++){
				apmax(f[i],f[j]-cost(t[j],t[i]));
			}
			f[i]+=add[i];
		}
		return f[n+1];
	}
}
namespace task2{
	inline lint work(){
		int j=0;
		lint sum=0;
		for(int i=1,top=n+1;i<=top;i++){
			for(;t[i]-t[j]>d;j++);
			if(i==j){
				j--;
			}
			f[i]=f[j]-cost(t[j],t[i]);
		}
		return f[n+1];
	}
}
int main(){
	t[0]=ni,m=ni,d=ni,a=ni,n=ni;
	t[n+1]=m;
	f[0]=0;
	for(int i=1;i<=n;i++){
		t[i]=ni,add[i]=ni;
	}
	printf("%lld\n",n<=1000?task1::work():task2::work());
}