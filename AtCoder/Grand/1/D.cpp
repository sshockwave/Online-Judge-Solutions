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
const int N=100010,M=110;
int a[M];
int main(){
	int n=ni,m=ni,cnt=0;
	for(int i=1;i<=m;i++){
		a[i]=ni;
		cnt+=a[i]&1;
	}
	if(cnt>2){
		puts("Impossible");
		return 0;
	}
	if(m==1){
		if(a[1]==1){
			puts("1\n1\n1");
		}else{
			printf("%d\n2\n%d 1\n",a[1],a[1]-1);
		}
		return 0;
	}
	cnt=0;
	for(int i=1;i<=m;i++){
		if(a[i]&1){
			if(cnt==0){
				swap(a[i],a[1]);
			}else{
				swap(a[i],a[m]);
			}
			cnt++;
		}
	}
	for(int i=1;i<=m;i++){
		printf("%d ",a[i]);
	}
	putchar('\n');
	a[1]++,a[m]--;
	if(a[m]==0){
		m--;
	}
	printf("%d\n",m);
	for(int i=1;i<=m;i++){
		printf("%d ",a[i]);
	}
	putchar('\n');
	return 0;
}
