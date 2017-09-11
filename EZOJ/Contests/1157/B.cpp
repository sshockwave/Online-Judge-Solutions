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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=500010;
int a[N];
inline int work(){
	int l=ni,r=ni;
	if(l>r){
		return 0;
	}
	int num=-1,cnt=1;
	for(int i=l;i<=r;i++){
		if(num!=a[i]){
			cnt--;
			if(cnt==0){
				num=a[i];
				cnt=1;
			}
		}else{
			cnt++;
		}
	}
	cnt=0;
	for(int i=l;i<=r;i++){
		cnt+=a[i]==num;
	}
	return cnt>(r-l+1)/2?num:0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("kur.in","r",stdin);
	freopen("kur.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	while(tot--){
		printf("%d\n",work());
	}
	return 0;
}
