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
struct bint{
	const static int MOD=1000000000;
	int d[130],ds;
	bint(){
		memset(d,0,sizeof(d));
	}
	inline void operator += (bint &b){
		if(b.ds>ds){
			ds=b.ds;
		}
		for(int i=0;i<ds;i++){
			d[i]+=b.d[i];
			d[i+1]+=d[i]/MOD;
			d[i]%=MOD;
		}
		for(;d[ds];ds++){
			d[ds+1]=d[ds]/MOD;
			d[ds]%=MOD;
		}
	}
	inline void print(){
		if(ds==0){
			puts("0");
		}else{
			printf("%d",d[ds-1]);
			for(int i=ds-2;i>=0;i--){
				printf("%09d",d[i]);
			}
			putchar('\n');
		}
	}
}ZERO,ONE;
struct HTable{
	const static int E=6561,MOD=2017;
	int to[E],bro[E],head[MOD],e;
	bint val[E];
	inline void init(){
		memset(head,-1,sizeof(head));
		e=0;
	}
	inline bint& getval(int t){
		int x=t%MOD;
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]==t){
				return val[i];
			}
		}
		return ZERO;
	}
	inline void push(int t,bint &v){
		int x=t%MOD;
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]==t){
				val[i]+=v;
				return;
			}
		}
		to[e]=t,bro[e]=head[x],val[e]=v,head[x]=e++;
	}
}*cur=new HTable,*nxt=new HTable;
int n;
int stat[9];
inline void psh(bint& cnt){
	int hash=0;
	for(int i=n;i>=0;i--){
		hash=(hash<<2)|stat[i];
	}
	nxt->push(hash,cnt);
}
inline void trans(int x,int state,bint& f){
	static int stk[9],mch[9],ss=0;
	int cnt=n+1;
	for(int i=0;i<=n;i++){
		stat[i]=(state>>(i<<1))&3;
		if(stat[i]==1){//(
			stk[ss++]=i;
		}else if(stat[i]==2){//)
			assert(ss);
			mch[mch[i]=stk[--ss]]=i;
		}else{
			cnt--;
		}
	}
	assert(ss==0);
	int l=stat[x-1],r=stat[x];
	if(l==0&&r==0){//__
		if(cnt){
			psh(f);
		}
		stat[x-1]=1,stat[x]=2,psh(f);
	}else if(l==0||r==0){//_( _) (_ _(
		int k=l|r;
		stat[x-1]=k,stat[x]=0,psh(f);
		stat[x-1]=0,stat[x]=k,psh(f);
	}else if(l==2&&r==1){//)(
		stat[x-1]=0,stat[x]=0,psh(f);
	}else if(l!=r){//()
		assert(cnt>=2);
		if(cnt==2){
			nxt->push(0,f);
		}
	}else{
		assert(l==r);
		stat[x-1]=stat[x]=0;
		if(l==1){//((
			assert(stat[mch[x]]==2);
			stat[mch[x]]=1,psh(f);
		}else{//))
			assert(stat[mch[x-1]]==1);
			stat[mch[x-1]]=2,psh(f);
		}
	}
}
bint ans;
inline void work(){
	for(int pos=1;pos<=n;pos++){
		nxt->init();
		trans(pos,0,ONE);
		for(int x=0;x<HTable::MOD;x++){
			for(int i=cur->head[x];~i;i=cur->bro[i]){
				if(cur->to[i]){
					trans(pos,cur->to[i],cur->val[i]);
				}
			}
		}
		swap(cur,nxt);
		ans+=cur->getval(0);
	}
	nxt->init();
	int bits=3<<(n<<1);
	for(int x=0;x<HTable::MOD;x++){
		for(int i=cur->head[x];~i;i=cur->bro[i]){
			if((cur->to[i]&bits)==0){
				nxt->push(cur->to[i]<<2,cur->val[i]);
			}
		}
	}
	swap(nxt,cur);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
#endif
	ONE.ds=1,ONE.d[0]=1;
	int tot=ni;
	n=ni;
	if(n>tot){
		swap(n,tot);
	}
	cur->init();
	for(;tot--;work());
	ans.print();
	return 0;
}
