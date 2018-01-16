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
const int N=1000010,D=100;
namespace PAM{
	int fail[N],len[N],nxt[N][D];
	inline int nn(){
		static int n=1;
		return ++n;
	}
	inline void init(){
		fail[0]=1;
		len[1]=-1;
	}
}
char str[N<<1];
struct state{
	int l,r;
	int lnode,rnode;
	int ans;
	inline state ins_left(char c)const{
		str[l-1]=c;
		int p=lnode;
		using namespace PAM;
		for(;l+len[p]>r||str[l+len[p]]!=c;p=fail[p]);
		if(nxt[p][c]==0){
			int q=fail[p];
			for(;l+len[q]>r||str[l+len[q]]!=c;q=fail[q]);
			q=nxt[q][c];
			nxt[p][c]=nn();
			fail[nxt[p][c]]=q;
			len[nxt[p][c]]=len[p]+2;
		}
		p=nxt[p][c];
		int q=rnode;
		if(len[p]==r-l+2){
			q=p;
		}
		return (state){l-1,r,p,q,max(ans,len[p])};
	}
	inline state ins_right(char c)const{
		str[r+1]=c;
		int p=rnode;
		using namespace PAM;
		for(;r-len[p]<l||str[r-len[p]]!=c;p=fail[p]);
		if(nxt[p][c]==0){
			int q=fail[p];
			for(;r-len[q]<l||str[r-len[q]]!=c;q=fail[q]);
			q=nxt[q][c];
			nxt[p][c]=nn();
			fail[nxt[p][c]]=q;
			len[nxt[p][c]]=len[p]+2;
		}
		p=nxt[p][c];
		int q=lnode;
		if(len[p]==r-l+2){
			q=p;
		}
		return (state){l,r+1,q,p,max(ans,len[p])};
	}
}stk[N];
int ss=0;
char s[N*3];
int main(){
#ifndef ONLINE_JUDGE
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
#endif
	int tot=ni;
	fread(s,1,N*3,stdin);
	s[tot*3]=0;
	stk[ss]=(state){N,N-1,0,0,0}; PAM::init();
	lint ans=0;
	for(int i=0,j=0;i<tot;i++,j+=3){
		int op=s[j]-'0';
		int num=((s[j+1]-'0')*10+(s[j+2]-'0')+stk[ss].ans)%100;
		if(op==1){
			stk[ss+1]=stk[ss].ins_left(num);
			ss++;
		}else if(op==2){
			stk[ss+1]=stk[ss].ins_right(num);
			ss++;
		}else{
			ss-=num;
		}
		ans+=stk[ss].ans;
	}
	printf("%lld\n",ans);
	return 0;
}
