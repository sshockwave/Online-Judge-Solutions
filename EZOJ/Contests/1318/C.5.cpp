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
lint k,MOD;
lint gcd(lint a,lint b){
	return b==0?a:gcd(b,a%b);
}
inline lint f(lint n,lint mx){
	apmin(mx,MOD-1);
	if(n<=0||mx<0){
		return 0;
	}
	if(k==0){
		bool inside=mx>=0;
		return n*inside;
	}
	lint gap=gcd(MOD,k),len=MOD/gap;
	lint oneloop=mx/gap+1,lastloop=min(oneloop,n%len);
	cout<<"gap="<<gap<<"\tlen="<<len<<endl;
	cout<<"oneloop="<<oneloop<<"\tlastloop="<<lastloop<<endl;
	return (n/len)*oneloop+lastloop;
}
int main(){
	for(int tot=ni;tot--;){
		lint A,B,L,R;
		cin>>k>>MOD>>A>>B>>L>>R;
		lint ans=f(B,R)-f(A-1,R)-f(B,L-1)+f(A-1,L-1);
		printf("%lld\n",ans);
	}
}
