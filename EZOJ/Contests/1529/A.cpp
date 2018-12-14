#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1000010;
typedef vector<int>vi;
inline void printvi(vi &vec1,vi &vec2){
	printf("%d",(int)(vec1.size()+vec2.size()));
	for(vi::iterator it=vec1.begin(),ti=vec1.end();it!=ti;++it){
		printf(" %d",*it);
	}
	for(vi::reverse_iterator it=vec2.rbegin(),ti=vec2.rend();it!=ti;++it){
		printf(" %d",*it);
	}
	putchar('\n');
}
vi ans1_l,ans1_r;
vi ans2_l,ans2_r;
int perm[N],pos[N],_perm[N];
inline bool inc(int l,int r){
	return _perm[r]-_perm[l]==r-l;
}
inline bool dec(int l,int r){
	return _perm[r]-_perm[l]==-(r-l);
}
inline bool Main(){
	const int n=ni;
	for(int i=1;i<=n;i++){
		perm[i]=ni;
		pos[perm[i]]=i;
		_perm[i]=i>1?_perm[i-1]+(perm[i]>perm[i-1]?1:-1):0;
	}
	int l=1,r=n;
	ans1_l.clear(),ans1_r.clear();
	ans2_l.clear(),ans2_r.clear();
	for(int i=1;i<=n;i++){
		const int x=pos[i];
		if(!(l<=x&&x<=r))continue;
		bool ok1=(l==x||ans2_l.empty()||ans2_l.back()>perm[l])&&dec(l,x)&&(ans1_r.empty()||i<ans1_r.back());
		bool ok2=(ans2_l.empty()||ans2_l.back()>i)&&inc(x,r)&&(r==x||ans1_r.empty()||perm[r]<ans1_r.back());
		if(ok1){
			for(;l<x;l++){
				ans2_l.push_back(perm[l]);
			}
			ans1_l.push_back(perm[l++]);
		}else if(ok2){
			for(;r>x;r--){
				ans1_r.push_back(perm[r]);
			}
			ans2_r.push_back(perm[r--]);
		}else return false;
	}
	puts("YES");
	printvi(ans1_l,ans1_r);
	printvi(ans2_l,ans2_r);
	return true;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("quin.in","r",stdin);
	freopen("quin.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		if(!Main()){
			puts("NO");
		}
	}
	return 0;
}
