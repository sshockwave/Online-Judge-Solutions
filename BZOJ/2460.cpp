#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
	if(a>b){a=b;}
}
const int N=1010;
struct Ore{
	lint id;
	int w;
	inline friend bool operator < (const Ore &a,const Ore &b){
		return a.w>b.w;
	}
}os[N];
lint a[70];
inline bool add(lint x){
	for(int i=69;x;i--){
		if((x>>i)&1){
			if(a[i]==0){
				a[i]=x;
				return true;
			}else{
				x^=a[i];
			}
		}
	}
	return false;
}
int main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		os[i].id=nl,os[i].w=ni;
	}
	sort(os+1,os+n+1);
	memset(a,0,sizeof(a));
	int ans=0;
	for(int i=1;i<=n;i++){
		if(add(os[i].id)){
			ans+=os[i].w;
		}
	}
	printf("%d\n",ans);
}