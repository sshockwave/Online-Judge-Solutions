#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=310;
const double EPS=1e-8;
struct Trie{
	static const int D=N*N;
	int son[D][2],fail[D],end[D],ntop;
	inline void reset(){
		ntop=1;
		memset(son,0,sizeof(son));
		memset(fail,0,sizeof(fail));
		memset(end,0,sizeof(end));
		son[0][0]=1,son[0][1]=1;
	}
	inline int nn(){
		return ++ntop;
	}
	inline int insert(char s[],int bln){
		int x=1;
		for(int i=0;s[i];i++){
			bool d=s[i]=='H';
			x=son[x][d]?son[x][d]:(son[x][d]=nn());
		}
		end[x]=bln;
		return x;
	}
	inline int go(int x,bool d){
		for(;x&&son[x][d]==0;x=fail[x]);
		return son[x][d];
	}
	void build(int x){//assert fail ready
		for(int i=0;i<2;i++){
			if(son[x][i]){
				fail[son[x][i]]=go(fail[x],i);
				build(son[x][i]);
			}
		}
	}
}T;
int to[N][2];
char s[N];
double f[2][N*N],ans[N];
int main(){
	T.reset();
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		T.insert(s,i);
	}
	T.build(1);
	for(int i=1;i<=T.ntop;i++){
		to[i][0]=T.go(i,0);
		to[i][1]=T.go(i,1);
	}
	memset(f,0,sizeof(f));
	memset(ans,0,sizeof(ans));
	double sum=1,*F=f[0],*NF=f[1];
	F[1]=1;
	for(;sum>EPS;swap(F,NF)){
		for(int i=1;i<=T.ntop;i++){
			NF[i]=0;
		}
		for(int i=1;i<=T.ntop;i++){
			if(T.end[i]==0){
				NF[to[i][0]]+=F[i]/2;
				NF[to[i][1]]+=F[i]/2;
			}
		}
		sum=0;
		for(int i=1;i<=T.ntop;i++){
			if(T.end[i]){
				ans[T.end[i]]+=NF[i];
			}else{
				sum+=NF[i];
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%.8lf\n",ans[i]);
	}
}
