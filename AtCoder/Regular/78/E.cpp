#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
inline char ask(lint x){
	printf("? %lld\n",x);
	fflush(stdout);
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
inline bool ispow10(int x){
	for(lint i=1;i<=x;i*=10){
		if(x==i)return true;
	}
	return false;
}
int main(){
	int num=1;
	for(;;num*=10){
		if(num==1000000000)break;
		int l=num,r=num+9;
		while(l<r){
			int m=(l+r)>>1;
			if(ask(m*1000000000ll+999999999)=='Y'){
				r=m;
			}else{
				l=m+1;
			}
		}
		num=l;
		//for(;ask(num*1000000000ll+999999999)=='N';num++,assert(num%10));
		if(ispow10(num+1)){
			if(ask(num*10ll-1)=='N')break;
		}else if(ask(num+1)=='Y')break;
	}
	printf("! %d\n",num);
	fflush(stdout);
	return 0;
}
