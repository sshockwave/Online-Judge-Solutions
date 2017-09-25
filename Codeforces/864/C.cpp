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
int seq[20010];
int main(){
#ifndef ONLINE_JUDGE
	freopen("bus.in","r",stdin);
	freopen("bus.out","w",stdout);
#endif
	int a=ni,b=ni,f=ni,k=ni,ss=0;
	seq[0]=f;
	if(k==0){
		puts("0");
		return 0;
	}
	if(k&1){
		seq[ss++]=f;
		for(int i=2;i<=k;i+=2){
			seq[ss++]=(a-f)<<1;
			seq[ss++]=f<<1;
		}
		seq[ss++]=a-f;
	}else{
		seq[ss++]=f;
		for(int i=4;i<=k;i+=2){
			seq[ss++]=(a-f)<<1;
			seq[ss++]=f<<1;
		}
		seq[ss++]=(a-f)<<1;
		seq[ss++]=f;
	}
	if(seq[0]>b){
		puts("-1");
		return 0;
	}
	int cnt=0,rst=b-seq[0];
	for(int i=1;i<ss;i++){
		if(seq[i]>rst){
			rst=b,cnt++;
		}
		rst-=seq[i];
		if(rst<0){
			puts("-1");
			return 0;
		}
	}
	printf("%d\n",cnt);
	return 0;
}
