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
const int N=500010;
namespace trie{
	struct Node;
	typedef Node* node;
	struct Node{
		union{
			struct{
				node lson,rson;
			};
			node son[2];
		};
		int size;
	}null;
	inline void init(){
		null.lson=null.rson=&null;
		null.size=0;
	}
	inline node nn(node x=&null){
		static node n=new Node[N*20];
		return *n=*x,n++;
	}
	inline node ins(node x,int val,int sh){
		x=nn(x);
		x->size++;
		if(sh<0)return x;
		node &son=x->son[(val>>sh)&1];
		son=ins(son,val,sh-1);
		return x;
	}
	int mxxor(node x,node y,int val,int sh){
		if(sh<0)return 0;
		bool d=(val>>sh)&1;
		if(y->son[!d]->size-x->son[!d]->size){
			return mxxor(x->son[!d],y->son[!d],val,sh-1)|((!d)<<sh);
		}
		return mxxor(x->son[d],y->son[d],val,sh-1)|(d<<sh);
	}
	int cntless(node x,node y,int val,int sh){
		if(sh<0)return y->size-x->size;
		bool d=(val>>sh)&1;
		int ans=cntless(x->son[d],y->son[d],val,sh-1);
		if((val>>sh)&1){
			ans+=y->lson->size-x->lson->size;
		}
		return ans;
	}
	int getkth(node x,node y,int val,int sh){
		if(sh<0)return 0;
		int lsize=y->lson->size-x->lson->size;
		if(lsize>=val)return getkth(x->lson,y->lson,val,sh-1);
		else return getkth(x->rson,y->rson,val-lsize,sh-1)|(1<<sh);
	}
}
trie::node rt[N]={&trie::null};
int main(){
#ifndef ONLINE_JUDGE
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
#endif
	int tot=ni,len=0;
	trie::init();
	while(tot--){
		int l,r;
		switch(ni){
			case 0://add x
				rt[len+1]=trie::ins(rt[len],ni,20);
				len++;
				break;
			case 1://find max [l,r] xor x
				l=ni,r=ni;
				printf("%d\n",trie::mxxor(rt[l-1],rt[r],ni,20));
				break;
			case 2://delete k eles
				len-=ni;
				break;
			case 3://count [l,r] less than x
				l=ni,r=ni;
				printf("%d\n",trie::cntless(rt[l-1],rt[r],ni,20));
				break;
			case 4://find [l,r] kth
				l=ni,r=ni;
				printf("%d\n",trie::getkth(rt[l-1],rt[r],ni,20));
				break;
		}
	}
	return 0;
}
