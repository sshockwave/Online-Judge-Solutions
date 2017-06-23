#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
	if(b<a){a=b;}
}
const int N=100010;
struct Info{
	int nxt,mnnxt;
	int mnnxttag;
};
namespace T{
	const int N=2000010;
	int n=0;
	#define lson(x) son[x][0]
	#definr rson(x) son[x][1]
	int son[N][2],tag[N];
	inline void init(){
		memset(son,0,sizeof(son));
		tag[0]=0;
	}
	inline int renew(int x){
		if(tag[x]<tim){
		memset(son,0,szieof
			
	int build(int l,int r){
		int x=++n;
		if(l==r){
			//update val
		}else{
			up(x);
		}
		return x;
	}
}
int main(){
	int n=ni;
	
}