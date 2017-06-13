#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=1000010,SIGMA=26;
struct SAM{
	typedef SAM* node;
	node lnk,go[SIGMA];
	int val,right,head;
	SAM(){
		memset(this,0,sizeof(SAM));
		head=-1;
	}
	inline void add(node);
	inline node ext(int);
	inline void dfs(){
		for(int i=0;i<SIGMA;i++){
			if(go[i]){
				go[i]->dfs();
				right+=go[i]->right;
			}
		}
	}
}sam,*tail=&sam,pol[N*3],*pool=pol,*to[N*3];
int bro[N*3],e=0;
inline void SAM::add(SAM* v){
	to[e]=v,bro[e]=head,head=e++;
}
inline SAM* SAM::ext(int c){
	node p=this,np=pool++;
	np->val=p->val+1;
	np->right=1;
	for(;p&&p->go[c]==NULL;p=p->lnk){
		p->go[c]=np;
	}
	if(p==NULL){
		np->lnk=&sam;
		return np;
	}
	node q=p->go[c];
	if(q->val==p->val+1){
		np->lnk=q;
		return np;
	}
	node nq=pool++;
	*nq=*q;
	nq->val=p->val+1;
	q->lnk=np->lnk=nq;
	for(;p&&p->go[c]==q;p=p->lnk){
		p->go[c]=nq;
	}
	return np;
}
char s[N];
int main(){
	scanf("%s",s);
	for(int i=0;s[i];i++){
		tail=tail->ext(s[i]-'a');
	}
	for(SAM* i=pol;i<pool;i++){
		i->lnk->add(i);
	}
	sam.dfs();
	for(int tot=ni;tot--;){
		scanf("%s",s);
		int n=strlen(s),ans=0;
		for(int i=0,j=n;i<n;i++,j++){
			s[j]=s[i];
		}
		SAM *p=&sam;
		for(int i=0,nn=n<<1;i<nn;i++){
			int c=s[i]-'a';
			for(;p&&p->go[c]==NULL;p=p->lnk);
			if(p==NULL){
				break;
			}
			p=p->go[c];
			if(p->val<=i-n+1){
				break;
			}
			if(p->val>=n){
				ans+=p->right;
			}
		}
		printf("%d\n",ans);
	}
}