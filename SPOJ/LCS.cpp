#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=250010;
char s1[N],s2[N];
struct SuffixAutomaton{
	struct state{
		state *lnk,*go[26];
		int val;
		state():lnk(0),val(0){
			memset(go,0,sizeof(go));
		}
	}ini,*tail;
	SuffixAutomaton():tail(&ini){}
	inline void extend(int c){
		static state *pool=new state[N*3];
		state *p=tail;
		tail=pool++;
		tail->val=p->val+1;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=tail;
		}
		if(p==0){
			tail->lnk=&ini;
			return;
		}
		state *q=p->go[c];
		if(p->val+1==q->val){
			tail->lnk=q;
			return;
		}
		state *nq=pool++;
		memcpy(nq->go,q->go,sizeof(q->go));
		nq->val=p->val+1;
		nq->lnk=q->lnk;
		tail->lnk=q->lnk=nq;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=nq;
		}
	}
	inline int solve(){
		for(int i=0;s1[i];i++){
			extend(s1[i]-'a');
		}
		state *p=&ini;
		int f=0,ans=0;
		for(int i=0,c;s2[i];i++){
			int c=s2[i]-'a';
			if(p->go[c]){
				p=p->go[c];
				apmax(ans,++f);
			}else{
				for(;p!=&ini&&p->go[c]==0;p=p->lnk);
				f=p->val;
			}
		}
	}
}SAM;
int main(){
	scanf("%s%s",s1,s2);
	printf("%d\n",SAM.solve());
}
