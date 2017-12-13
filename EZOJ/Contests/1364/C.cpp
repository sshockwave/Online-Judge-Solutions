#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
const int M=4,S=166,O=998244353,T=1010;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
struct pti{
	int a[M];
	inline friend bool operator < (const pti &x,const pti &y){
		for(int i=0;i<M;i++){
			if(x.a[i]!=y.a[i])return x.a[i]<y.a[i];
		}
		return false;
	}
	inline friend ostream & operator << (ostream & out,const pti &b){
		out<<"[";
		for(int i=0;i<=2;i++){
			out<<b.a[i]<<",";
		}
		out<<"\b]";
		return out;
	}
}stat[S];
int scnt=0;
map<pti,int>mp;
struct Mat{
	const static int D=S;
	int a[D][D];
	inline friend Mat operator * (const Mat &a,const Mat &b){
		Mat c;
		for(int i=0;i<=scnt;i++){
			for(int j=0;j<=scnt;j++){
				lint tmp=0;
				for(int k=0;k<=scnt;k++){
					tmp+=(lint)a.a[i][k]*b.a[k][j]%O;
				}
				c.a[i][j]=tmp%O;
			}
		}
		return c;
	}
	inline void operator = (const Mat &b){
		for(int i=0;i<=scnt;i++){
			memcpy(a[i],b.a[i],(scnt+1)<<2);
		}
	}
}pw[70],res;
int m,k;
void dfs(pti s){
	if(mp.find(s)!=mp.end())return;
	int x=++scnt;
	stat[x]=s;
	mp[s]=x;
	for(int j=1;j<=m;j++){
		if(stat[x].a[j]==0)continue;
		pti tmp=s;
		if(tmp.a[0]&&j>1){
			tmp.a[0]--,tmp.a[m]++;
		}
		tmp.a[j-1]++,tmp.a[j]--;
		dfs(tmp);
	}
}
lint ask[T];
int main(){
#ifndef ONLINE_JUDGE
	freopen("slave.in","r",stdin);
	freopen("slave.out","w",stdout);
#endif
	int tot=ni;
	m=ni,k=ni;
	{
		pti tmp=(pti){k-1,0,0,0};
		tmp.a[m]=1;
		dfs(tmp);
	}
	Mat &trans=pw[0];
	memset(&trans,0,sizeof(trans));
	trans.a[0][0]=1;
	for(int i=1;i<=scnt;i++){
		int fact=inv(k-stat[i].a[0]+1);
		trans.a[0][i]=fact;
		trans.a[i][i]=fact;
		for(int j=1;j<=m;j++){
			if(stat[i].a[j]==0)continue;
			pti tmp=stat[i];
			if(tmp.a[0]&&j>1){
				tmp.a[0]--,tmp.a[m]++;
			}
			tmp.a[j-1]++,tmp.a[j]--;
			(trans.a[mp[tmp]][i]+=(lint)stat[i].a[j]*fact%O)%=O;
		}
	}
	lint mx=0;
	for(int i=1;i<=tot;i++){
		ask[i]=next_num<lint>();
		apmax(mx,ask[i]);
	}
	mx>>=1;
	for(int sh=1;mx;mx>>=1,sh++){
		pw[sh]=pw[sh-1]*pw[sh-1];
	}
	for(int i=1;i<=tot;i++){
		bool flag=true;
		for(int sh=0;ask[i];ask[i]>>=1,sh++){
			if(ask[i]&1){
				if(flag){
					res=pw[sh];
					flag=false;
				}else{
					res=res*pw[sh];
				}
			}
		}
		printf("%d\n",flag?0:res.a[0][1]);
	}
	return 0;
}
