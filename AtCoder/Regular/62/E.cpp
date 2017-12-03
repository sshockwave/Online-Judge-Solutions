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
	inline bool cmp(int x,int y){
		for(int i=0;i<D;(++x)%=D,(++y)%=D,i++){
			if(a[x]!=a[y])return a[x]<a[y];
		}
		return false;
	}
	inline bool equal(int x,int y){
		for(int i=0;i<D;(++x)%=D,(++y)%=D,i++){
			if(a[x]!=a[y])return false;
		}
		return true;
	}
	inline void sani(){
		int j=0;
		for(int i=1;i<D;i++){
			if(cmp(i,j)){
				j=i;
			}
		}
		int b[D];
		memcpy(b,a,D<<2);
		for(int i=0;i<D;i++,(++j)%=D){
			a[i]=b[j];
		}
	}
	inline int getloop(){
		int cnt=0;
		for(int i=0;i<D;i++){
			cnt+=equal(0,i);
		}
		return cnt;
	}
	inline friend bool operator < (const Tile &a,const Tile &b){
		for(int i=0;i<D;i++){
			if(a.a[i]!=b.a[i])return a.a[i]<b.a[i];
		}
		return false;
	}
	inline friend bool operator == (const Tile &a,const Tile &b){
		for(int i=0;i<D;i++){
			if(a.a[i]!=b.a[i])return false;
		}
		return true;
	}
}tile[N];
map<Tile,int>m;
int main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		tile[i]=(Tile){ni,ni,ni,ni};
		tile[i].sani();
		m[tile[i]]++;
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		m[tile[i]]--;
		int *a=tile[i].a;
		for(int j=i+1;j<=n;j++){
			int *b=tile[j].a;
			m[tile[j]]--;
			for(int d=0;d<4;d++){
				Tile t[4];
				for(int e=0;e<4;e++){
					t[e]=(Tile){a[e+1],a[e],b[(d+4-e)&3],b[(d+3-e)&3]};
					t[e].sani();
				}
				sort(t,t+4);
				lint tmp=1;
				int cnt[4];
				for(int e=0;e<4;e++){
					if(e&&t[e]==t[e-1]){
						cnt[e]=cnt[e-1]-1;
					}else{
						cnt[e]=m[t[e]];
					}
					tmp*=cnt[e]*t[e].getloop();
				}
				ans+=tmp;
			}
			m[tile[j]]++;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
