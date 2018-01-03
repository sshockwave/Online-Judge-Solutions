#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <random>
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
const int N=200;
lint a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("num8.in","r",stdin);
	freopen("num8.out","w",stdout);
#endif
	random_device rand;
	unsigned long long num=next_num<unsigned long long>();
	cout<<"num="<<num<<endl;
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=next_num<lint>();
	}
	while(num){
		int j=0;
		for(int i=1;i<=n;i++){
			if(a[i]<=num){
				if(j==0||a[i]>a[j]){
					j=i;
				}else if(rand()&1){
					j=i;
				}
			}
		}
		assert(j);
		num-=a[j];
		printf("%d\n",j);
	}
	return 0;
}
