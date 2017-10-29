#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <set>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=1010,N2=1000010;
int a[N2],b[N],bs=0;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("password.in","r",stdin);
	freopen("password.out","w",stdout);
#endif
	int n=ni;
	for(int i=0,ti=n*n;i<ti;i++){
		a[i]=ni;
	}
	multiset<int>s;
	sort(a,a+n*n);
	for(int i=n*n-1;i>=0;i--){
		multiset<int>::iterator it=s.find(a[i]);
		if(it==s.end()){
			b[bs]=a[i];
			for(int j=0;j<bs;j++){
				int d=gcd(a[i],b[j]);
				s.insert(d);
				s.insert(d);
			}
			bs++;
		}else{
			s.erase(it);
		}
	}
	for(int i=0;i<bs;i++){
		printf("%d ",b[i]);
	}
	putchar('\n');
	return 0;
}
