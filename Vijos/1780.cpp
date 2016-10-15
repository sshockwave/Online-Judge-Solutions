#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100010
#define INF 2000000000
#define lson(x) son[x][0]
#define rson(x) son[x][1]
using namespace std;
int h[N],anext[N],bnext[N],curh,f[N][25],la[N][25],lb[N][25];
namespace sbt{
	int ntop=1,key[N],org[N],son[N][2],size[N],root=0;
	void left_rotate(int &x){
		
	}
	void maintain(int &x){
		
	}
	void insert(int &x,int k,int o){
		if(!x){
			x=ntop++;
			lson(x)=rson(x)=0;
			key[x]=k;
			size[x]=1;
			org[x]=o;
			return;
		}
		size[x]++;
		insert(son[x][k>key[x]],k,o);
		maintain(x);
	}
	int pred(int &x,int last,int k){
		if(x==0){
			return org[last];//last  =>  org[last]
		}
		if(k>key[x]){
			return pred(rson(x),x,k);
		}
		return pred(lson(x),last,k);
	}
	int succ(int &x,int last,int k){
		if(x==0){
			return org[last];//last  => org[last]
		}
		if(k<key[x]){
			return succ(lson(x),x,k);
		}
		return succ(rson(x),last,k);
	}
}
inline int abs(int x){
	return x>0?x:-x;
}
bool diycmp(const int &a,const int &b){
	if(abs(h[a]-curh)==abs(h[b]-curh)){
		return h[a]<h[b];
	}
	return abs(h[a]-curh)<abs(h[b]-curh);
}
inline int log2(int x){
	
}
inline void query(int s,int x,int &ans1,int &ans2){
	ans1=ans2=0;
	int j,t=x,cnt=-1;
	for(;t;t>>=1,cnt++);
	for(j=cnt;j>=0;j--){
		if(la[s][j]!=INF&&lb[s][j]!=INF&&ans1+ans2+la[s][j]+lb[s][j]<=x){
			ans1+=la[s][j];
			ans2+=lb[s][j];
			s=f[s][j];
		}
	}
	if(la[s][0]+ans1+ans2<=x){
		ans1+=la[s][0];
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	sbt::org[0]=0;//together with last => org[last]
	memset(la,0,sizeof(la));
	memset(lb,0,sizeof(lb));
	int n,m,nodes[4],ntop,ans1,ans2,s,x,q1=INF,q2=1,s0=0;
	cin>>n;
	h[0]=-INF;
	anext[0]=bnext[0]=0; 
	for(int i=1;i<=n;i++){
		cin>>h[i];
	}
	for(int i=n;i>=1;i--){
		memset(nodes,0,sizeof(nodes));
		ntop=0;
		if(nodes[ntop]=sbt::pred(sbt::root,0,h[i])){
			ntop++;
			if(nodes[ntop]=sbt::pred(sbt::root,0,h[nodes[ntop-1]])){
				ntop++;
			}
		}
		if(nodes[ntop]=sbt::succ(sbt::root,0,h[i])){
			ntop++;
			if(nodes[ntop]=sbt::succ(sbt::root,0,h[nodes[ntop-1]])){
				ntop++;
			}
		}
		curh=h[i];
		sort(nodes,nodes+ntop,diycmp);
		bnext[i]=nodes[0];
		anext[i]=nodes[1];
//la and lb shouldn't be calculated here because bnext[anext[i]] might not have been calculated.
//		lb[i][0]=abs(h[bnext[i]]-h[i]);//A drive first, and then b drive. They don't drive at the same time!
		sbt::insert(sbt::root,h[i],i);
	}
	for(int i=1;i<=n;i++){
		f[i][0]=bnext[anext[i]];//Forgotten
		if(anext[i]){
			la[i][0]=abs(h[i]-h[anext[i]]);
		}else{
			la[i][0]=INF;
		}
		if(bnext[i]){
			lb[i][0]=abs(h[f[i][0]]-h[anext[i]]);
		}else{
			lb[i][0]=INF;
		}
//		cout<<"From "<<i<<" to "<<anext[i]<<" to "<<f[i][0]<<"\t len:"<<la[i][0]<<"+"<<lb[i][0]<<endl;
	}
	for(int j=1;j<20;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
			if(la[i][j-1]==INF||la[f[i][j-1]][j-1]==INF){
				la[i][j]=INF;
			}else{
				la[i][j]=la[i][j-1]+la[f[i][j-1]][j-1];
			}
			if(lb[i][j-1]==INF||lb[f[i][j-1]][j-1]==INF){
				lb[i][j]=INF;
			}else{
				lb[i][j]=lb[i][j-1]+lb[f[i][j-1]][j-1];
			}
		}
	}
	cin>>x;
	for(s=1;s<=n;s++){
		query(s,x,ans1,ans2);
		if(1ll*ans1*q2<1ll*q1*ans2||(1ll*ans1*q2==1ll*q1*ans2&&h[s]>h[s0]&&ans1&&ans2)){
			q1=ans1,q2=ans2;
			s0=s;
		}
	}
	cout<<s0<<endl;
	for(cin>>m;m--;){
		cin>>s>>x;
		query(s,x,ans1,ans2);
		cout<<ans1<<" "<<ans2<<endl;
	}
}
