#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define M 300010
#define N 155
#define R 550
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
struct edge{
	int u,v;
}e[M];
struct bit{
	unsigned int digit[5];
	inline void set(int x){
		digit[x>>5]|=1u<<(x&31);
	}
	inline void flip(int x){
		digit[x>>5]^=1u<<(x&31);
	}
	inline void setall(){
		for(int i=0;i<5;i++){
			digit[i]=0xffffffffu;
		}
	}
	void operator |= (bit b){
		for(int i=0;i<5;i++){
			digit[i]|=b.digit[i];
		}
	}
}nvis;
struct con{
	bit node[N];
	void operator |= (con b){
		for(int i=0;i<N;i++){
			node[i]|=b.node[i];
		}
	}
	inline void clearall(){
		memset(node,0,sizeof(node));
	}
}st[R][12],res;
bit operator | (bit a,bit b){
	bit c;
	for(int i=0;i<5;i++){
		c.digit[i]=a.digit[i]|b.digit[i];
	}
	return c;
}
bit operator & (bit a,bit b){
	bit c;
	for(int i=0;i<5;i++){
		c.digit[i]=a.digit[i]&b.digit[i];
	}
	return c;
}
con operator | (con a,con b){
	con c;
	for(int i=0;i<N;i++){
		c.node[i]=a.node[i]|b.node[i];
	}
	return c;
}
int n,stk[N],stop=0;
void dfs1(int x){
	nvis.flip(x);
	bit stat=nvis&res.node[x];
	for(int i=0;i<5;i++){
		if(stat.digit[i]){
			for(int j=0;j<32;j++){
				if(stat.digit[i]&(1<<j)){
					dfs1((i<<5)|j);
				}
			}
		}
	}
	stk[stop++]=x;
}
void dfs2(){
	
}
int main(){
	n=ni();
	int m=ni(),tot=ni();
	for(int i=0;i<m;i++){//from 0 to m-1
		e[i].u=ni(),e[i].v=ni();
		st[i/R][0].node[e[i].u].set(e[i].v);
	}
	int bcnt=m/R+1;
	for(int i=1;(1<<i)<bcnt;i++){
		for(int j=0;j+(1<<i)<=bcnt;j++){
			st[j][i]=st[j][i-1]|st[j+(1<<(i-1))][i-1];
		}
	}
	while(tot--){
		int l=ni()-1,r=ni()-1,bl,br;
		bl=l/R,br=r/R;
		res.clearall();
		if(bl==br){
			for(int i=l;i<=r;i++){
				res.node[e[i].u].set(e[i].v);
			}
		}else{
			if(l%R){
				bl++;
				for(int i=l,top=bl*R;i<top;i++){
					res.node[e[i].u].set(e[i].v);
				}
			}
			if((r+1)%R){
				br--;
				for(int i=r/R*R,top;i<=r;i++){
					res.node[e[i].u].set(e[i].v);
				}
			}
			if(bl<=br){//st query
				int i=0;
				for(;bl+(1<<i)<=br;i++);
				i--;
				res|=st[bl][i]|st[br-(1<<i)+1][i];
			}
		}
		nvis.setall();
	}
}
