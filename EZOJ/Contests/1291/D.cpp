#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=100010,E=N*2;
int a[N],A[N];
struct Query{
	int lend,rend,x,l,r,mid,cnt;
}q[N];
int to[E],bro[E],head[N],etop;
bool type[E];
inline void add_edge(int u,int v,bool t){
	to[etop]=v;
	bro[etop]=head[u];
	type[etop]=t;
	head[u]=etop++;
}
int prime[N],mu[N],ptop=0;
bool np[N];
inline void work(int x){
	for(int i=head[x];~i;i=bro[i]){
		int t=to[i],sum=0,n=q[t].x;
		for(int j=1;j*j<=n;j++){
			if(n%j==0){
				sum+=A[j]*mu[j];
				if(j*j!=n){
					sum+=A[n/j]*mu[n/j];
				}
			}
		}
		if(type[i]){
			q[t].cnt+=sum;
		}else{
			q[t].cnt=-sum;
		}
	}
}
int main(){
	memset(np,0,sizeof(np));
	mu[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			mu[i]=-1;
		}
		for(int j=0,cur=2;i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				mu[i*cur]=0;
				break;
			}else{
				mu[i*cur]=-mu[i];
			}
		}
	}
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=tot;i++){
		q[i]=(Query){ni,ni,ni};
		q[i].l=q[i].lend-1,q[i].r=q[i].rend;
	}
	for(int rest=tot;rest;){
		etop=0;
		memset(head+1,-1,n<<2);
		for(int i=1;i<=tot;i++){
			if(q[i].l!=q[i].r){
				q[i].mid=((q[i].l+q[i].r)>>1)+1;
				add_edge(q[i].mid-1,i,0);
				add_edge(q[i].rend,i,1);
			}
		}
		memset(A,0,sizeof(A));
		for(int i=1;i<=n;i++){
			for(int j=1;j*j<=a[i];j++){//to be better
				if(a[i]%j==0){
					A[j]++;
					if(a[i]!=j*j){
						A[a[i]/j]++;
					}
				}
			}
			work(i);
		}
		rest=tot;
		for(int i=1;i<=tot;i++){
			if(q[i].l!=q[i].r){
				if(q[i].cnt){
					q[i].l=q[i].mid;
				}else{
					q[i].r=q[i].mid-1;
				}
			}
			if(q[i].l==q[i].r){
				rest--;
			}
		}
	}
	for(int i=1;i<=tot;i++){
		if(q[i].l<q[i].lend){
			puts("-1");
		}else{
			printf("%d\n",q[i].l);
		}
	}
}
