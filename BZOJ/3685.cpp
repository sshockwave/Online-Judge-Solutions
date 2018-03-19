#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
struct vEBproto{
	unsigned mn,mx;
	vEBproto():mn(-1u),mx(-1u){}
};
template<unsigned w>struct vEB;
template<>struct vEB<1>:vEBproto{
	inline unsigned pred(unsigned x){
		return x>=mx?mx:x>=mn?mn:-1;
	}
	inline unsigned succ(unsigned x){
		return x<=mn?mn:x<=mx?mx:-1;
	}
	inline void ins(unsigned x){
		if(mx==-1u){
			mn=mx=x;
		}else if(x!=mn){
			mn=0,mx=1;
		}
	}
	inline void del(unsigned x){
		mn=mx=mn==mx?-1u:!x;
	}
	void dfs(unsigned t){
		if(mn==-1u)return;
		cout<<(t|mn)<<" ";
		if(mn!=mx){
			cout<<(t|mx)<<" ";
		}
	}
};
template<unsigned w>struct vEB:vEBproto{//n==(1<<w)
	const static int flo=w>>1,cel=w-flo;
	vEB<flo>summary;
	vEB<cel>cluster[1<<flo];
	inline unsigned pred(unsigned x){
		if(x<0||x<mn)return -1u;
		if(x>=mx)return mx;
		const unsigned hi=x>>cel,lo=x^(hi<<cel);
		if(lo>=cluster[hi].mn)return (hi<<cel)|cluster[hi].pred(lo);
		unsigned p=summary.pred(hi-1);
		return p!=-1u?(hi<<cel)|cluster[p].mn:mn;
	}
	inline unsigned succ(unsigned x){
		if(x>mx)return -1u;
		if(x<=mn)return mn;
		const unsigned hi=x>>cel,lo=x^(hi<<cel);
		if(cluster[hi].mx!=-1u&&lo<=cluster[hi].mx)return (hi<<cel)|cluster[hi].succ(lo);
		return (hi<<cel)|cluster[summary.succ(hi+1)].mn;
	}
	inline void ins(unsigned x){
		if(mx==-1u)return mn=mx=x,void();
		if(x<mn){
			swap(x,mn);
		}else if(x>mx){
			mx=x;
		}
		const unsigned hi=x>>cel,lo=x^(hi<<cel);
		if(cluster[hi].mx==-1u){
			summary.ins(hi);
		}
		cluster[hi].ins(lo);
	}
	inline void del(unsigned x){
		assert(mx!=-1u);
		if(mn==mx){
			assert(x==mn);
			mn=mx=-1u;
			return;
		}
		if(x==mn){
			x=mn=(summary.mn<<cel)|cluster[summary.mn].mn;
		}
		const unsigned hi=x>>cel,lo=x^(hi<<cel);
		cluster[hi].del(lo);
		if(cluster[hi].mx==-1u){
			summary.del(hi);
		}
		if(x==mx){
			mx=summary.mx!=-1u?(summary.mx<<cel)|cluster[summary.mx].mx:mn;
		}
	}
	void dfs(unsigned t){
		if(mn==-1u)return;
		cout<<(mn|t)<<" ";
		for(int i=0;i<(1<<(w>>1));i++){
			cluster[i].dfs(t|(i<<(w-(w>>1))));
		}
	}
};
const int SH=20,N=1<<SH;
vEB<SH>T;
inline void putnum(unsigned x){
	if(x==-1u){
		puts("-1");
	}else{
		printf("%d\n",x);
	}
}
bool liv[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("van.in","r",stdin);
	freopen("van.out","w",stdout);
#endif
	memset(liv,0,sizeof(liv));
	ni;
	unsigned x;
	for(int tot=ni;tot--;){
		switch(ni){
			case 1:
				x=ni;
				if(!liv[x]){
					liv[x]=true;
					T.ins(x);
				}
				break;
			case 2:
				x=ni;
				if(liv[x]){
					T.del(x);
					liv[x]=false;
				}
				break;
			case 3:
				putnum(T.mn);
				break;
			case 4:
				putnum(T.mx);
				break;
			case 5:
				putnum(T.pred(ni-1));
				break;
			case 6:
				putnum(T.succ(ni+1));
				break;
			case 7:
				putnum(liv[ni]?1u:-1u);
				break;
		}
	}
	return 0;
}
