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
inline int abs(int a){
	return a>0?a:-a;
}
const int K=2,N=100010;
struct kdtree{
	inline void loop(int x){
		if((++x)==K){
			x=0;
		}
	}
	struct node{
		int val[K],d;
		node *son[2];
		inline int & operator [] (int i){
			return val[i];
		}
		node query(node &x){
			if(son[x.val[d]<val[d]]==NULL){
				return *this;
			}
		}
	}pt[N],*root;
	int ntop;
	kdtree(){
		ntop=0;
		root=NULL;
	}
	inline int dist(node a,node b){
		int sum=0;
		for(int i=0;i<K;i++){
			sum+=abs(a[i]-b[i]);
		}
		return sum;
	}
	inline void set(int x,int y){
		pt[ntop]=(node){x,y};
		memset(pt[ntop].son,NULL,sizeof(pt[ntop].son));
	}
	inline void insert(){
		node **x=&root,&cur=pt[ntop++];
		int now=0;
		while((*x)!=NULL){
			x=&((*x)->son[cur->val[now]<(*x)->val[now]]);
			loop(now);
		}
		cur.d=now;
	}
	inline int query(){
		assert(root!=NULL);
		return dist(pt[ntop],root->query(pt[ntop]));
	}
}T;
int main(){
	int tot1=ni(),tot2=ni(),op,x,y;
	while(tot1--){
		x=ni(),y=ni();
		T.set(x,y);
		T.insert();
	}
	while(tot2--){
		op=ni(),x=ni(),y=ni();
		T.set(x,y);
		if(op==1){
			T.insert();
		}else{
			printf("%d\n",T.query());
		}
	}
}
