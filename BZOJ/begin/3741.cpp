#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define M 300010
#define N 5//150
#define R 2//550
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
	bool operator [] (int x){
		return digit[x>>5]&(1u<<(x&31));
	}
}nvis;
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
}st[R][12],res,revst[R][12],revres;
con operator | (con a,con b){
	con c;
	for(int i=0;i<N;i++){
		c.node[i]=a.node[i]|b.node[i];
	}
	return c;
}
ostream & operator << (ostream & out,bit b){
	for(int i=0;i<N;i++){
		if(b[i]){
			putchar(i+'0');
		}else{
			putchar(' ');
		}
	}
	return out;
}
ostream & operator << (ostream & out,con b){
	for(int i=1;i<N;i++){
		out<<"node["<<i<<"]:"<<b.node[i]<<endl;
	}
	return out;
}
int n,stk[N],stop=0;
void dfs1(int x){
	cout<<"DFS1:"<<x<<endl;
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
int dfs2(int x){
	cout<<"DFS2:"<<x<<endl;
	nvis.flip(x);
	bit stat=nvis&revres.node[x];
	int size=1;
	for(int i=0;i<5;i++){
		if(stat.digit[i]){
			for(int j=0;j<32;j++){
				if(stat.digit[i]&(1<<j)){
					size+=dfs2((i<<5)|j);
				}
			}
		}
	}
	return size;
}
int main(){
	freopen("3741.in","r",stdin);
	n=ni();
	int m=ni(),tot=ni();
	for(int i=0;i<m;i++){//from 0 to m-1
		e[i].u=ni(),e[i].v=ni();
		st[i/R][0].node[e[i].u].set(e[i].v);
		revst[i/R][0].node[e[i].v].set(e[i].u);
	}
	int bcnt=(m-1)/R+1;
	for(int i=1;(1<<i)<bcnt;i++){
		cout<<"i="<<i<<"\tn="<<n<<endl;
		assert(n);
		for(int j=0;j+(1<<i)<=bcnt;j++){
			cout<<"j="<<j<<"\tn="<<n<<endl;
			st[j][i]=st[j][i-1]|st[j+(1<<(i-1))][i-1];
			revst[j][i]=revst[j][i-1]|revst[j+(1<<(i-1))][i-1];
		}
	}
	assert(n);
	while(tot--){
		int l=ni()-1,r=ni()-1,bl,br,ans=0;
		bl=l/R,br=r/R;
		res.clearall();
		revres.clearall();
		if(bl==br){
			for(int i=l;i<=r;i++){
				res.node[e[i].u].set(e[i].v);
				revres.node[e[i].v].set(e[i].u);
			}
		}else{
			if(l%R){
				bl++;
				for(int i=l,top=bl*R;i<top;i++){
					res.node[e[i].u].set(e[i].v);
					revres.node[e[i].v].set(e[i].u);
				}
			}
			if((r+1)%R){
				br--;
				for(int i=r/R*R,top;i<=r;i++){
					res.node[e[i].u].set(e[i].v);
					revres.node[e[i].v].set(e[i].u);
				}
			}
			if(bl<=br){//st query
				int i=0;
				for(;bl+(1<<i)-1<br;i++);
				res|=st[bl][i]|st[br-(1<<i)+1][i];
				revres|=revst[bl][i]|revst[br-(1<<i)+1][i];
			}
		}
		nvis.setall();
		cout<<"query:["<<l<<","<<r<<"]"<<endl;
		cout<<"res:"<<endl<<res<<"revres:"<<endl<<revres;
		cout<<"n="<<n<<endl;
		cout<<"nvis:"<<nvis<<endl;
		for(int i=1;i<=n;i++){
			cout<<"Looping"<<endl;
			if(nvis[i]){
				dfs1(i);
			}
		}
		nvis.setall();
		while(stop){
			if(nvis[stk[--stop]]){
				int cur=dfs2(stop);
				ans+=cur*(cur-1)/2;
			}
		}
		printf("%d\n",ans);
	}
}
