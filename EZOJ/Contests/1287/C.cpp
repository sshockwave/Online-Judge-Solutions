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
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=55,L=110,D=L*2,SIGMA=26,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
struct ACAutomaton{
	struct node{
		int son[SIGMA],fail;
		bool end;
		char c;
		node(){
			memset(son,0,sizeof(son));
		}
	}pol[D];
	int pool;
	ACAutomaton():pool(1){}
	void insert(int id,char s[]){
		node &x=pol[id];
		if((*s)==0){
			x.end=true;
			return;
		}
		int c=(*s)-'a';
		if(x.son[c]==0){
			x.son[c]=++pool;
			pol[pool].c=*s;
		}
		insert(x.son[c],s+1);
	}
	void build(int id){//assert fail ok
		node &x=pol[id];
		for(int i=0;i<26;i++){
			if(x.son[i]){
				int p=x.fail;
				for(;p&&pol[p].son[i]==0;p=pol[p].fail);
				pol[x.son[i]].fail=pol[p].son[i];
				build(x.son[i]);
			}
		}
	}
	void build(){
		for(int i=0;i<SIGMA;i++){
			pol[0].son[i]=1;
		}
		pol[1].fail=0;
		build(1);
	}
	int digest(int p,char c){
		node &x=pol[p];
		if(x.end){
			return -1;
		}
		c-='a';
		for(;p&&pol[p].son[c]==0;p=pol[p].fail);
		if(pol[pol[p].son[c]].end){
			return -1;
		}
		return pol[p].son[c];
	}
}ac;
int n,m,lim;
int len1[N],len2[N];
char s[N][L],t[N][L];//t:forbidden
namespace solve1{
	int f[L*2][D];
	int to[D][N];//to[at][str]
	inline int work(){
		for(int i=1;i<=ac.pool;i++){
			for(int j=1;j<=n;j++){
				to[i][j]=i;
				for(int k=0;s[j][k];k++){
					to[i][j]=ac.digest(to[i][j],s[j][k]);
					if(to[i][j]==-1){
						break;
					}
				}
			}
		}
		f[0][1]=1;
		for(int i=0;i<lim;i++){
			for(int j=1;j<=ac.pool;j++){
				if(f[i][j]==0){
					continue;
				}
				for(int k=1;k<=n;k++){
					if(~to[j][k]){
						apadd(f[i+len1[k]][to[j][k]],f[i][j]);
					}
				}
			}
		}
		int ans=0;
		for(int i=1;i<=ac.pool;i++){
			apadd(ans,f[lim][i]);
		}
		return ans;
	}
}
namespace solve2{
	int len;
	struct Matrix{
		int num[D][D];
		Matrix(){
			memset(num,0,sizeof(num));
		}
		inline int* operator [] (int i){
			return num[i];
		}
		inline friend Matrix operator * (Matrix &a,Matrix &b){
			Matrix c;
			for(int i=1;i<=len;i++){
				for(int j=1;j<=len;j++){
					for(int k=1;k<=len;k++){
						apadd(c[i][j],mul(a[i][k],b[k][j]));
					}
				}
			}
			return c;
		}
	}trans,ret;
	inline void fpow(int exp){
		for(int i=1;i<=len;i++){
			ret[i][i]=1;
		}
		for(;exp;exp>>=1,trans=trans*trans){
			if(exp&1){
				ret=ret*trans;
			}
		}
	}
	inline int work(){
		int half=ac.pool;
		len=half<<1;
		for(int i=1;i<=half;i++){
			for(int j=1;j<=n;j++){
				int t1=ac.digest(i,s[j][0]);
				if(t1==-1){
					continue;
				}
				if(len1[j]==1){
					apadd(trans[t1][i],1);
				}else{
					apadd(trans[t1+half][i],1);
				}
			}
		}
		for(int i=1;i<=half;i++){
			for(int j=1;j<=n;j++){
				if(len1[j]==2&&ac.pol[i].c==s[j][0]){
					int t2=ac.digest(i,s[j][1]);
					if(~t2){
						apadd(trans[t2][i+half],1);
					}
				}
			}
		}
		fpow(lim);
		int ans=0;
		for(int i=1;i<=half;i++){
			apadd(ans,ret[i][1]);
		}
		return ans;
	}
}
int main(){
	n=ni,m=ni,lim=ni;
	int mxlen=0;
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]);
		len1[i]=strlen(s[i]);
		apmax(mxlen,len1[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%s",t[i]);
		ac.insert(1,t[i]);
		len2[i]=strlen(t[i]);
	}
	ac.build();
	if(mxlen<=2){
		printf("%d\n",solve2::work());
	}else{
		printf("%d\n",solve1::work());
	}
}
