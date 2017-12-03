#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <algorithm>
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
const int N=410;
struct Tile{
	const static int D=4;
	int a[D];
	inline Tile nxt(){
		return (Tile){a[1],a[2],a[3],a[0]};
	}
	inline friend bool operator < (const Tile &a,const Tile &b){
		for(int i=0;i<4;i++){
			if(a.a[i]!=b.a[i])return a.a[i]<b.a[i];
		}
		return false;
	}
	inline friend ostream & operator <<(ostream & out,const Tile &b){
		out<<b.a[0]<<" "<<b.a[1]<<" "<<b.a[2]<<" "<<b.a[3]<<" ";
		return out;
	}
}tile[N];
map<Tile,int>m;
inline void add(Tile x,int v){
	for(int i=0;i<Tile::D;i++,x=x.nxt()){
		m[x]+=v;
	}
}
int main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		tile[i]=(Tile){ni,ni,ni,ni};
		add(tile[i],1);
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		add(tile[i],-1);
		int *a=tile[i].a;
		for(int j=i+1;j<=n;j++){
			int *b=tile[j].a;
			add(tile[j],-1);
			for(int d=0;d<4;d++){
				tile[j]=tile[j].nxt();
				Tile f1=(Tile){a[1],a[0],b[0],b[3]};
				Tile f2=(Tile){a[2],a[1],b[3],b[2]};
				Tile f3=(Tile){a[3],a[2],b[2],b[1]};
				Tile f4=(Tile){a[0],a[3],b[1],b[0]};
				lint tmp=1;
				tmp*=m[f1],add(f1,-1);
				tmp*=m[f2],add(f2,-1);
				tmp*=m[f3],add(f3,-1);
				tmp*=m[f4];
				add(f1,1),add(f2,1),add(f3,1);
				ans+=tmp;
			}
			add(tile[j],1);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
