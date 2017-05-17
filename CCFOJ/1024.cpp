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
int main(){
	lint ans=1;
	int n=ni;
	for(lint i=2;i*i<=n;i++){
		if(n%i==0){
			int exp=0;
			for(;n%i==0;n/=i,exp++);
			ans*=exp+1;
		}
	}
	if(n>1){
		ans*=2;
	}
	printf("%d",ans);
}
