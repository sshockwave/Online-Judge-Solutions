#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
inline void Main(){
	set<int>s;
	bool flag=true;
	for(int i=1,n=ni;i<=n;i++){
		int a=ni;
		if(s.insert(a).second){
			if(flag){
				flag=false;
			}else{
				putchar(' ');
			}
			printf("%d",a);
		}
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("num.in","r",stdin);
	freopen("num.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		Main();
	}
	return 0;
}
