#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=1000010;
map<int,int>fa;
int qx[N],qy[N],qtop;
int root(int x){
	map<int,int>::iterator it=fa.find(x);
	if(it==fa.end()){
		return x;
	}
	return fa[x]=root(it->second);
}
inline bool test(){
	for(int i=0;i<qtop;i++){
		if(root(qx[i])==root(qy[i])){
			return false;
		}
	}
	return true;
}
int main(){
	for(int tot=ni;tot--;){
		qtop=0;
		for(;!fa.empty();fa.erase(fa.begin()));
		for(int tot=ni;tot--;){
			int u=ni,v=ni;
			if(ni){
				fa[root(u)]=root(v);
			}else{
				qx[qtop]=u,qy[qtop]=v,qtop++;
			}
		}
		puts(test()?"YES":"NO");
	}
}
