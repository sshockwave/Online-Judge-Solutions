#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef double db;
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=9;
inline db dfpow(db x,lint n){
	db a=1;
	for(;n;n>>=1,x*=x){
		if(n&1){
			a*=x;
		}
	}
	return a;
}
struct sint{
	int s;
	sint(int _s):s(_s){}
	inline int operator [] (int i)const{
		return (s>>(i<<1))&3;
	}
	inline int at(int i)const{
		return operator[](i);
	}
	inline sint set(int i,int v)const{
		i<<=1;
		return sint(s^((((s>>i)&3)^v)<<i));
	}
	inline int match(int i)const{
		int cnt=0;
		if(at(i)==1){
			for(;(at(i)==1?++cnt:at(i)==2?--cnt:0),cnt;i++);
		}else if(at(i)==2){
			for(;(at(i)==1?++cnt:at(i)==2?--cnt:0),cnt;i--);
		}else assert(false);
		return i;
	}
	inline sint redu(const int i)const{
		int j=i;
		int cnt=0;
		if(at(i)==0)return *this;
		else if(at(i)==1){
			for(;(at(j)==1?++cnt:at(j)==2?--cnt:0),!(cnt==0||(cnt==1&&at(j)==3));j++);
		}else if(at(i)==2){
			for(;(at(j)==1?--cnt:at(j)==2?++cnt:0),!(cnt==0||(cnt==1&&at(j)==3));j--);
		}else if(at(i)==3)return set(i,0);
		else assert(false);
		return set(i,0).set(j,at(j)==3?at(i):0);
	}
	inline friend ostream& operator << (ostream& out,const sint &b){
		out<<"[";
		for(int i=0;i<3;i++){
			out<<b[i];
			if(i<2){
				out<<",";
			}
		}
		out<<"]";
		return out;
	}
};
db f[1<<(N<<1)],nf[1<<(N<<1)];
db p_con,p_cut;
inline void dp1(const sint s,const int i,const db p){//up is gone
	assert(s[i]==0);
	if(i){//has left
		const int l=s[i-1];
		if(l==0){
			nf[s.set(i-1,1).set(i,2).s]+=p*p_con;
		}else if(l==1||l==3){
			nf[s.set(i,3).s]+=p*p_con;
		}else if(l==2){
			nf[s.set(i-1,3).set(i,2).s]+=p*p_con;
		}else assert(false);
	}else{
		nf[s.s]+=p*p_con;
	}
	//no left
	nf[s.s]+=p*p_cut;
}
inline void dp2(const sint s,const int i,const db p){//has up
	if(i){
		const int l=s[i-1],r=s[i];
		if(l==0||r==0){
			const int v=l|r;
			if(v==0)nf[s.set(i-1,1).set(i,2).s]+=p*p_con;
			else if(v==1)nf[s.set(i-1,1).set(i,3).s]+=p*p_con;
			else if(v==2)nf[s.set(i-1,3).set(i,2).s]+=p*p_con;
			else if(v==3)nf[s.set(i-1,3).set(i,3).s]+=p*p_con;
			else assert(false);
		}else if(l==1){
			if(r==1)nf[s.set(s.match(i),3).set(i,3).s]+=p*p_con;
			else nf[s.s]+=p*p_con;
		}else if(l==2){
			if(r==1)nf[s.set(i-1,3).set(i,3).s]+=p*p_con;
			else if(r==2)nf[s.set(s.match(i-1),3).set(i-1,3).s]+=p*p_con;
			else if(r==3)nf[s.set(s.match(i-1),3).set(i-1,3).s]+=p*p_con;
			else assert(false);
		}else if(l==3){
			if(r==1)nf[s.set(s.match(i),3).set(i,3).s]+=p*p_con;
			else nf[s.s]+=p*p_con;
		}else assert(false);
	}else{
		nf[s.s]+=p*p_con;
	}
	//no left
	nf[s.s]+=p*p_cut;
}
inline void dp(const sint s,const int i,const db p){
	dp1(s.redu(i),i,p*p_cut);
	dp2(s,i,p*p_con);
}
int *stlst[N+1],stcnt[N+1];
inline db calc_ans(int n){
	db ans=0;
	for(int k=0;k<stcnt[n];k++){
		const sint s=stlst[n][k];
		if(s[n-1]==3){
			ans+=f[s.s];
		}
	}
	return ans;
}
inline db Main(){
	const int n=ni;
	const lint m=next_num<lint>();
	scanf("%lf",&p_cut),p_con=1-p_cut;
	for(int i=0;i<stcnt[n];i++){
		const int s=stlst[n][i];
		f[s]=0;
	}
	const int breakp=30;
	db ans1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<stcnt[n];k++){
				const int s=stlst[n][k];
				nf[s]=0;
			}
			if(i==1&&j==0){
				const static sint s(0);
				nf[sint(0).set(0,3).s]=1;
			}else for(int k=0;k<stcnt[n];k++){
				const int s=stlst[n][k];
				if(f[s]){
					dp(sint(s),j,f[s]);
				}
			}
			for(int k=0;k<stcnt[n];k++){
				const int s=stlst[n][k];
				f[s]=nf[s];
			}
		}
		if(i==breakp){
			ans1=calc_ans(n);
		}else if(i==breakp+1){
			db c=calc_ans(n)/ans1;
			return ans1*dfpow(c,m-breakp);
		}
	}
	return calc_ans(n);
}
inline bool teststate(const int n,const sint s){
	int ss=0;
	int cnt1=0;
	for(int i=0;i<n;i++){
		const int c=s[i];
		if(c==1){
			++ss;
		}else if(c==2){
			if(ss==0)return false;
			--ss;
		}else if(c==3){
			cnt1+=ss==0;
		}else assert(c==0);
	}
	return ss==0&&cnt1;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("socialman.in","r",stdin);
	freopen("socialman.out","w",stdout);
#endif
	for(int n=1;n<=8;n++){
		int sn=1<<(n<<1);
		stcnt[n]=0;
		for(int i=0;i<sn;i++){
			if(teststate(n,sint(i))){
				++stcnt[n];
			}
		}
		stlst[n]=new int[stcnt[n]]+stcnt[n];
		for(int i=0;i<sn;i++){
			if(teststate(n,sint(i))){
				*--stlst[n]=i;
			}
		}
	}
	for(int tot=ni;tot--;printf("%.10lf\n",Main()));
	return 0;
}
