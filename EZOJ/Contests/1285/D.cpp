#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=100010;
struct State{
	State *lnk,*go[26];
	int val,head;
	inline void init(int v){
		lnk=0,head=-1,val=v;
		memset(go,0,sizeof(go));
	}
}pol[N*3],*pool=pol;
struct SAM{
	State ini,*tail;
	SAM():tail(&ini){
		ini.init(0);
	}
	inline void extend(int c){
		State *p=tail;
		tail=pool++;
		tail->init(p->val+1);
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
State *gor[N];
inline int getans(char *s,int n){
	pool=pol;
	SAM sam;
	cout<<"Ask ";
	for(int i=0;i<n;i++){
		sam.extend(s[i]-'a');
		gor[i]=sam.tail;
		cout<<s[i];
	}
	cout<<endl;
	int ans=0;
	for(int i=0;i<n;i++){
		cout<<"End with "<<s[i]<<":"<<gor[i]->val-gor[i]->lnk->val<<endl;
		ans+=gor[i]->val-gor[i]->lnk->val;
	}
	return ans;
}
char s[N];
int main(){
	scanf("%s",s+1);
	for(int tot=ni(),len=ni();tot--;){
		printf("%d\n",getans(s+ni(),len));
	}
}
