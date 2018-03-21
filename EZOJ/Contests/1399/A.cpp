#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
using namespace std;
typedef double db;
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
const int N=5010;
const db EPS=1e-8;
struct Pt{
	int x,y;
	inline lint d2(){return (lint)x*x+(lint)y*y;}
	inline friend Pt operator + (const Pt &a,const Pt &b){return (Pt){a.x+b.x,a.y+b.y};};
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};};
	inline friend lint dot(const Pt &a,const Pt &b){return (lint)a.x*b.x+(lint)a.y*b.y;};
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;};
}pt[N<<1],seg[N];
queue<int>q;
set<int>s;
db oldans,newans;
inline db disid(int u,int v){
	return sqrt((pt[u]-pt[v]).d2());
}
inline int sgn(lint x){
	return x>0?1:x<0?-1:0;
}
inline bool intersect(Pt u1,Pt v1,Pt u2,Pt v2){
	return sgn(crs(u1-v1,u2-v1))*sgn(crs(u1-v1,v2-v1))<0&&sgn(crs(u2-v2,u1-v2))*sgn(crs(u2-v2,v1-v2))<0;
}
inline bool work(){
	if(q.empty())return false;
	int x=q.front();
	q.pop();
	int &A=seg[x].x,&B=seg[x].y;
	for(set<int>::iterator it=s.begin();it!=s.end();it++){
		int y=*it;
		int &C=seg[y].x,&D=seg[y].y;
		if(!intersect(pt[A],pt[B],pt[C],pt[D]))continue;
		db pre=disid(A,B)+disid(C,D);
		db nxt1=disid(A,C)+disid(B,D);
		db nxt2=disid(A,D)+disid(B,C);
		if(nxt1>nxt2){
			swap(B,C);
			newans+=nxt1-pre;
			s.erase(it);
			q.push(x),q.push(y);
			return true;
		}else{
			swap(B,D);
			newans+=nxt2-pre;
			s.erase(it);
			q.push(x),q.push(y);
			return true;
		}
	}
	s.insert(x);
	return true;
}
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("nonintersect.in","r",stdin);
	freopen("nonintersect.out","w",stdout);
#endif
	srand(990099);
	int n=ni;
	for(int i=1;i<=(n<<1);i++){
		pt[i]=(Pt){ni,ni};
	}
	for(int i=1;i<=n;i++){
		seg[i]=(Pt){ni,ni};
		oldans+=disid(seg[i].x,seg[i].y);
	}
	newans=oldans;
	for(int i=1;i<=n;i++){
		a[i]=i;
	}
	random_shuffle(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		q.push(a[i]);
	}
	while(work());
	for(int i=1;i<=n;i++){
		printf("%d %d\n",seg[i].x,seg[i].y);
	}
	return 0;
}
