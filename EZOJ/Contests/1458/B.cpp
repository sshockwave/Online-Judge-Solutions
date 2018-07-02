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
		if(at(i)==1){
			for(;(at(j)==1?++cnt:at(j)==2?--cnt:0),!(cnt==0||(cnt==1&&at(j)==3));j++);
		}else if(at(i)==2){
			for(;(at(j)==1?--cnt:at(j)==2?++cnt:0),!(cnt==0||(cnt==1&&at(j)==3));j--);
		}else assert(false);
		return set(i,0).set(j,at(j)==3?at(i):0);
	}
	inline friend ostream& operator << (ostream& out,const sint &b){
		out<<"[";
		for(int i=0;i<4;i++){
			out<<b[i];
			if(i<3){
				out<<",";
			}
		}
		out<<"]";
		return out;
	}
};
db f[1<<(N<<1)],nf[1<<(N<<1)];
db p_con,p_cut;
inline void dp1(sint s,const int i,const db p){
	const int l=s[i],r=s[i+1];
	int v;
	if(l==0||r==0){
		v=l|r;
	}else if(l==1){
		if(r==1)s=s.set(s.match(i+1),3),v=1;
		else if(r==2)v=0;
		else if(r==3)v=1;
	}else if(l==2){
		if(r==1)v=3;
		else if(r==2)s=s.set(s.match(i),3),v=2;
		else if(r==3)s=s.set(s.match(i),3),v=3;
	}else if(l==3){
		if(r==1)s=s.set(s.match(i+1),3),v=3;
		else if(r==2)v=2;
		else if(r==3)v=3;
	}
	s=s.set(i,v).set(i+1,0);
	if(v==3||v==0){
		nf[s.set(i,0).set(i+1,0).s]+=p*p_cut*p_cut;
	}else if(v==1||v==2){
		nf[s.redu(i).s]+=p*p_cut*p_cut;
	}else assert(false);
	nf[s.set(i,v).set(i+1,0).s]+=p*p_con*p_cut;
	nf[s.set(i,0).set(i+1,v).s]+=p*p_cut*p_con;
	const db np=p*p_con*p_con;
	if(v==0){
		nf[s.set(i,1).set(i+1,2).s]+=np;
	}else if(v==1){
		nf[s.set(i,1).set(i+1,3).s]+=np;
	}else if(v==2){
		nf[s.set(i,3).set(i+1,2).s]+=np;
	}else if(v==3){
		nf[s.set(i,3).set(i+1,3).s]+=np;
	}else assert(false);
}
inline void dp2(sint s,const int i,const db p){
	const int l=s[i],r=s[i+1];
	int v;
	if(l==0||r==0){
		v=l|r;
	}else if(l==1){
		if(r==1)s=s.set(s.match(i+1),3),v=1;
		else if(r==2)v=0;
		else if(r==3)v=1;
	}else if(l==2){
		if(r==1)v=3;
		else if(r==2)s=s.set(s.match(i),3),v=2;
		else if(r==3)s=s.set(s.match(i),3),v=3;
	}else if(l==3){
		if(r==1)s=s.set(s.match(i+1),3),v=3;
		else if(r==2)v=2;
		else if(r==3)v=3;
	}
	s=s.set(i,v).set(i+1,0);
	if(v==3||v==0){
		nf[s.set(i,0).set(i+1,0).s]+=p*p_cut;
	}else if(v==1){
		nf[s.redu(i).s]+=p*p_cut;
	}else assert(false);
	nf[s.set(i,0).set(i+1,v).s]+=p*p_con;
}
int *stlst[N+1],stcnt[N+1];
inline db Main(){
	const int n=ni;
	const lint m=next_num<lint>();
	scanf("%lf",&p_cut),p_con=1-p_cut;
	if(m==1){
		db ans=1;
		for(int i=1;i<n;i++){
			ans*=p_con;
		}
		return ans;
	}
	for(int i=0;i<stcnt[n+1];i++){
		const int s=stlst[n+1][i];
		f[s]=0;
	}
	db ans=0;
	for(int i=1;i<=m;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<stcnt[n+1];k++){
				const int s=stlst[n+1][k];
				nf[s]=0;
			}
			if(i==1&&j==0){
				const static sint s(0);
				nf[s.set(0,3).set(1,0).s]+=p_con*p_cut;
				nf[s.set(0,0).set(1,3).s]+=p_cut*p_con;
				nf[s.set(0,3).set(1,3).s]+=p_con*p_con;
			}else if(i==m&&j==n-1){
				for(int k=0;k<stcnt[n+1];k++){
					const sint s=stlst[n+1][k];
					if(f[s.s]&&(s[n]==3||(s[n]==0&&s[n-1]==3))){
						ans+=f[s.s];
					}
				}
			}else for(int k=0;k<stcnt[n+1];k++){
				const int s=stlst[n+1][k];
				if(f[s]){
					if(i==m){
						dp2(sint(s),j,f[s]);
					}else{
						dp1(sint(s),j,f[s]);
					}
				}
			}
			for(int k=0;k<stcnt[n+1];k++){
				const int s=stlst[n+1][k];
				f[s]=nf[s];
			}
		}
		for(int k=0;k<stcnt[n+1];k++){
			const int s=stlst[n+1][k];
			nf[s]=0;
		}
		for(int k=0;k<stcnt[n+1];k++){
			const int s=stlst[n+1][k];
			const int b=sint(s)[n];
			if(b==0){
				nf[s<<2]+=f[s];
			}else if(b==2){
				nf[sint(s).redu(n).set(n,0).s<<2]+=f[s];
			}else if(b==3){
				nf[sint(s).set(n,0).s<<2]+=f[s];
			}else assert(false);
		}
		db sum=0;
		for(int k=0;k<stcnt[n+1];k++){
			const int s=stlst[n+1][k];
			sum+=f[s]=nf[s];
		}
		if(i<m&&sum<1e-7)return 0;
	}
	return ans;
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
	for(int n=1;n<=9;n++){
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
