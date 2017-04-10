#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline bool is_letter(char c){
	return c>='a'&&c<='z';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int L=50010,K=55;
int res[L*2];
inline void manacher(char *s,int n){
	
}
struct SegmentTree{
	typedef SegmentTree node;
	int lend,rend,mid,sum,delta;
	char c;
	node *lson,*rson;
	void build(int,int);
	inline void push_up(){
		sum=lson->sum+rson->sum;
	}
	char operator [] (int i){
		assert(lend<=i&&i<=rend);
		if(c){
			return c;
		}
		if(i<=mid){
			return (*lson)[i];
		}else{
			return (*rson)[i];
		}
	}
	void cover(int l,int r,char val){
		assert(lend<=l&&r<=rend);
		if(l==lend&&r==rend){
			c=val;
		}
		if(c){
			lson->c=rson->c=c;
			c=0;
		}
		if(r<=mid){
			lson->cover(l,r,val);
		}else if(l>mid){
			rson->cover(l,r,val);
		}else{
			lson->cover(l,mid,val);
			rson->cover(mid+1,r,val);
		}
	}
	void cover(int l,int r,int val){
		assert(lend<=l&&r<=rend);
		if(l==lend&&r==rend){
			delta=val;
			sum=val*(r-l+1);
			return;
		}
		if(delta){
			lson->delta=rson->delta=delta;
			lson->sum=delta*(mid-l+1);
			rson->sum=delta*(r-mid);
			delta=0;
		}
		if(r<=mid){
			lson->cover(l,r,val);
		}else if(l>mid){
			rson->cover(l,r,val);
		}else{
			lson->cover(l,mid,val);
			rson->cover(mid+1,r,val);
		}
		push_up();
	}
	void alter(int x,int v){
		if(lend==rend){
			assert(lend==x);
			sum=v;
		}else{
			(x<=mid?lson:rson)->alter(x,v);
			push_up();
		}
	}
	int query(int l,int r){
		assert(lend<=l&&r<=rend);
		if(delta){
			return delta*(r-l+1);
		}
		if(l==lend&&r==rend){
			return sum;
		}
		if(r<=mid){
			return lson->query(l,r);
		}
		if(l>mid){
			return rson->query(l,r);
		}
		return lson->query(l,mid)+rson->query(mid+1,r);
	}
}seg,pool[L*2];
char s[L],cur[L];
int pcnt[L];
void SegmentTree::build(int l,int r){
	static node* n=pool;
	lend=l,rend=r,mid=(l+r)>>1;
	delta=0;
	if(l==r){
		c=s[l],sum=pcnt[l];
	}else{
		(lson=n++)->build(l,mid);
		(rson=n++)->build(mid+1,r);
		c=0,sum=lson->sum+rson->sum;
	}
}
int main(){
	scanf("%s%d",s+1,&k);
	int totlen=strlen(s+1);
	manacher(s+1,totlen);
	memset(pcnt,0,sizeof(pcnt));
	for(int i=1;i<=n;i++){
		for(int j=(i<<1)-1,top=k+j;j<=top;j++){
			if(i+res[j]>=j){
				pcnt[i]++;
			}
		}
	}
	for(int tot=ni(),l,r;tot--;){
		if(ni()==1){
			l=ni(),r=ni();
			char c;
			while(!is_letter(c=getchar()));
			seg.cover(l,r,c);
			int div=r-k+1,ctop=0;
			if(l<=div){
				seg.cover(l,div,k);
			}
			for(int i=max(l-k+1,0),top=min(totlen,l+k-1);i<=top;i++){
				cur[ctop++]=seg[i];
			}
			manacher(cur,ctop);
			for(int from=max(l-k+1,0),i=from;i<=l;i++){
				int val=0;
				for(int st=((i-from)<<1)|1,j=st,top=min(k+j,ctop<<1);j<=top;j++){
					if(st+res[j]>=j){
						val++;
					}
				}
				seg.alter(i,val);
			}
			ctop=0;
			for(int i=max(r-k+1,0),top=min(totlen,r+k-1);i<=top;i++){
				cur[ctop++]=seg[i];
			}
			manacher(cur,ctop);
			for(int from=max(r-k+1,0),i=from;i<=r;i++){
				int val=0;
				for(int st=((i-from)<<1)|1,j=st,top=min(k+j,ctop<<1);j<=top;j++){
					if(st+res[j]>=j){
						val++;
					}
				}
				seg.alter(i,val);
			}
		}else{
			l=ni(),r=ni();
			int div=r-k+1,ans=0,ctop=0;
			if(l<=div){
				ans+=seg.query(l,div);
			}
			for(int i=div+1;i<=r;i++){
				cur[ctop++]=seg[i];
			}
			manacher(cur,ctop);
			for(int i=0,top=ctop<<1;i<=top;i++){
				ans+=res[i];
			}
			printf("%d\n",ans);
		}
	}
}
