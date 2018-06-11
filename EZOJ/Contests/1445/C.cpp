#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef vector<int>vi;
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=22;
namespace gmath{
	int c[N][N];
	inline void main(int n=N-1){
		memset(c,0,sizeof(c));
		for(int i=0;i<=n;i++){
			c[i][0]=1;
			for(int j=1;j<=i;j++){
				c[i][j]=c[i-1][j-1]+c[i-1][j];
			}
		}
	}
}
using gmath::c;
struct State{
	vi bef,nxt;//before,new
	int unvis,mencnt;
	inline friend bool operator < (const State &a,const State &b){
		const int lena=a.bef.size()+a.nxt.size();
		const int lenb=b.bef.size()+b.nxt.size();
		if(lena!=lenb)return lena<lenb;
		//distinguish purpose only
		if(a.unvis!=b.unvis)return a.unvis>b.unvis;
		if(a.mencnt!=b.mencnt)return a.mencnt>b.mencnt;
		if(a.bef.size()!=b.bef.size())return a.bef.size()>b.bef.size();
		for(vi::const_iterator it1=a.bef.begin(),it2=b.bef.begin(),ti=a.bef.end();it1!=ti;++it1){
			if(*it1!=*it2)return *it1>*it2;
		}
		for(vi::const_iterator it1=a.nxt.begin(),it2=b.nxt.begin(),ti=a.nxt.end();it1!=ti;++it1){
			if(*it1!=*it2)return *it1>*it2;
		}
		return false;
	}
};
struct Valans{
	int cnt;
	lint f;
};
map<State,Valans>mp;
typedef map<State,Valans>::iterator mpiter;
set<pair<int,State> >st;
int curval;
inline void upd(const State &s,int d=curval){
	mpiter it=mp.find(s);
	if(it==mp.end()){
		mp[s]=(Valans){d,0};
		st.insert(make_pair(d,s));
	}else if(d<it->second.cnt){
		st.erase(make_pair(it->second.cnt,s));
		st.insert(make_pair(d,s));
		it->second.cnt=d;
	}
}
int n;
void dfs1(const vi &bef,const vi &nxt,int dshrst,int dshmx,int menrst,int menmn,int unvis,bool flag){
	//flag:be careful with unvis, unvis remains unvis!
	if(dshrst==0){
		State s=(State){bef,nxt,unvis,menrst};
		sort(s.nxt.begin(),s.nxt.end());
		if(flag){
			assert(bef.empty());
			s.mencnt=n;
			s.bef=s.nxt,s.nxt.clear();
			upd(s,curval+1);
		}else{
			upd(s);
		}
		return;
	}
	int i=1;
	if(flag&&menmn==0){
		i=0;
	}
	for(;i<=dshrst&&i<=dshmx;i++){
		if(menrst-menmn*i<0)break;
		vi nnx=nxt;
		int tmx=i,tvis=unvis;
		if(flag&&menmn==0){
			tmx=dshmx,tvis=i;
		}else{
			nnx.push_back(i);
		}
		dfs1(bef,nnx,dshrst-i,tmx,menrst-menmn*i,menmn+1,tvis,flag);
	}
}
inline void Main(){
	n=ni;
	const int d=ni;
	mp.clear();
	st.clear();
	{//initial
		State s;
		s.unvis=d;
		s.mencnt=n;
		upd(s,0);
	}
	for(set<pair<int,State> >::iterator it=st.begin();/*it!=st.end()*/;++it){
		const State &s=it->second;
		curval=it->first;
		if(s.bef.empty()){
			dfs1(s.bef,s.nxt,s.unvis,s.unvis,s.mencnt,0,s.unvis,true);
		}else if((int)s.bef.size()==d){
			assert(s.unvis==0);
			set<pair<int,State> >::iterator j;
			for(;j=st.end(),--j,j!=it;st.erase(j));
			break;
		}else{
			vi tmp=s.bef;
			int t=tmp.back();
			tmp.pop_back();
			dfs1(tmp,s.nxt,t,t,s.mencnt,0,s.unvis,false);
		}
	}
	printf("%d %lld\n",st.rbegin()->first,mp.begin()->second.f);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fantasy.in","r",stdin);
	freopen("fantasy.out","w",stdout);
#endif
	gmath::main();
	for(int tot=ni;tot--;Main());
	return 0;
}
