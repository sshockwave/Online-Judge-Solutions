#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
struct vEBproto{
	unsigned mn,mx;
	vEBproto():mn(-1u),mx(-1u){}
};
template<unsigned w>struct vEB;
template<>struct vEB<1>:vEBproto{
	inline unsigned pred(unsigned x){
		return x==-1u?-1u:x>=mx?mx:x>=mn?mn:-1u;
	}
	inline unsigned succ(unsigned x){
		return x==-1u?-1u:x<=mn?mn:x<=mx?mx:-1u;
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
};
template<unsigned w>struct vEB:vEBproto{
	const static int flo=w>>1,cel=w-flo;
	vEB<flo>summary;
	vEB<cel>cluster[1<<flo];
	inline unsigned pred(unsigned x){
		if(x==-1u||x<mn)return -1u;
		if(x>=mx)return mx;
		const unsigned hi=x>>cel,lo=x^(hi<<cel);
		if(lo>=cluster[hi].mn)return (hi<<cel)|cluster[hi].pred(lo);
		unsigned p=summary.pred(hi-1);
		return p!=-1u?(p<<cel)|cluster[p].mx:mn;
	}
	inline unsigned succ(unsigned x){
		if(x>mx)return -1u;
		if(x<=mn)return mn;
		const unsigned hi=x>>cel,lo=x^(hi<<cel);
		if(cluster[hi].mx!=-1u&&lo<=cluster[hi].mx)return (hi<<cel)|cluster[hi].succ(lo);
		int p=summary.succ(hi+1);
		return (p<<cel)|cluster[p].mn;
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
		if(mn==mx){
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
};
const int SH=20,N=1<<SH;
vEB<SH>T;
namespace IO{
	const int N=30000010;
	char s[N],*t=s;
	char buf[N],*bufp=buf;
	inline void init(){
		fread(s,1,N,stdin);
	}
	inline unsigned ni(){
		unsigned i=0;
		for(;!isdigit(*t);t++);
		while(i=i*10-'0'+*t,isdigit(*++t));
		return i;
	}
	void putnum(unsigned x){
		if(x){
			int t=x/10;
			putnum(t),*(bufp++)=x-t*10+'0';
		}
	}
	inline void put(unsigned x){
		if(x==-1u){
			*(bufp++)='-',*(bufp++)='1';
		}else if(x==0){
			*(bufp++)='0';
		}else{
			putnum(x);
		}
		*(bufp++)='\n';
	}
	inline void flush(){
		fwrite(buf,1,bufp-buf,stdout);
	}
}
bool liv[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("van.in","r",stdin);
	freopen("van.out","w",stdout);
#endif
	IO::init();
	IO::ni();
	unsigned x;
	for(int tot=IO::ni();tot--;){
		switch(IO::ni()){
			case 1:
				x=IO::ni();
				if(!liv[x]){
					liv[x]=true;
					T.ins(x);
				}
				break;
			case 2:
				x=IO::ni();
				if(liv[x]){
					T.del(x);
					liv[x]=false;
				}
				break;
			case 3:
				IO::put(T.mn);
				break;
			case 4:
				IO::put(T.mx);
				break;
			case 5:
				IO::put(T.pred(IO::ni()-1));
				break;
			case 6:
				IO::put(T.succ(IO::ni()+1));
				break;
			case 7:
				IO::put(liv[IO::ni()]?1u:-1u);
				break;
		}
	}
	IO::flush();
	return 0;
}
