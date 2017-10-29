#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
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
struct state{
	lint a,b,c;
	inline void sort(){
		if(a>b)swap(a,b);
		if(b>c)swap(b,c);
		if(a>b)swap(a,b);
	}
	inline friend bool operator == (const state &x,const state &y){
		return x.a==y.a&&x.b==y.b&&x.c==y.c;
	}
};
inline state reduce(state x,lint &step){
	x.sort();
	lint a=x.b-x.a,b=x.c-x.b;
	if(a==b){
		return x;
	}
	if(a>b){
		lint d=a%b?a/b:a/b-1;
		step+=d;
		return reduce((state){x.a,x.b-d*b,x.c-d*b},step);
	}else{
		lint d=b%a?b/a:b/a-1;
		step+=d;
		return reduce((state){x.a+d*a,x.b+d*a,x.c},step);
	}
}
inline state fly(state x,lint step){
	x.sort();
	if(step==0){
		return x;
	}
	lint a=x.b-x.a,b=x.c-x.b;
	if(a>b){
		lint d=min((a%b?a/b:a/b-1),step);
		return fly((state){x.a,x.b-d*b,x.c-d*b},step-d);
	}else{
		lint d=min((b%a?b/a:b/a-1),step);
		return fly((state){x.a+d*a,x.b+d*a,x.c},step-d);
	}
}
inline ostream & operator << (ostream & out,const state &b){
	out<<"("<<b.a<<","<<b.b<<","<<b.c<<")";
	return out;
}
inline lint Main(){
	state s=(state){ni,ni,ni};
	state t=(state){ni,ni,ni};
	s.sort(),t.sort();
	if(s==t){
		return 0;
	}
	lint step1=0,step2=0;
	if(!(reduce(s,step1)==reduce(t,step2))){
		return -1;
	}
	if(step1<step2){
		swap(s,t),swap(step1,step2);
	}
	lint ans=step1-step2;
	s=fly(s,step1-step2);//now step2
	if(s==t){
		return ans;
	}
	for(lint j=1ll<<50;j;j>>=1){
		if(j<step2){
			state ns=fly(s,j);
			state nt=fly(t,j);
			if(!(ns==nt)){
				ans+=j<<1;
				step2-=j;
				s=ns,t=nt;
			}
		}
	}
	assert(!(s==t));
	assert(fly(s,1)==fly(t,1));
	return ans+2;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("throw.in","r",stdin);
	freopen("throw.out","w",stdout);
#endif
	lint ans=Main();
	if(ans>=0){
		printf("YES\n%lld\n",ans);
	}else{
		puts("NO");
	}
	return 0;
}
