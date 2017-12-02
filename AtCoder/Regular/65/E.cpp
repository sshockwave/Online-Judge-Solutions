#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=100010;
struct Pt{
	lint x,y;
	int id;
	inline Pt to1(){
		return (Pt){y-x,x+y,id};
	}
	inline Pt to2(){
		return (Pt){x+y,y-x,id};
	}
	inline friend Pt operator + (const Pt &a,const Pt &b){
		return (Pt){a.x+b.x,a.y+b.y};
	}
	inline friend bool operator < (const Pt &a,const Pt &b){
		return a.x!=b.x?a.x<b.x:a.y<b.y;
	}
}pt[N],pt1[N],pt2[N];
int n;
set<Pt>s1,s2;
lint ans=0;
int que[N],qh=0,qt=0;
inline void psh(int v){
	s1.erase(pt[v].to1());
	s2.erase(pt[v].to2());
	que[qt++]=v;
}
inline void work(Pt pt[],set<Pt>&s,Pt l,Pt r){
	ans+=upper_bound(pt+1,pt+n+1,r)-lower_bound(pt+1,pt+n+1,l);
	set<Pt>::iterator it1=s.lower_bound(l);
	set<Pt>::iterator it2=s.upper_bound(r);
	for(;it1!=it2;psh((*(it1++)).id));
}
int main(){
	n=ni;
	int a=ni,b=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni,i};
		s1.insert(pt1[i]=pt[i].to1());
		s2.insert(pt2[i]=pt[i].to2());
	}
	sort(pt1+1,pt1+n+1);
	sort(pt2+1,pt2+n+1);
	lint d=cabs(pt[a].x-pt[b].x)+cabs(pt[a].y-pt[b].y);
	if(d==0){
		puts("1");
		return 0;
	}
	psh(a);
	for(;qh<qt;qh++){
		Pt cur=pt[que[qh]];
		Pt pt1=(Pt){cur.x+d,cur.y};
		Pt pt2=(Pt){cur.x,cur.y+d};
		Pt pt3=(Pt){cur.x-d,cur.y};
		Pt pt4=(Pt){cur.x,cur.y-d};
		work(::pt2,s2,pt1.to2(),pt2.to2()+(Pt){0,-1});
		work(::pt1,s1,pt3.to1()+(Pt){0,1},pt2.to1());
		work(::pt2,s2,pt4.to2()+(Pt){0,1},pt3.to2());
		work(::pt1,s1,pt4.to1(),pt1.to1()+(Pt){0,-1});
	}
	printf("%lld\n",ans>>1);
	return 0;
}
