#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010,K=5;
int k;
int curd;
bool usemx;
struct Node{
	int mn[K],mx[K],size;
	inline friend bool operator < (const Node &a,const Node &b){
		return usemx?a.mx[curd]<b.mx[curd]:a.mn[curd]<b.mn[curd];
	}
	inline friend bool bigg(const Node &a,const Node &b){
		for(int j=0;j<k;j++){
			if(a.mx[j]>b.mn[j])return true;
		}
		return false;
	}
	inline void operator += (const Node &b){
		for(int j=0;j<k;j++){
			apmin(mn[j],b.mn[j]);
			apmax(mx[j],b.mx[j]);
		}
		size+=b.size;
	}
};
typedef set<Node>sn;
typedef sn::iterator iter;
iter nxt[K];
int main(){
#ifndef ONLINE_JUDGE
	freopen("s.in","r",stdin);
	freopen("s.out","w",stdout);
#endif
	const int n=ni;
	k=ni;
	sn s;
	for(int i=1;i<=n;i++){
		Node cur;
		cur.size=1;
		iter mn,mx;
		for(int j=0;j<k;j++){
			cur.mn[j]=cur.mx[j]=ni;
			curd=j;
			iter tmpmn=(usemx=true,s.lower_bound(cur));
			iter tmpmx=(usemx=false,s.lower_bound(cur));
			if(j==0){
				mn=tmpmn,mx=tmpmx;
			}else{
				if(tmpmx==s.end()||(mx!=s.end()&&bigg(*tmpmx,*mx))){
					mx=tmpmx;
				}
				if(mn==s.end()||(tmpmn!=s.end()&&bigg(*mn,*tmpmn))){
					mn=tmpmn;
				}
			}
		}
		for(;mn!=mx;){
			assert(mn!=s.end());
			iter it=mn;
			++mn;
			cur+=*it;
			s.erase(it);
		}
		curd=0,s.insert(cur);
		printf("%d\n",s.rbegin()->size);
	}
	return 0;
}
