#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include "oath.h"
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=300010,D=N*2;
int tim=0;
#define lson(x) son[x][0]
#define rson(x) son[x][1]
int son[D][2],tag[D],nn=0;
Data val[D];
int root[N],last[N],len[N];
inline int renew(int x){
	if(tag[x]<tim){
		nn++;
		lson(nn)=lson(x),rson(nn)=rson(x);
		val[nn]=val[x];
		tag[nn]=tim;
		x=nn;
	}
	return x;
}
int ins(int x,int p,const Data &v,int l=1,int r=N-1){
	x=renew(x);
	if(l==r){
		val[x]=v;
		return x;
	}
	int mid=(l+r)>>1;
	if(p<=mid){
		lson(x)=ins(lson(x),p,v,l,mid);
		val[x]=val[lson(x)];
	}else{
		rson(x)=ins(rson(x),p,v,mid+1,r);
		val[x]=F(val[lson(x)],val[rson(x)]);
	}
	return x;
}
Data ask(int x,int l,int r,int lend=1,int rend=N-1){
	if(lend==l&&rend==r){
		return val[x];
	}
	int mid=(lend+rend)>>1;
	if(r<=mid){
		return ask(lson(x),l,r,lend,mid);
	}else if(l>mid){
		return ask(rson(x),l,r,mid+1,rend);
	}else{
		return F(ask(lson(x),l,mid,lend,mid),ask(rson(x),mid+1,r,mid+1,rend));
	}
}
void Init(){
	memset(tag,0,sizeof(tag));
	memset(son,0,sizeof(son));
	memset(val,0,sizeof(val));
	memset(root,0,sizeof(root));
	memset(last,0,sizeof(last));
	memset(len,0,sizeof(len));
}
void Add_element(int id, Data x){
	last[++tim]=id;
	len[tim]=len[id]+1;
	root[tim]=ins(root[id],len[tim],x);
}
void Del_element(int id){
	id=last[id];
	root[++tim]=root[id];
	last[tim]=last[id];
	len[tim]=len[id];
}
Data Query_range(int id,int l,int r){
	return ask(root[id],l,r);
}
