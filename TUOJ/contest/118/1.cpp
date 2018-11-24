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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=50,INF=0x7f7f7f7f;
union State{
	struct{
		short lbx,lby;
		//sum: initial sum
		//Sum: total process time
		short fx,fy;
		//fx=Sumx-sumy
		//fy=Sumy-sumx
	};
	lint hsh;
	inline friend bool operator < (const State &a,const State &b){
		return a.hsh<b.hsh;
	}
};
typedef map<State,lint>mp;
int x[N],y[N],n;
int _x[N],_y[N],_mx[N];
namespace work1{
	mp f,nxtf;
	inline State addx(int i,State s){
		apmax(s.lbx-=x[i],0);
		apmax(s.lby,x[i]-s.fy);
		s.fx+=x[i];
		s.fy+=y[i]-x[i];
		return s;
	}
	inline State addy(int i,State s){
		apmax(s.lbx,y[i]-s.fx);
		apmax(s.lby-=y[i],0);
		s.fx+=x[i]-y[i];
		s.fy+=y[i];
		return s;
	}
	namespace pack{
		const int A=22;
		int f[N][A*::N];
		inline void main(){
			f[n+1][0]=0;
			for(int i=n,sum=0;i>=1;i--){
				sum+=x[i];
				for(int j=sum;j>=0;j--){
					int &F=f[i][j]=0;
					if(j<=sum-x[i]){
						apmax(F,f[i+1][j]+y[i]);
					}
					if(j>=x[i]){
						apmax(F,f[i+1][j-x[i]]);
					}
				}
			}
			for(int i=n,sum=0;i>=1;i--){
				sum+=x[i];
				for(int j=sum-1;j>=0;j--){
					apmax(f[i][j],f[i][j+1]);
				}
			}
		}
	}
	inline void psh(int i,const State &s,lint f){
		if(s.lbx>_x[n]-_x[i])return;
		if(pack::f[i+1][s.lbx]<s.lby)return;
		nxtf[s]+=f;
	}
	inline void init(){
		pack::main();
		{
			State ini;
			ini.lbx=ini.lby=0;
			ini.fx=ini.fy=0;
			f[ini]=1;
		}
	}
	inline void main(int i){
		for(mp::iterator it=f.begin(),ti=f.end();it!=ti;++it){
			if(it->second){
				psh(i,addx(i,it->first),it->second);
				psh(i,addy(i,it->first),it->second);
			}
		}
		f=nxtf,nxtf.clear();
	}
}
namespace work2{
	mp f,nxtf;
	inline State addx(int i,State s){
		s.lbx+=x[i];
		s.fx+=x[i];
		s.fy+=y[i]-x[i];
		apmin(s.fy,s.lby-x[i]);
		return s;
	}
	inline State addy(int i,State s){
		s.lby+=y[i];
		s.fy+=y[i];
		s.fx+=x[i]-y[i];
		apmin(s.fx,s.lbx-y[i]);
		return s;
	}
	inline void init(){
		State ini;
		ini.lbx=ini.lby=0;
		ini.fx=ini.fy=0;
		f[ini]=1;
	}
	inline void main(int i){
		for(mp::iterator it=f.begin(),ti=f.end();it!=ti;++it){
			if(it->second){
				nxtf[addx(i,it->first)]+=it->second;
				nxtf[addy(i,it->first)]+=it->second;
			}
		}
		f=nxtf,nxtf.clear();
	}
}
lint ans=0;
namespace mg{
	const int N=300010,B=0;
	State a[N],b[N];
	lint va[N],vb[N];
	inline bool ok(State a,State b){
		return a.lbx<=b.lbx&&a.lby<=b.lby&&a.fx<=b.fx&&a.fy<=b.fy;
	}
	inline void brute(int al,int ar,int bl,int br){
		for(int i=al;i<=ar;i++){
			for(int j=bl;j<=br;j++){
				if(ok(a[i],b[j])){
					ans+=va[i]*vb[j];
				}
			}
		}
	}
	inline void addall(int al,int ar,int bl,int br){
		lint suma=0,sumb=0;
		for(int i=al;i<=ar;i++){
			suma+=va[i];
		}
		for(int i=bl;i<=br;i++){
			sumb+=vb[i];
		}
		ans+=suma*sumb;
	}
	void solve4(int al,int ar,int bl,int br){
		if(ar-al<=B||br-bl<=B)return brute(al,ar,bl,br);
		int mn=INF,mx=-INF;
		for(int i=al;i<=ar;i++){
			apmin(mn,a[i].fy),apmax(mx,a[i].fy);
		}
		const int pdiv=mn+(mx-mn)/2;
		int ai=al,aj=ar,bi=bl,bj=br;
		for(;ai<aj;){
			for(;ai<=aj&&a[ai].fy<=pdiv;ai++);
			for(;ai<=aj&&a[aj].fy>pdiv;aj--);
			if(ai<aj){
				swap(a[ai],a[aj]);
				swap(va[ai],va[aj]);
			}
		}
		for(;bi<bj;){
			for(;bi<=bj&&b[bi].fy<pdiv;bi++);
			for(;bi<=bj&&b[bj].fy>=pdiv;bj--);
			if(bi<bj){
				swap(b[bi],b[bj]);
				swap(vb[bi],vb[bj]);
			}
		}
		if(mn<mx){
			solve4(al,aj,bl,bj);
		}
		solve4(ai,ar,bi,br);
		addall(al,aj,bi,br);
	}
	void solve3(int al,int ar,int bl,int br){
		if(ar-al<=B||br-bl<=B)return brute(al,ar,bl,br);
		int mn=INF,mx=-INF;
		for(int i=al;i<=ar;i++){
			apmin(mn,a[i].fx),apmax(mx,a[i].fx);
		}
		const int pdiv=mn+(mx-mn)/2;
		int ai=al,aj=ar,bi=bl,bj=br;
		for(;ai<aj;){
			for(;ai<=aj&&a[ai].fx<=pdiv;ai++);
			for(;ai<=aj&&a[aj].fx>pdiv;aj--);
			if(ai<aj){
				swap(a[ai],a[aj]);
				swap(va[ai],va[aj]);
			}
		}
		for(;bi<bj;){
			for(;bi<=bj&&b[bi].fx<pdiv;bi++);
			for(;bi<=bj&&b[bj].fx>=pdiv;bj--);
			if(bi<bj){
				swap(b[bi],b[bj]);
				swap(vb[bi],vb[bj]);
			}
		}
		if(mn<mx){
			solve3(al,aj,bl,bj);
		}
		solve3(ai,ar,bi,br);
		solve4(al,aj,bi,br);
	}
	void solve2(int al,int ar,int bl,int br){
		if(ar-al<=B||br-bl<=B)return brute(al,ar,bl,br);
		int mn=INF,mx=-INF;
		for(int i=al;i<=ar;i++){
			apmin(mn,a[i].lby),apmax(mx,a[i].lby);
		}
		const int pdiv=mn+(mx-mn)/2;
		int ai=al,aj=ar,bi=bl,bj=br;
		for(;ai<aj;){
			for(;ai<=aj&&a[ai].lby<=pdiv;ai++);
			for(;ai<=aj&&a[aj].lby>pdiv;aj--);
			if(ai<aj){
				swap(a[ai],a[aj]);
				swap(va[ai],va[aj]);
			}
		}
		for(;bi<bj;){
			for(;bi<=bj&&b[bi].lby<pdiv;bi++);
			for(;bi<=bj&&b[bj].lby>=pdiv;bj--);
			if(bi<bj){
				swap(b[bi],b[bj]);
				swap(vb[bi],vb[bj]);
			}
		}
		if(mn<mx){
			solve2(al,aj,bl,bj);
		}
		solve2(ai,ar,bi,br);
		solve3(al,aj,bi,br);
	}
	void solve1(int al,int ar,int bl,int br){
		if(ar-al<=B||br-bl<=B)return brute(al,ar,bl,br);
		int mn=INF,mx=-INF;
		for(int i=al;i<=ar;i++){
			apmin(mn,a[i].lbx),apmax(mx,a[i].lbx);
		}
		const int pdiv=mn+(mx-mn)/2;
		int ai=al,aj=ar,bi=bl,bj=br;
		for(;ai<aj;){
			for(;ai<=aj&&a[ai].lbx<=pdiv;ai++);
			for(;ai<=aj&&a[aj].lbx>pdiv;aj--);
			if(ai<aj){
				swap(a[ai],a[aj]);
				swap(va[ai],va[aj]);
			}
		}
		for(;bi<bj;){
			for(;bi<=bj&&b[bi].lbx<pdiv;bi++);
			for(;bi<=bj&&b[bj].lbx>=pdiv;bj--);
			if(bi<bj){
				swap(b[bi],b[bj]);
				swap(vb[bi],vb[bj]);
			}
		}
		if(mn<mx){
			solve1(al,aj,bl,bj);
		}
		solve1(ai,ar,bi,br);
		solve2(al,aj,bi,br);
	}
	inline void main(){
		int as=0,bs=0;
		for(mp::iterator it=work1::f.begin(),ti=work1::f.end();it!=ti;++it){
			if(it->second){
				++as;
				a[as]=it->first;
				va[as]=it->second;
				a[as].fx*=-1;
				a[as].fy*=-1;
			}
		}
		for(mp::iterator it=work2::f.begin(),ti=work2::f.end();it!=ti;++it){
			if(it->second){
				++bs;
				b[bs]=it->first;
				vb[bs]=it->second;
			}
		}
		solve1(1,as,1,bs);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	n=ni;
	_x[0]=_y[0]=_mx[0]=0;
	for(int i=1;i<=n;i++){
		x[i]=ni,_x[i]=_x[i-1]+x[i];
	}
	for(int i=1;i<=n;i++){
		y[i]=ni,_y[i]=_y[i-1]+y[i];
	}
	for(int i=1;i<=n;i++){
		_mx[i]=_mx[i-1]+max(x[i],y[i]);
	}
	work1::init();
	work2::init();
	for(int i=1,j=n;i<=j;){
		if(work1::f.size()<=work2::f.size()){
			work1::main(i++);
		}else{
			work2::main(j--);
		}
	}
	mg::main();
	printf("%lld\n",ans);
	return 0;
}
