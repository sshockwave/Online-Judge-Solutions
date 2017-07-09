#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
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
inline void apmin(int &a,const int &b){
	if(b<a){
		a=b;
	}
}
const int P=10007,P32=1001000,INF=0x7f7f7f7f;
int MOD,rtP;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return a*b%MOD;
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ans=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ans,x);
		}
	}
	return ans;
}
struct Matrix{
	int a[3][3];
	inline friend Matrix operator * (const Matrix &a,const Matrix &b){
		Matrix c;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				int sum=0;
				for(int k=0;k<3;k++){
					sum+=a.a[i][k]*b.a[k][j];
				}
				c.a[i][j]=sum%MOD;
			}
		}
		return c;
	}
	inline void operator ^= (int n){
		static Matrix tmp;
		if(n==0){
			static Matrix id=(Matrix){1,0,0,0,1,0,0,0,1};
			tmp=*this;
			*this=id;
		}
		*this^=n>>1;
		*this=(*this)*(*this);
		if(n&1){
			*this=(*this)*tmp;
		}
	}
}bstep,gstep;
struct Vector{
	int a[2];
	inline friend Vector operator * (const Matrix &a,const Vector &b){
		Vector c;
		for(int i=0;i<3;i++){
			int sum=0;
			for(int j=0;j<2;j++){
				sum+=a.a[i][j]*b.a[j];
			}
			c.a[i]=(sum+a.a[i][2])%MOD;
		}
		return c;
	}
	inline int hash(){
		return a[0]*MOD+a[1];
	}
};
namespace H{
	const int MOD=1000003;
	int to[P32],val[P32],bro[P32],head[MOD],e;
	inline void init(){
		memset(head,-1,sizeof(head));
		e=0;
	}
	inline bool ins(int u,int v){
		int x=u%MOD;
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]==u){
				return false;
			}
		}
		to[e]=u,val[e]=v,bro[e]=head[x],head[x]=e++;
		return true;
	}
	inline int eval(int u){
		int x=u%MOD;
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]==u){
				return val[i];
			}
		}
		return -1;
	}
}
inline int bsgs(Vector vec){
	for(int i=0;i<rtP;i++,vec=bstep*vec){
		int val=H::eval(vec.hash());
		if(~val){
			return val-i;
		}
	}
	return -1;
}
int cnt[2],a[P],as,loop;
inline int bitchop(int n){
	int l=0,r=as+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(a[mid]>n){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	return l;
}
inline lint calc(lint n){
	if(n<2){
		return cnt[n];
	}
	n--;
	return (n/loop)*a[as]+bitchop(n%loop)+cnt[1];
}
inline void work(){
	H::init();
	Vector ini=(Vector){ni,ni};
	bstep.a[0][0]=ni;
	bstep.a[0][1]=ni;
	bstep.a[0][2]=ni;
	MOD=ni;
	int C=ni,Q=ni;
	cnt[0]=0,cnt[1]=ini.a[0]==C;
	for(rtP=0;rtP*rtP<MOD;rtP++);
	gstep=bstep,gstep^=rtP;
	Vector cur=ini;
	for(int i=0,tn=MOD*MOD;i<tn&&H::ins(cur.hash(),i);cur=gstep*cur,i+=rtP);
	loop=INF,cur=ini;
	for(int i=1;cur=bstep*cur,i<rtP;i++){
		int val=H::eval(cur.hash());
		if(~val){
			apmin(loop,val-i);
		}
	}
	as=0;
	for(int i=0;i<MOD;i++){
		int val=bsgs((Vector){C,i});
		if(~val){
			a[++as]=val%loop;
		}
	}
	a[0]=0,a[as+1]=loop,sort(a+1,a+as+1);
	while(Q--){
		lint l=nl,r=nl;
		printf("%lld\n",calc(r)-calc(l-1));
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("eclipse.in","r",stdin);
	freopen("eclipse.out","w",stdout);
#endif
	memset(&bstep,0,sizeof(Matrix));
	bstep.a[1][0]=bstep.a[2][2]=1;
	for(int tot=ni;tot--;){
		work();
	}
}
