#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
//#include <ctime>
#define N 50010
#define INF 2147483647
#define SEG 600100
#define F 100000
using namespace std;
int l[N],r[N],f[N][2],drop[N][2],
	val[SEG],lend[SEG],rend[SEG],mid[SEG],lson[SEG],rson[SEG],ntop=0,root;
bool delta[N];
inline int abs(int a){
	return a>0?a:-a;
}
inline void apmin(int &a,int b){
	if(a>b||a==-1){
		a=b;
	}
}
void build(int &x,int left,int right){
	x=ntop++;
	cout<<"("<<left<<","<<right<<"):node "<<x<<endl;
	lend[x]=left,rend[x]=right,mid[x]=(left+right)/2,val[x]=0;
	if(left!=right){
		build(lson[x],left,mid[x]);
		build(rson[x],mid[x]+1,right);
	}
}
void cover(int x,int a,int b,int v){
	cout<<"\tAlter ("<<a<<","<<b<<") in ("<<lend[x]<<","<<rend[x]<<") to "<<v<<endl;
	if(lend[x]==rend[x]){
		val[x]=v;
		return;
	}
	if(delta[x]){
		val[lson[x]]=val[x],delta[lson[x]]=true;
		val[rson[x]]=val[x],delta[rson[x]]=true;
		delta[x]=false;
	}
	if(a==lend[x]&&b==rend[x]){
		delta[x]=true;
		val[x]=v;
	}else if(a>mid[x]){
		cover(rson[x],a,b,v);
	}else if(b<=mid[x]){
		cover(lson[x],a,b,v);
	}else{
		cover(lson[x],a,mid[x],v);
		cover(rson[x],mid[x]+1,b,v);
	}
}
int query(int x,int p){
	if(lend[x]==rend[x]||delta[x]){
		return val[x];
	}
	if(p>mid[x]){
		return query(rson[x],p);
	}else{
		return query(lson[x],p);
	}
}
int main(){
	freopen("1421.in","r",stdin);
//	freopen("1421.out","w",stdout);
	memset(delta,0,sizeof(delta));
	int n,s,lm=INF,rm=-INF;
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++){
		scanf("%d%d",l+i,r+i);
		if(lm>l[i]){
			lm=l[i];
		}
		if(rm<r[i]){
			rm=r[i];
		}
	}
	cout<<"LM:"<<lm<<"\tRM:"<<rm<<endl;
	cout<<"Building:"<<endl;
	build(root,0,rm-lm);
	for(int i=1;i<=n;i++){
		drop[i][0]=query(root,l[i]-lm);
		drop[i][1]=query(root,r[i]-lm);
		cout<<"Fence "<<i<<" drop left:"<<drop[i][0]<<" drop right:"<<drop[i][1]<<endl;
		cover(root,l[i]-lm,r[i]-lm,i);
	}
	memset(f,-1,sizeof(f));
	l[0]=r[0]=0;
	f[n][0]=abs(s-l[n]),f[n][1]=abs(s-r[n]);
	for(int i=n;i>0;i--){
		apmin(f[drop[i][0]][0],abs(l[i]-l[drop[i][0]]));
		apmin(f[drop[i][0]][1],abs(l[i]-r[drop[i][0]]));
		apmin(f[drop[i][1]][0],abs(r[i]-l[drop[i][1]]));
		apmin(f[drop[i][1]][1],abs(r[i]-r[drop[i][1]]));
	}
	printf("%d",max(f[0][0],f[0][1]));
//	printf("\n%dms",clock());
}
