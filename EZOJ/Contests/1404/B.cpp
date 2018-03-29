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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=410;
struct Pt{
	int x,y;
	inline friend Pt operator * (const Pt &a,const int &b){return (Pt){a.x*b,a.y*b};}
	inline friend Pt operator + (const Pt &a,const Pt &b){return (Pt){a.x+b.x,a.y+b.y};}
	inline friend Pt operator - (const Pt &a,const Pt &b){return (Pt){a.x-b.x,a.y-b.y};}
	inline friend lint crs(const Pt &a,const Pt &b){return (lint)a.x*b.y-(lint)a.y*b.x;}
}pt[N];
inline bool flat(int i,int j,int k){
	return crs(pt[j]-pt[i],pt[k]-pt[i])==0;
}
struct Movement{
	int i,j,k;
};
vector<Movement>vec;
inline void putop(int i,int j,int k){
	vec.push_back((Movement){i,j,k});
	pt[k]=pt[i]+pt[j]-pt[k];
}
inline void putop(Pt *i,Pt *j,Pt *k){
	putop(i-pt,j-pt,k-pt);
}
inline void work(int _a,int _b,int _c){
	assert(!flat(_a,_b,_c));
	Pt *a=pt+_a,*b=pt+_b,*c=pt+_c;
	int p=-min(a->x,min(b->x,c->x));
	int q=-min(a->y,min(b->y,c->y));
	apmax(p,0),apmax(q,0);
	Pt v1=*b-*a,v2=*c-*a;
	int mv1=p*v2.y-q*v2.x,mv2=q*v1.x-p*v1.y;
	if(mv1*v1.x+mv2*v2.x<0||mv1*v1.y+mv2*v2.y<0){
		mv1=-mv1,mv2=-mv2;
	}
	while(min(min(a->x,a->y),min(min(b->x,b->y),min(c->x,c->y)))<0){
		if(mv1>0){
			putop(b,c,a),putop(a,b,c);
			_a=b-pt,_b=c-pt,_c=a-pt;
			mv1--;
		}else if(mv1<0){
			putop(a,c,b),putop(a,b,c);
			_a=c-pt,_b=a-pt,_c=b-pt;
			mv1++;
		}
		a=pt+_a,b=pt+_b,c=pt+_c;
		if(mv2>0){
			putop(b,c,a),putop(a,c,b);
			_a=c-pt,_b=a-pt,_c=b-pt;
			mv2--;
		}else if(mv2<0){
			putop(a,b,c),putop(a,c,b);
			_a=b-pt,_b=c-pt,_c=a-pt;
			mv2++;
		}
		a=pt+_a,b=pt+_b,c=pt+_c;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("parallel.in","r",stdin);
	freopen("parallel.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	for(int i=1,j,k;i<=n;i++){
		if(min(pt[i].x,pt[i].y)<0){
			bool flag=false;
			for(j=1;j<=n;j++){
				if(i!=j){
					for(k=1;k<=n;k++){
						if(i!=k&&j!=k&&!flat(i,j,k)){
							flag=true;
							break;
						}
					}
				}
				if(flag)break;
			}
			work(i,j,k);
		}
	}
	printf("%lu\n",vec.size());
	for(vector<Movement>::iterator it=vec.begin();it!=vec.end();it++){
		printf("%d %d %d\n",it->i,it->j,it->k);
	}
	return 0;
}
