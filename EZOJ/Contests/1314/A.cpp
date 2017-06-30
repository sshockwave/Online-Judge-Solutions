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
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
inline lint to10(int n){
	lint ans=0,x=1;
	for(;n;n>>=1,x*=10){
		if(n&1){
			ans+=x;
		}
	}
	return ans;
}
inline bool check(int n){
	lint a=to10(n),b=a,ans=0,x=1;
	for(;a;a>>=1,x*=10){
		if(a&1){
			ans+=x;
		}
		if(ans==b){
			return true;
		}
	}
	return false;
}
int main(){
	int n=ni;
	int cnt=0;
	for(int i=1;;i++){
		if(check(i)){
			cnt++;
			if(cnt==n){
				printf("%lld\n",to10(i));
				return 0;
			}
		}
	}
}
