#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
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
const int N=2010;
struct SAM{
	struct state{
		state *lnk,*go[26];
		int val;
		state():lnk(0),val(0){
			memset(go,0,sizeof(go));
		}
	}ini,*tail;
	SAM():tail(&ini){}
	inline void extend(int c){
		static state *pool=new state[N*5];
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
		if(q->val==p->val+1){
			tail->lnk=q;
			return;
		}
		state *nq=pool++;
		memcpy(nq->go,q->go,sizeof(q->go));
		nq->val=p->val+1;
		nq->lnk=q->lnk;
		tail->lnk=q->lnk=nq;
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
	}
}sam_a,sam_b;
struct QAM{
	struct state{
		state *go[26];
		state(){
			memset(go,0,sizeof(go));
		}
	}ini,st[N];
	inline void build(char *s,int n){
		for(int i=n-1;i>=0;i--){
			st[i]=ini;
			ini.go[s[i]-'a']=st+i;
		}
	}
}seq_a,seq_b;
template<typename T1,typename T2>
	inline int solve(T1 p1,T2 p2){
	struct state{
		T1 p1;
		T2 p2;
		int len;
	}*que=new state[N*N],*qtail=que;
	*(qtail++)=(state){p1,p2,0};
	while(que<qtail){
		p1=que->p1;
		p2=que->p2;
		int len=que->len+1;
		que++;
		for(int i=0;i<26;i++){
			if(p1->go[i]){
				if(p2->go[i]){
					*(qtail++)=(state){p1->go[i],p2->go[i],len};
				}else{
					return len;
				}
			}
		}
	}
	return -1;
}
char a[N],b[N];
int main(){
	cin>>a>>b;
	int la=strlen(a),lb=strlen(b);
	for(int i=0;a[i];i++){
		sam_a.extend(a[i]-'a');
	}
	for(int i=0;b[i];i++){
		sam_b.extend(b[i]-'a');
	}
	seq_a.build(a,la);
	seq_b.build(b,lb);
	cout<<solve(&sam_a.ini,&sam_b.ini)<<endl;
	cout<<solve(&sam_a.ini,&seq_b.ini)<<endl;
	cout<<solve(&seq_a.ini,&sam_b.ini)<<endl;
	cout<<solve(&seq_a.ini,&seq_b.ini)<<endl;
}
