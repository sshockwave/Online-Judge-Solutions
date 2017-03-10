#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 50010
#define D (N*2)
#define lson(x) son[x][0]
#define rson(x) son[x][1]
#define ROOT 0
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
int year[N],rain[N],mx[D],lend[D],rend[D],mid[D],son[D][2],ntop=0,n;
bool gap[D];
inline void push_up(int x){
	assert(lend[x]!=rend[x]);
	mx[x]=max(mx[lson(x)],mx[rson(x)]);
	gap[x]=gap[lson(x)]||gap[rson(x)]||(year[mid[x]]+1!=year[mid[x]+1]);
}
int build(int l,int r){
	int x=ntop++;
	lend[x]=l,rend[x]=r,mid[x]=(l+r)>>1;
	if(l==r){
		mx[x]=rain[l];
		gap[x]=false;
	}else{
		lson(x)=build(l,mid[x]);
		rson(x)=build(mid[x]+1,r);
		push_up(x);
	}
	return x;
}
bool ask_gap(int x,int l,int r){
	assert(l<=r);
	if(l==lend[x]&&r==rend[x]){
		return gap[x];
	}
	if(r<=mid[x]){
		return ask_gap(lson(x),l,r);
	}
	if(l>mid[x]){
		return ask_gap(rson(x),l,r);
	}
	return year[mid[x]]+1!=year[mid[x]+1]||ask_gap(lson(x),l,mid[x])||ask_gap(rson(x),mid[x]+1,r);
}
int ask_mx(int x,int l,int r){
	assert(l<=r);
	if(l==lend[x]&&r==rend[x]){
		return mx[x];
	}
	if(r<=mid[x]){
		return ask_mx(lson(x),l,r);
	}
	if(l>mid[x]){
		return ask_mx(rson(x),l,r);
	}
	return max(ask_mx(lson(x),l,mid[x]),ask_mx(rson(x),mid[x]+1,r));
}
int get_id(int y){
	int l=1,r=n,m;
	while(l<r){
		m=(l+r)>>1;
		if(year[m]<y){
			l=m+1;
		}else if(year[m]>y){
			r=m;
		}else{
			return m;
		}
	}
	return l;
}
int main(){
	n=ni();
	for(int i=1;i<=n;i++){
		year[i]=ni(),rain[i]=ni();
	}
	build(1,n);
	for(int tot=ni(),x,y;tot--;){
		y=get_id(ni()),x=get_id(ni());
		if(x<=y){
			puts("false");
		}else if(rain[x]>rain[y]){
			puts("false");
		}else if(x==y+1){
			puts("true");
		}else if(ask_mx(ROOT,y+1,x-1)>=rain[x]){
			puts("false");
		}else if(ask_gap(ROOT,y,x)){
			puts("maybe");
		}else{
			puts("true");
		}
	}
}
