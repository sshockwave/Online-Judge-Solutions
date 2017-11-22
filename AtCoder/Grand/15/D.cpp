#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
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
lint solve(lint l,lint r){
	if(l>r){
		return 0;
	}
	if(l==r){
		return 1;
	}
	lint hi=1;
	for(;hi<=(l^r);hi<<=1);
	hi--;
	l&=hi,r&=hi;
	hi++;
	hi>>=1;
	assert(r&hi);
	assert((l&hi)==0);
	lint a=r^hi,b=l;
	lint ans=(hi-1)-b+1;//0 | 1
	lint hi2=1;
	for(;hi2<=a;hi2<<=1);
	ans+=min(hi2,b);//1 | 1
	ans+=solve(b,hi-1);//0 | 0
	return ans;
}
int main(){
	lint l=nl,r=nl;
	printf("%lld\n",solve(l,r));
	return 0;
}
