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
int k;
char s[L];
struct SegmentTree{
	typedef SegmentTree node;
	struct Info{
		char sl[K*2],sr[K*2];
		int lenl[K],lenr[K],intl,top,sum;//[0,ll)[0,lr)
		inline void init(char c){
			intl=1;
			sl[0]=sr[0]=sl[2]=sr[2]='*';
			sl[1]=sr[1]=c;
			lenl[0]=lenr[0]=lenl[2]=lenr[2]=0;
			lenl[1]=lenr[1]=intl=sum=1;
			top=min(k,intl);
		}
		inline void setall(char c){
			if(top==k){
				sum=(intl-k+1)*(k-1)+(k-1)*(k-2)/2;
			}else{
				sum=intl*(intl-1)/2;
			}
			for(int i=0;i<top;i++){
				sl[(i<<1)|1]=sr[(i<<1)|1]=c;
				lenl[i]=lenr[i]=min(i,(intl<<1)-i);
			}
			lenl[top]=lenr[top]=min(top,(intl<<1)-top);
		}
		inline void update(Info l,Info r){
			intl=l.intl+r.intl;
			sum=l.sum+r.sum;
			top=min(k,intl);
			if(l.top==k){
				memcpy(sl,l.sl,(k<<1)|1);
				memcpy(lenl,l.lenl,(k+1)<<2);
			}else{
				memcpy(sl,l.sl,l.top<<1);
				memcpy(sl+(l.top<<1),r.sl,(r.top<<1)|1);
				memcpy(lenl,l.top<<1);
			}
			if(r.top==k){
				memcpy(sr,r.sr,(k<<1)|1);
				memcpy(lenr,r.lenr,(k+1)<<2);
			}else{
				
			}
		}
	}info;
	int lend,rend,mid;
	node *lson,*rson;
	bool flag;
	void build(int,int);
	void cover(int l,int r,char c){
		assert(lend<=l&&r<=rend);
		if(l==lend&&r==rend){
			flag=true;
			info.setall(c);
			return;
		}
		if(r<=mid){
			lson->cover(l,r,c);
		}else if(l>mid){
			rson->cover(l,r,c);
		}else{
			lson->cover(l,mid,c);
			rson->cover(mid+1,r,c);
		}
		info.update(lson->info,rson->info);
	}
	Info ask(int l,int r){
		assert(lend<=l&&r<=rend);
		if(l==lend&&r==rend){
			return info;
		}
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		Info ans;
		ans.update(lson->ask(l,mid),rson->ask(mid+1,r));
		return ans;
	}
}seg,pool[L*2];
void SegmentTree::build(int l,int r){
	static node *n=pool;
	lend=l,rend=r,mid=(l+r)>>1;
	flag=false;
	if(l==r){
		info.init(s[l]);
	}else{
		(lson=n++)->build(l,mid);
		(rson=n++)->build(mid+1,r);
		info.update(lson->info,rson->info);
	}
}
inline bool is_palin(char *s,char *t){
	for(;s<t;s++,t--){
		if((*s)!=(*t)){
			return false;
		}
	}
	return true;
}
inline int query(int l,int r){
	int cnt=0;
	for(int i=l;i<=r;i++){
		for(int j=i,top=min(r,i+k-1);j<=top;j++){
			if(is_palin(s+i,s+j)){
				cnt++;
			}
		}
	}
	return cnt;
}
int main(){
	scanf("%s%d",s+1,&k);
	for(int tot=ni(),l,r;tot--;){
		if(ni()==1){
			l=ni(),r=ni();
			char c;
			while(!is_letter(c=getchar()));
			for(int i=l;i<=r;i++){
				s[i]=c;
			}
		}else{
			l=ni(),r=ni();
			printf("%d\n",query(l,r));
		}
	}
}
