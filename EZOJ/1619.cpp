#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<typename T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=100010;
struct State{
	State *lnk,*go[26];
	int val;
	State():lnk(0),val(0){
		memset(go,0,sizeof(go));
	}
}pol[N*3],*pool;
struct SAM{
	State ini,*tail;
	SAM():tail(&ini){
		pool=pol;
		memset(pol,0,sizeof(pol));
	}
	inline void extend(int c){
		State *p=tail;
		tail=pool++;
		tail->val=p->val+1;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=tail;
		}
		if(p==0){
			tail->lnk=&ini;
			return;
		}
		State *q=p->go[c];
		if(q->val==p->val+1){
			tail->lnk=q;
			return;
		}
		State *nq=pool++;
		*nq=*q;
		nq->val=p->val+1;
		tail->lnk=q->lnk=nq;
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
	}
};
char s[N];
int main(){
	int ans=0;
	for(int tot=ni;tot--;){
		scanf("%s",s);
		SAM sam;
		for(int i=0;s[i];i++){
			sam.extend(s[i]-'a');
		}
		for(State *p=pol;p<pool;p++){
			ans+=p->val-p->lnk->val;
		}
	}
	printf("%d\n",ans);
}