#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=32,D=10,logN=20;
namespace nfa{
	struct Node{
		unsigned f[D],end;
		inline friend Node operator | (const Node &a,const Node &b){
			Node c;
			for(int i=0;i<D;i++){
				c.f[i]=a.f[i]|b.f[i];
			}
			c.end=a.end|b.end;
			return c;
		}
	}pt[N];
	const char *s;
	int n;
	Node dfs(int &p,Node nd){
		for(;;){
			if(s[p]=='*'){
				p-=2;
				assert(s[p+1]==')');
				const int q=p+1;
				nd.end|=1u<<q;
				nd=nd|dfs(p,nd);
				nd.end^=1u<<q;
				assert(s[p]=='(');
				for(int i=p+1;i<q;i++){
					if((pt[i].end>>q)&1){
						pt[i]=pt[i]|nd;
						pt[i].end^=1u<<q;
					}
				}
				--p;
			}else if(s[p]==')'){
				Node cur;
				memset(&cur,0,sizeof(cur));
				for(;s[p--]!='(';cur=cur|dfs(p,nd));
				nd=cur;
			}else if(isdigit(s[p])){
				pt[p]=nd;
				memset(&nd,0,sizeof(nd));
				nd.f[s[p]-'0']=1u<<p;
				p--;
			}else break;
		}
		return nd;
	}
	inline void main(char _s[]){
		_s[0]=0;
		s=_s,n=strlen(s+1);
		mset(pt+1,0,n);
		Node fin;
		memset(&fin,0,sizeof(fin));
		fin.end=1;
		int p=n;
		pt[0]=dfs(p,fin);
	}
	inline unsigned trans(unsigned s,int d){
		int ans=0;
		for(int i=0;i<=n;i++){
			if((s>>i)&1){
				ans|=pt[i].f[d];
			}
		}
		return ans;
	}
	inline bool ended(unsigned s){
		for(int i=1;i<=n;i++){
			if((s>>i)&1){
				if(pt[i].end&1)return true;
			}
		}
		return false;
	}
}
char s[N];
map<unsigned,lint>f[logN][2];//f[bitcount][with n]
int dig[logN],dcnt;
void dig_dfs(lint n){
	if(n){
		dig_dfs(n/10);
		dig[++dcnt]=n%10;
	}
}
inline lint calc(lint n){
	dcnt=0,dig_dfs(n);
	for(int i=0;i<=dcnt;i++){
		f[i][0].clear(),f[i][1].clear();
	}
	for(int i=0;i<dcnt;i++){
		++f[i][i!=0][1];
		for(int j=0;j<2;j++){
			for(map<unsigned,lint>::iterator it=f[i][j].begin(),ti=f[i][j].end();it!=ti;++it){
				if(it->first==0)continue;
				for(int d=it->first==1,td=(j?9:dig[i+1]);d<=td;d++){
					f[i+1][j||d<td][nfa::trans(it->first,d)]+=it->second;
				}
			}
		}
	}
	lint ans=0;
	for(int j=0;j<2;j++){
		for(map<unsigned,lint>::iterator it=f[dcnt][j].begin(),ti=f[dcnt][j].end();it!=ti;++it){
			if(nfa::ended(it->first)){
				ans+=it->second;
			}
		}
	}
	return ans;
}
inline lint Main(){
	lint l=next_num<lint>(),r=next_num<lint>();
	scanf("%s",s+1);
	nfa::main(s);
	return calc(r)-calc(l-1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("prognostication.in","r",stdin);
	freopen("prognostication.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%lld\n",Main()));
	return 0;
}
