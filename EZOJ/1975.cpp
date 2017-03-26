#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=100010;
const double alpha=0.8;
struct Scapegoat{
	#define lson(x) son[x][0]
	#define rson(x) son[x][1]
	int key[N],son[N][2],size[N],ntop,seq[N],stop,root;
	Scapegoat(){
		memset(son,0,sizeof(son));
		size[0]=root=0;
		ntop=1;
	}
	void dfs(int x){
		if(x){
			seq[stop++]=x;
			dfs(lson(x)),dfs(rson(x));
		}
	}
	int build(int l,int r){
		if(l>r){
			return 0;
		}
		int mid=(l+r)>>1,x=seq[mid];
		lson(x)=build(l,mid-1);
		rson(x)=build(mid+1,r);
		size[x]=size[lson(x)]+size[rson(x)]+1;
		return x;
	}
	inline void balance(int &x){
		if(size[lson(x)]<=size[x]*alpha&&size[rson(x)]<=size[x]*alpha){
			return;
		}
		stop=1;
		dfs(x);
		x=build(1,size[x]);
	}
	void insert(int &x,int k){
		if(x){
			insert(son[x][k>key[x]],k);
			size[x]++;
			balance(x);
		}else{
			x=ntop++;
			key[x]=k;
			size[x]=1;
		}
	}
	int del(int &x,int k){
		if(son[x][k>key[x]]==0||(key[x]==k&&(lson(x)==0||rson(x)==0))){
			int p=x;
			x=lson(x)|rson(x);
			return p;
		}
		size[x]--;
		if(key[x]==k){
			key[x]=key[del(rson(x),k)];
			balance(x);
			return x;
		}else{
			int p=del(son[x][k>key[x]],k);
			balance(x);
			return p;
		}
	}
	int ask_rank(int x,int k,int last){//assert k exists
		if(x==0){
			return last;
		}
		if(k<key[x]){
			return ask_rank(lson(x),k,last);
		}
		if(k>key[x]){
			if(rson(x)==0){
				return last;
			}
			return ask_rank(rson(x),k,last)+size[lson(x)]+1;
		}
		return ask_rank(lson(x),k,size[lson(x)]+1);
	}
	int rank_ele(int x,int r){
		if(r<=size[lson(x)]){
			return rank_ele(lson(x),r);
		}
		r-=size[lson(x)]+1;
		return r?rank_ele(rson(x),r):key[x];
	}
	int prec(int x,int k,int last){
		if(x==0){
			return last;
		}
		if(k>key[x]){
			return prec(rson(x),k,key[x]);
		}
		return prec(lson(x),k,last);
	}
	int succ(int x,int k,int last){
		if(x==0){
			return last;
		}
		if(k<key[x]){
			return succ(lson(x),k,key[x]);
		}
		return succ(rson(x),k,last);
	}
	void print(int x){
		if(x){
			print(lson(x));
			cout<<key[x]<<" ";
			print(rson(x));
		}
	}
}bst;
int main(){
	for(int tot=ni(),opt,x;tot--;){
		scanf("%d%d",&opt,&x);
		switch(opt){
			case 1:{
				bst.insert(bst.root,x);
				break;
			}
			case 2:{
				bst.del(bst.root,x);
				break;
			}
			case 3:{
				printf("%d\n",bst.ask_rank(bst.root,x,-1));
				break;
			}
			case 4:{
				printf("%d\n",bst.rank_ele(bst.root,x));
				break;
			}
			case 5:{
				printf("%d\n",bst.prec(bst.root,x,-1));
				break;
			}
			case 6:{
				printf("%d\n",bst.succ(bst.root,x,-1));
				break;
			}
		}
	}
}
