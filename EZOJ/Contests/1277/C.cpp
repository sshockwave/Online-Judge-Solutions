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
int res[L*2],k,pcnt[L];
char tmp[L*2];
inline void count_palin(int n){
	memset(pcnt+1,0,n<<2);
	for(int i=1;i<=n;i++){
		for(int j=(i<<1)-1,top=min(j+k-1,n<<1);j<=top;j++){
			if(j-res[j]<(i<<1)-1){
				pcnt[i]++;
			}
		}
	}
}
inline void manacher(char *s,int n){
	memset(res,0,sizeof(res));
	for(int i=0;i<n;i++){
		tmp[i<<1]='*';
		tmp[(i<<1)|1]=s[i];
	}
	tmp[n<<1]='*';
	for(int i=1,top=n<<1,p=0;i<=top;i++){
		if(p+res[p]>=i){
			res[i]=min(res[p*2-i],min(p+res[p]-i,i-p));
		}
		for(;i>=res[i]&&i+res[i]<=top&&tmp[i-res[i]]==tmp[i+res[i]];res[i]++);
		res[i]--;
		if(i+res[i]>p+res[p]){
			p=i;
		}
	}
	count_palin(n);
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
		return (*(i<=mid?lson:rson))[i];
	}
	void cover(int l,int r,char val){
		assert(lend<=l&&r<=rend);
		if(l==lend&&r==rend){
			c=val;
			return;
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
	seg.build(1,totlen);
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
			for(int i=max(l-k+1,1),top=min(totlen,l+k-2);i<=top;i++){
				cur[ctop++]=seg[i];
			}
			manacher(cur,ctop);
			for(int i=max(l-k+1,1),j=1;i<l;i++,j++){
				seg.alter(i,pcnt[j]);
			}
			ctop=0;
			for(int i=max(r-k+2,1),top=min(totlen,r+k-1);i<=top;i++){
				cur[ctop++]=seg[i];
			}
			manacher(cur,ctop);
			for(int i=max(r-k+2,1),j=1;i<=r;i++,j++){
				seg.alter(i,pcnt[j]);
			}
		}else{
			l=ni(),r=ni();
			int div=r-k+1,ans=0,ctop=0;
			if(l<=div){
				ans+=seg.query(l,div);
			}else{
				div=l-1;
			}
			for(int i=div+1;i<=r;i++){
				cur[ctop++]=seg[i];
			}
			manacher(cur,ctop);
			for(int i=1;i<=ctop;i++){
				ans+=pcnt[i];
			}
			printf("%d\n",ans);
		}
	}
}
