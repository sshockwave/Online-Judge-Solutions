#include <iostream>
#include <cstdio>
#include <cstring>
#define lson(x) son[0][x]
#define rson(x) son[1][x]
#define N 100010
int low,son[2][N],val[N],size[N],delta=0,ntop=1,root,cnt=0;
inline void left_rotate(int &x){
	int y=rson(x);
	rson(x)=lson(y);
	lson(y)=x;
	size[y]=size[x];
	size[x]=size[lson(x)]+size[rson(x)]+1;
	x=y;
}
inline void right_rotate(int &x){
	int y=lson(x);
	lson(x)=rson(y);
	rson(y)=x;
	size[y]=size[x];
	size[x]=size[lson(x)]+size[rson(x)]+1;
	x=y;
}
void maintain(int &x,bool flag){//flag side have insertions
	if(flag){
		if(size[lson(rson(x))]>size[lson(x)]){
			right_rotate(rson(x)),left_rotate(x);
		}else if(size[rson(rson(x))]>size[rson(x)]){
			left_rotate(x);
		}else{
			return;
		}
	}else{
		if(size[lson(lson(x))]>size[rson(x)]){
			right_rotate(x);
		}else if(size[rson(lson(x))]>size[rson(x)]){
			left_rotate(lson(x)),right_rotate(x);
		}else{
			return;
		}
	}
	maintain(lson(x),false);
	maintain(rson(x),true);
	maintain(x,true);
	maintain(x,false);
}
void insert(int &x,int key){
	if(x==0){
		x=ntop++;
		val[x]=key;
		size[x]=1;
		return;
	}
	size[x]++;
	insert(son[key>val[x]][x],key);
	maintain(x,key>val[x]);
}
int query(int x,int rank){
	if(rank<=size[lson(x)]){
		return query(lson(x),rank);
	}
	if(rank==size[lson(x)]+1){
		return val[x];
	}
	return query(rson(x),rank-size[lson(x)]-1);
}
void leave(int &x){
	while(x&&val[x]+delta<low){
		cnt+=size[lson(x)]+1;
		x=rson(x);
	}
	if(x){
		leave(lson(x));
		size[x]=size[lson(x)]+size[rson(x)]+1;
	}
}
int main(){
	memset(son,0,sizeof(son));
	size[0]=root=0;
	int n,k;
	char op;
	scanf("%d%d",&n,&low);
	while(n--){
		while(op=getchar(),op>'Z'||op<'A');
		scanf("%d",&k);
		switch(op){
			case 'I':{
				if(k-delta<low){
					cnt++;
				}else{
					insert(root,k-delta);
				}
				break;
			}
			case 'A':{
				delta+=k;
				break;
			}
			case 'S':{
				delta-=k;
				leave(root);
				break;
			}
			case 'F':{
				if(k>size[root]){
					printf("-1\n");
				}else{
					printf("%d\n",query(root,size[root]+1-k)+delta);
				}
				break;
			}
		}
	}
	printf("%d",cnt);
}
