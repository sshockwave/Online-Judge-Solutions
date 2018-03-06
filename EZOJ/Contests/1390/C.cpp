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
lint a[N];
int c[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni,c[i]=0;
	}
	for(int tot=ni;tot--;){
		char op;
		while(!isalpha(op=getchar()));
		if(op=='A'){
			int l=ni,r=ni,v=ni;
			for(int i=l;i<=r;i++){
				a[i]+=v,c[i]++;
			}
		}else if(op=='M'){
			int l=ni,r=ni,v=ni;
			for(int i=l;i<=r;i++){
				if(a[i]<v){
					a[i]=v,c[i]++;
				}
			}
		}else if(op=='Q'){
			int p=ni;
			printf("%lld %d\n",a[p],c[p]);
		}else assert(false);
	}
	return 0;
}
