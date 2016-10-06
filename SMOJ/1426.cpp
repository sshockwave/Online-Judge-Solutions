#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 100010
using namespace std;
int posx[N],posy[N],posz[N],fa[N],rank[N];
struct edge{
	int from,to,length;
	edge(int f,int t,int l){
		from=f,to=t,length=l;
	}
};
bool operator < (const edge &a,const edge &b){
	return a.length>b.length;
}
priority_queue<edge>q;
inline int abs(int a){
	return a>0?a:-a;
}
int getroot(int x){
	if(fa[x]==0){
		return x;
	}
	return fa[x]=getroot(fa[x]);
}
inline void unionp(int a,int b){
	a=getroot(a),b=getroot(b);
	if(rank[a]<rank[b]){
		swap(a,b);
	}
	fa[b]=a;
	if(rank[a]==rank[b]){
		rank[a]++;
	}
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	memset(fa,0,sizeof(fa));
	memset(rank,0,sizeof(rank));
	int n;
	long long sum=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",posx+i,posy+i,posz+i);
		for(int j=1;j<i;j++){
			q.push(edge(i,j,min(abs(posx[i]-posx[j]),min(abs(posy[i]-posy[j]),abs(posz[i]-posz[j])))));
		}
	}
	while(!q.empty()){
		edge cur=q.top();
		q.pop();
		if(getroot(cur.from)!=getroot(cur.to)){
//			cout<<"Union:"<<cur.from<<"\t"<<cur.to<<endl;
			sum+=cur.length;
			unionp(cur.from,cur.to);
		}
	}
	cout<<sum;
}
