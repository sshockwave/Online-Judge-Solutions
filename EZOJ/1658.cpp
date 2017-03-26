#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
const int N=100010,D=1700000;
#define lson(x) son[x][0]
#define rson(x) son[x][1]
int root[N],son[D][2],ints[D],ntop=1;
bool tol[D],tor[D];
inline void push_up(int x){
	ints[x]=ints[lson(x)]+ints[rson(x)]-(tor[lson(x)]&&tol[rson(x)]);
	assert(lson(x)||rson(x));
	tol[x]=tol[lson(x)];
	tor[x]=tor[rson(x)];
}
void alter(int &x,int l,int r,int p){
	if(x==0){
		x=ntop++;
	}
	int mid=(l+r)>>1;
	if(l==r){
		tol[x]=tor[x]=true;
		ints[x]=1;
		return;
	}
	if(p<=mid){
		alter(lson(x),l,mid,p);
	}else{
		alter(rson(x),mid+1,r,p);
	}
	push_up(x);
}
void merge(int &x,int y,int l,int r){
	if(x&y){
		int mid=(l+r)>>1;
		merge(lson(x),lson(y),l,mid);
		merge(rson(x),rson(y),mid+1,r);
		push_up(x);
	}else{
		x+=y;
	}
}
int main(){
	memset(ints,0,sizeof(ints));
	memset(son,0,sizeof(son));
	memset(root,0,sizeof(root));
	memset(tol,0,sizeof(tol));
	memset(tor,0,sizeof(tor));
	int n=ni(),tot=ni(),ans=0;
	for(int i=1;i<=n;i++){
		alter(root[ni()],1,n,i);
	}
	for(int i=1;i<=n;i++){
		ans+=ints[root[i]];
	}
	while(tot--){
		if(ni()==1){
			int x=ni(),y=ni();
			if(x!=y){
				ans-=ints[root[x]]+ints[root[y]];
				merge(root[y],root[x],1,n);
				ans+=ints[root[y]];
			}
		}else{
			printf("%d\n",ans);
		}
	}
}
