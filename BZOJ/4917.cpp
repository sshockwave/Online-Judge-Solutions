#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
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
inline uint rev1(uint x){//t+(t<<10)
	uint ander=(1u<<10)-1;
	uint b=x&ander;
	uint a=((x>>10)-b)&ander;
	b|=a<<10;
	a=(((x>>10)-b)>>10)&ander;
	b|=a<<20;
	a=(((x>>10)-b)>>20)&ander;
	b|=a<<30;
	assert(b+(b<<10)==x);
	return b;
}
inline uint rev2(uint x){//t^(t>>6)
	uint ander=(1<<6)-1;
	uint b=(x>>26)<<26;
	b|=(((b>>26)^(x>>20))&ander)<<20;
	b|=(((b>>20)^(x>>14))&ander)<<14;
	b|=(((b>>14)^(x>>8))&ander)<<8;
	b|=(((b>>8)^(x>>2))&ander)<<2;
	b|=((b>>6)^x)&ander;
	assert((b^(b>>6))==x);
	return b;
}
inline uint rev3(uint x){//t+(t<<3)
	uint ander=(1u<<3)-1;
	uint a=((x>>3)-(x&ander))&ander;
	uint b=(x&ander)|(a<<3);
	a=(((x>>3)-b)>>3)&ander;
	b|=a<<6;
	a=(((x>>3)-b)>>6)&ander;
	b|=a<<9;
	a=(((x>>3)-b)>>9)&ander;
	b|=a<<12;
	a=(((x>>3)-b)>>12)&ander;
	b|=a<<15;
	a=(((x>>3)-b)>>15)&ander;
	b|=a<<18;
	a=(((x>>3)-b)>>18)&ander;
	b|=a<<21;
	a=(((x>>3)-b)>>21)&ander;
	b|=a<<24;
	a=(((x>>3)-b)>>24)&ander;
	b|=a<<27;
	a=(((x>>3)-b)>>27)&ander;
	b|=a<<30;
	assert(b+(b<<3)==x);
	return b;
}
inline uint rev4(uint x){//t^(t>>11)
	uint a=x>>21;
	uint b=x^(a<<10);
	a=(b>>11)&((1u<<10)-1);
	b^=a;
	assert((b^(b>>11))==x);
	return b;
}
inline uint rev5(uint x){//t=t+(t<<16)
	uint ander=(1u<<16)-1;
	uint a=(x>>16)-(x&ander);
	assert(((a+(x&ander))&ander)==(x>>16));
	uint ret=(a<<16)|(x&ander);
	assert(ret+(ret<<16)==x);
	return ret;
}
unsigned int Hash(unsigned int v){
    unsigned int t = v;
    t = t + (t << 10);
    t = t ^ (t >> 6);
    t = t + (t << 3);
    t = t ^ (t >> 11);
    t = t + (t << 16);
    return t;
}
inline uint work(uint x){
	uint res=rev1(rev2(rev3(rev4(rev5(x)))));
	assert(Hash(res)==x);
	return res;
}
int main(){
	for(int tot=ni;tot--;){
		printf("%u\n",work(next_num<uint>()));
	}
}