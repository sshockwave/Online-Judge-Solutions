#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <set>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
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
const int N=100010;
int a[N],b[N],c[N];
int lst[N];
inline bool bccmp(int x,int y){
	return b[x]-c[x]>b[y]-c[y];
}
struct bacmp{
	inline bool operator () (int x,int y){
		int v1=b[x]-a[x],v2=b[y]-a[y];
		return v1!=v2?v1<v2:x<y;
	}
};
struct cacmp{
	inline bool operator () (int x,int y){
		int v1=c[x]-a[x],v2=c[y]-a[y];
		return v1!=v2?v1<v2:x<y;
	}
};
set<int,bacmp>sb1,sb2;
set<int,cacmp>sc1,sc2;
lint ans=0;
template<class T>inline void ins(T &cur,T &bak,int ele,uint amt,int b[]){
	ans+=b[ele];
	cur.insert(ele);
	if(cur.size()>amt){
		int tmp=*cur.begin();
		cur.erase(cur.begin());
		ans+=a[tmp]-b[tmp];
		bak.insert(tmp);
	}
}
template<class T>inline void del(T &cur,T &bak,int ele,uint amt,int b[]){
	if(cur.find(ele)==cur.end()){
		bak.erase(ele);
		ans-=a[ele];
	}else{
		cur.erase(ele);
		ans-=b[ele];
		if(cur.size()<amt&&!bak.empty()){
			int tmp=*--bak.end();
			bak.erase(--bak.end());
			ans+=b[tmp]-a[tmp];
			cur.insert(tmp);
		}
	}
}
int main(){
	int x=ni,y=ni,z=ni,n=x+y+z;
	for(int i=1;i<=n;i++){
		a[i]=ni,b[i]=ni,c[i]=ni,lst[i]=i;
	}
	sort(lst+1,lst+n+1,bccmp);
	for(int i=1;i<=y;i++){
		ins(sb1,sb2,lst[i],y,b);
	}
	for(int i=y+1;i<=n;i++){
		ins(sc1,sc2,lst[i],z,c);
	}
	lint fin=ans;
	for(int i=y+1;i<=n-z;i++){
		del(sc1,sc2,lst[i],z,c);
		ins(sb1,sb2,lst[i],y,b);
		apmax(fin,ans);
	}
	printf("%lld\n",fin);
	return 0;
}
