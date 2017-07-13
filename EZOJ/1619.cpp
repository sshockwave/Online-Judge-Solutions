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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010,D=26;
struct SAM{
	typedef SAM* node;
	static SAM pol[N<<1],*pool,ini;
	node lnk,go[D];
	int val;
	static inline void init(){
		memset(pol,0,sizeof(pol));
	}
	inline node ext(int c){
		node p=this,np=pool++;
		np->val=val+1;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=np;
		}
		if(p==0){
			np->lnk=&ini;
			return np;
		}
		node q=p->go[c];
		if(q->val==p->val+1){
			np->lnk=q;
			return np;
		}
		assert(q->val>p->val+1);
		node nq=pool++;
		*nq=*q;
		nq->val=p->val+1;
		q->lnk=np->lnk=nq;
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		return np;
	}
};
SAM SAM::pol[N<<1],*SAM::pool=SAM::pol,SAM::ini;
namespace T{
	int son[N][D],n=1;
	inline void init(){
		memset(son,0,sizeof(son));
	}
	inline void ins(char s[]){
		int x=1;
		for(;*s;x=son[x][(*s++)-'a']){
			if(son[x][(*s)-'a']==0){
				son[x][(*s)-'a']=++n;
			}
		}
	}
	void dfs(int x,SAM* p){
		for(int i=0;i<D;i++){
			if(son[x][i]){
				dfs(son[x][i],p->ext(i));
			}
		}
	}
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("substring.in","r",stdin);
	freopen("substring.out","w",stdout);
#endif
	T::init(),SAM::init(),memset(&SAM::ini,0,sizeof(SAM));
	for(int tot=ni;tot--;){
		scanf("%s",s);
		T::ins(s);
	}
	T::dfs(1,&SAM::ini);
	int ans=0;
	for(SAM* i=SAM::pol;i<SAM::pool;i++){
		ans+=i->val-i->lnk->val;
	}
	printf("%d\n",ans);
}
