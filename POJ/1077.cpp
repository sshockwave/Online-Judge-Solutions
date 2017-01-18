#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define P 362880
using namespace std;
inline bool isNum(char c){
	return c>='0'&&c<='9';
}
int prev[P],est[P],mat[3][3],que[P],qtop=1,fac[10],ktop=0,mx[4]={0,0,1,-1},my[4]={1,-1,0,0};
char move[P],mc[]="lrud",stk[P];
inline bool valid(int x,int y){
	return x>=0&&x<3&&y>=0&&y<3;
}
inline int abs(int a){
	return a>0?a:-a;
}
inline int estimate(){
	int ret=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			ret+=abs((mat[i][j]-1)/3-i)+abs((mat[i][j]-1)%3-j);
		}
	}
	return ret;
}
inline int encode(){
	int *num=*mat,hash=0;
	for(int i=0,cnt;i<9;i++){
		cnt=num[i]-1;
		for(int j=0;j<i;j++){
			if(num[j]<num[i]){
				cnt--;
			}
		}
		hash+=cnt*fac[8-i];
	}
	return hash;
}
inline void decode(int hash){
	int *num=*mat;
	bool exist[10]={0};
	for(int i=0,rank;i<9;i++){
		rank=hash/fac[8-i];
		num[i]=0;
		for(int j=0;j<=rank;j++){
			while(exist[++num[i]]);
		}
		exist[num[i]]=true;
		hash%=fac[8-i];
	}
}
inline void push(int x){
	est[x]=estimate();
	que[qtop]=x;
	for(int i=qtop++;i>1;i>>=1){
		if(est[que[i>>1]]>est[x]){
			swap(que[i],que[i>>1]);
		}else{
			break;
		}
	}
}
inline int pop(){
	for(int i=--qtop,j=1;i!=j;){
		swap(que[i],que[j]);
		i=j;
		if((i<<1)<qtop&&est[que[i<<1]]<est[que[j]]){
			j=(i<<1);
		}
		if(((i<<1)|1)<qtop&&est[que[(i<<1)|1]]<est[que[j]]){
			j=((i<<1)|1);
		}
	}
	return que[qtop];
}
inline void blank(int &x,int &y){
	for(x=0;x<3;x++){
		for(y=0;y<3;y++){
			if(mat[x][y]==9){
				return;
			}
		}
	}
}
int main(){
	memset(prev,-1,sizeof(prev));
	fac[0]=1;
	for(int i=1;i<=9;i++){
		fac[i]=fac[i-1]*i;
	}
	char c;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cin>>c;
			if(isNum(c)){
				mat[i][j]=c-'0';
			}else{
				mat[i][j]=9;
			}
		}
	}
	int hash=encode(),x,y,to;
	prev[hash]=-2;
	push(hash);
	while(qtop>1){
		hash=pop();
		if(hash==0){
			while(prev[hash]!=-2){
				stk[ktop++]=move[hash];
				hash=prev[hash];
			}
			while(ktop--){
				putchar(stk[ktop]);
			}
			return 0;
		}
		decode(hash);
		blank(x,y);
		for(int i=0,tx,ty;i<4;i++){
			tx=x+mx[i],ty=y+my[i];
			if(valid(tx,ty)){
				swap(mat[x][y],mat[tx][ty]);
				to=encode();
				if(prev[to]==-1){
					prev[to]=hash;
					move[to]=mc[i];
					push(to);
				}
				swap(mat[x][y],mat[tx][ty]);
			}
		}
	}
	printf("unsolvable");
}
