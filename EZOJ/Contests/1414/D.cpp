#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <map>
#include <set>
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
const int N=50010,M=300010;
int a[N];
int fa[N],size[N],sum[N];
int grt(int x){
	for(;fa[x]!=x;x=fa[x]);
	return x;
}
struct pii{
	int x,y;
	inline friend bool operator < (const pii &a,const pii &b){
		return a.x!=b.x?a.x<b.x:a.y<b.y;
	}
};
multiset<int>s;
int op[M],xpt[M],vpt[M];
namespace seg{
	const int N=::M<<1;
	struct Node;
	typedef Node* node;
	typedef vector<pii>vp;
	struct Node{
		node lson,rson;
		int l,m,r;
		vp vec;
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void cov(node x,int l,int r,const pii &p){
		if(x->l==l&&x->r==r){
			x->vec.push_back(p);
		}else if(r<=x->m){
			cov(x->lson,l,r,p);
		}else if(l>x->m){
			cov(x->rson,l,r,p);
		}else{
			cov(x->lson,l,x->m,p);
			cov(x->rson,x->m+1,r,p);
		}
	}
	void solve(node x){
		//make
		for(vp::iterator it=x->vec.begin(),ti=x->vec.end();it!=ti;++it){
			int &x=it->x=grt(it->x),&y=it->y=grt(it->y);
			if(x==y)continue;
			if(size[x]>size[y]){
				swap(x,y);
			}
			fa[x]=y;
			size[y]+=size[x];
			s.erase(s.find(sum[y]));
			s.erase(s.find(sum[x]));
			sum[y]+=sum[x];
			s.insert(sum[y]);
		}
		if(x->l<x->r){
			solve(x->lson),solve(x->rson);
		}else{
			if(op[x->l]==3){
				int p=xpt[x->l];
				int dt=vpt[x->l]-a[p];
				a[p]=vpt[x->l];
				for(;fa[p]!=p;p=fa[p]){
					sum[p]+=dt;
				}
				s.erase(s.find(sum[p]));
				s.insert(sum[p]+=dt);
			}
			printf("%d\n",*s.rbegin());
		}
		//undo
		for(vp::reverse_iterator it=x->vec.rbegin(),ti=x->vec.rend();it!=ti;++it){
			int x=it->x,y=it->y;
			if(x==y)continue;
			s.erase(s.find(sum[y]));
			sum[y]-=sum[x];
			s.insert(sum[x]);
			s.insert(sum[y]);
			size[y]-=size[x];
			fa[x]=x;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("packet.in","r",stdin);
	freopen("packet.out","w",stdout);
#endif
	int n=ni,m=ni,t=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		fa[i]=i;
		size[i]=1;
		sum[i]=a[i];
		s.insert(a[i]);
	}
	map<pii,int>mp;
	seg::node rt=seg::build(1,m);
	for(int i=1;i<=m;i++){
		op[i]=ni,xpt[i]=ni,vpt[i]=ni;
		if(op[i]<3){
			pii t=(pii){xpt[i],vpt[i]};
			if(t.x>t.y){
				swap(t.x,t.y);
			}
			map<pii,int>::iterator it=mp.find(t);
			if(it==mp.end()){//insert
				mp[t]=i;
			}else{//delete
				seg::cov(rt,it->second,i-1,t);
				mp.erase(it);
			}
		}
	}
	for(map<pii,int>::iterator it=mp.begin();it!=mp.end();++it){
		seg::cov(rt,it->second,m,it->first);
	}
	printf("%d\n",*s.rbegin());
	seg::solve(rt);
	return 0;
}
