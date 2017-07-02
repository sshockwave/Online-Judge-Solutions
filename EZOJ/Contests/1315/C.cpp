#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include "oath.h"
using namespace std;
typedef long long lint;
const int N=300010,logN=20;
struct Node{
	Node *lson,*rson;
	int size;
	Data val,sum,*pre;
	void push(Data arr[]){
		if(size==0){
			return;
		}
		rson->push(arr);
		arr+=rson->size;
		arr[1]=F(arr[0],val);
		lson->push(arr+1);
	}
	inline void init(){
		static Data *pool=new Data[N*logN];
		pre=pool,pool+=size;
		*pre=val,lson->push(pre),sum=pre[lson->size];
	}
}null=(Node){&null,&null,0},*root[N]={&null};
inline Node* nn(Node *x=&null){
	static Node *n=new Node[N*logN];
	return *n=*x,n++;
}
void ins(Node* &x,Node *pt){
	if(x->lson->size==x->rson->size){
		pt->lson=x,pt->size=x->size+1;
		pt->init(),x=pt;
	}else{
		ins((x=nn(x))->rson,pt);
		x->size++,x->sum=F(x->pre[x->lson->size],x->rson->sum);
	}
}
Data ask(Node *x,int kth){//from right
	if(kth<=x->rson->size){
		return ask(x->rson,kth);
	}
	if(x->rson->size){
		return F(x->rson->sum,x->pre[kth-x->rson->size-1]);
	}else{
		return x->pre[kth-1];
	}
}
int last[N][logN],tim=0;
void Init(){
	memset(last,0,sizeof(last));
}
void Add_element(int id, Data x){
	last[++tim][0]=id;
	for(int j=0;last[tim][j+1]=last[last[tim][j]][j];j++);
	Node *pt=nn();
	pt->val=x;
	ins(root[tim]=root[id],pt);
}
void Del_element(int id){
	tim++,id=last[id][0];
	memcpy(last[tim],last[id],sizeof(last[id]));
	root[tim]=root[id];
}
Data Query_range(int id,int l,int r){
	for(int j=0,diff=root[id]->size-r;root[id]->size!=r;j++){
		if((diff>>j)&1){
			id=last[id][j];
		}
	}
	return ask(root[id],r-l+1);
}
