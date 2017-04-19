#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
#include <set>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=200010;
struct state{
	state *lnk,*go[26];
	int val,right;
	set<state*>son;
	state():lnk(0),val(0),right(1){
		memset(go,0,sizeof(go));
	}
}ini,*tail=&ini;
inline void extend(int c){
	static state *pool=new state[N*3];
	state *p=tail;
	tail=pool++;
	tail->val=p->val+1;
	for(;p&&p->go[c]==0;p=p->lnk){
		p->go[c]=tail;
	}
	if(p==0){
		ini.son.insert(tail);
		tail->lnk=&ini;
		return;
	}
	state *q=p->go[c];
	if(q->val==p->val+1){
		q->son.insert(tail);
		tail->lnk=q;
		return;
	}
	state *nq=pool++;
	*nq=*q;
	nq->val=p->val+1;
	q->lnk->son.erase(q);
	q->lnk->son.insert(nq);
	q->lnk=tail->lnk=nq;
	nq->son.insert(q);
	nq->son.insert(tail);
	for(;p&&p->go[c]==q;p=p->lnk){
		p->go[c]=nq;
	}
}
void dfs(state *x){
	for(set<state*>::iterator it=x->son.begin();it!=x->son.end();it++){
		dfs(*it);
		x->right+=(*it)->right;
	}
}
char s[N];
struct node{
	int i;
	bool used;
	state *p;
};
inline int bfs(){
	int ans=0;
	queue<node>q;
	q.push((node){0,0,&ini});
	while(!q.empty()){
		int i=q.front().i+1,c=s[i]-'a';
		bool used=q.front().used;
		state *p=q.front().p;
		q.pop();
		if(s[i]==0){
			ans+=p->right;
			continue;
		}
		if(used){
			if(p->go[c]){
				q.push((node){i,true,p->go[c]});
			}
		}else for(int j=0;j<26;j++){
			if(p->go[j]){
				if(j==c){
					q.push((node){i,false,p->go[j]});
				}else{
					q.push((node){i,true,p->go[j]});
				}
			}
		}
	}
	return ans;
}
int main(){
	scanf("%s",s);
	for(int i=0;s[i];i++){
		extend(s[i]-'a');
	}
	for(int tot=ni();tot--;){
		scanf("%s",s+1);
		printf("%d\n",bfs());
	}
}
