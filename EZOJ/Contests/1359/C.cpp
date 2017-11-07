#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=300010,INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
struct Query{
	int x;
	lint ans;
}q[N];
struct Line{
	int a,b;
	int dfn,dfe;
}line[N];
int qs=0,ls=0;
int qpos[N],lpos[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		vector<int>line,query;
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void cover(node x,int v){
		if(line[v].dfn<=x->l&&line[v].dfe>=x->r){
			x->line.push_back(v);
			return;
		}
		if(line[v].dfn<=x->m){
			cover(x->lson,v);
		}
		if(line[v].dfe>x->m){
			cover(x->rson,v);
		}
	}
	inline bool qcmp(int a,int b){
		return q[a].x<q[b].x;
	}
	int stk[N];
	void dfs(node x){
		if(x->l==x->r){
			for(int i=qpos[x->l-1]+1;i<=qpos[x->l];i++){
				x->query.push_back(i);
			}
			sort(x->query.begin(),x->query.end(),qcmp);
		}else{
			dfs(x->lson),dfs(x->rson);
			for(int i=0,j=0,ti=x->lson->query.size(),tj=x->rson->query.size();i<ti||j<tj;){
				if(j==tj||(i<ti&&q[x->lson->query[i]].x<q[x->rson->query[j]].x)){
					x->query.push_back(x->lson->query[i++]);
				}else{
					x->query.push_back(x->rson->query[j++]);
				}
			}
		}
		int ss=0;
		for(vector<int>::iterator it=x->line.begin();it!=x->line.end();it++){
			if(ss&&line[stk[ss-1]].a==line[*it].a){
				stk[ss-1]=line[stk[ss-1]].b>line[*it].b?stk[ss-1]:*it;
			}else{
				for(int i=*it,j,k;ss>=2;ss--){
					j=stk[ss-1],k=stk[ss-2];
					if((lint)(line[k].b-line[i].b)*(line[j].a-line[k].a)>(lint)(line[k].b-line[j].b)*(line[i].a-line[k].a)){
						break;
					}
				}
				stk[ss++]=*it;
			}
		}
		for(int i=0,j=0,tj=x->query.size();j<tj;j++){
			for(int a,b;a=stk[i],b=stk[i+1],i<ss-1&&line[a].b-line[b].b<=(lint)x->query[j]*(line[b].a-line[a].a);i++);
			apmax(q[x->query[j]].ans,(lint)line[i].a*q[x->query[j]].x+line[i].b);
		}
	}
}
int lst[N];
inline bool lcmp(int a,int b){
	return line[a].a<line[b].a;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("max.in","r",stdin);
	freopen("max.out","w",stdout);
#endif
	for(int i=1,tot=ni;i<=tot;i++){
		int tp=ni;
		if(tp==1){
			qpos[ls]=qs;
			lpos[i]=++ls;
			line[ls]=(Line){ni,ni,ls};
			lst[ls]=ls;
		}else if(tp==2){
			line[lpos[ni]].dfe=ls;
		}else{
			q[++qs]=(Query){ni,-LINF};
		}
	}
	qpos[ls]=qs;
	sort(lst+1,lst+ls+1,lcmp);
	seg::rt=seg::build(1,ls);
	for(int i=1;i<=ls;i++){
		seg::cover(seg::rt,lst[i]);
	}
	seg::dfs(seg::rt);
	for(int i=1;i<=qs;i++){
		if(i<=qpos[0]){
			puts("EMPTY SET");
		}else{
			printf("%lld\n",q[i].ans);
		}
	}
	return 0;
}
