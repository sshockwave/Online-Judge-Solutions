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
const int N=100010;
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int a[N],n;
bool Main(){
	if(n==1)return (a[1]&1)==0;
	int cnt[2]={0,0};
	bool hasone=false;
	for(int i=1;i<=n;i++){
		cnt[a[i]&1]++;
		hasone|=a[i]==1;
	}
	if(hasone)return cnt[0]&1;
	if(cnt[0]&1)return true;
	if(cnt[1]>1)return false;
	assert(cnt[1]==1);
	int g=0;
	for(int i=1;i<=n;i++){
		if(a[i]&1){
			a[i]--;
		}
		g=gcd(g,a[i]);
	}
	for(int i=1;i<=n;i++){
		a[i]/=g;
	}
	return !Main();
}
int main(){
	n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	puts(Main()?"First":"Second");
	return 0;
}
