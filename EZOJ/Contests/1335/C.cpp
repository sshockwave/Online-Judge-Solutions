#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=300010,D=26;
char s[N];
int _sum[N][D];
namespace sam{
	struct Node;
	typedef Node* node;
	struct Node{
		node lnk,go[D];
		int len,end,son;
	}pol[N<<1],*pool=pol,*ini=pool++,*tail=ini;
	inline void init(){
		memset(pol,0,sizeof(pol));
	}
	inline void ext(int i,int c){
		node p=tail;
		node np=tail=pool++;
		np->len=p->len+1;
		np->end=i;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=np;
		}
		if(p==0){
			np->lnk=ini;
			return;
		}
		node q=p->go[c];
		if(q->len==p->len+1){
			np->lnk=q;
			return;
		}
		node nq=pool++;
		*nq=*q;
		np->end=i;
		nq->len=p->len+1;
		nq->lnk=q->lnk;
		q->lnk=np->lnk=nq;
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
	}
	inline lint work(){
		for(node i=pol+1;i<pool;i++){
			i->lnk->son|=1<<(s[i->end-i->lnk->len]-'a');
		}
		lint ans=0;
		for(node i=pol;i<pool;i++){
			for(int c=0;c<D;c++){
				if(i->go[c]){
					if((i->son>>c)&1){
						ans++;
					}
					if(i!=ini){
						ans+=_sum[i->end-i->lnk->len-1][c]-_sum[i->end-i->len][c];
					}
				}
			}
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("loop.in","r",stdin);
	freopen("loop.out","w",stdout);
#endif
	scanf("%s",s+1);
	sam::init();
	memset(_sum[0],0,sizeof(_sum[0]));
	for(int i=1;s[i];i++){
		sam::ext(i,s[i]-'a');
		memcpy(_sum[i],_sum[i-1],sizeof(_sum[i]));
		_sum[i][s[i]-'a']++;
	}
	printf("%lld\n",sam::work());
	return 0;
}
