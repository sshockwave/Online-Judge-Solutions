#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline bool is_letter(char c){
	return c>='a'&&c<='z';
}
inline char nc(){
	char c;
	while(!is_letter(c=getchar()));
	return c;
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=200010;
char s[N],to[26][26];
lint f[N];
struct Info{
	char c;
	int x;
	Info *bro;
}*head[N];
inline void push_back(Info** &pt,char c,int x){
	static Info *pool=new Info[N*50];
	*pt=pool++;
	(*pt)->c=c,(*pt)->x=x;
	pt=&((*pt)->bro);
	*pt=NULL;
}
int main(){
	memset(to,0,sizeof(to));
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int tot=ni();tot--;){
		char a=nc(),b=nc(),c;
		while(c=getchar(),!is_letter(c)&&c!='*');
		to[a-'a'][b-'a']=c;
	}
	memset(head,0,sizeof(head));
	memset(f,0,sizeof(f));
	lint ans=0;
	for(int i=n,p;i>=1;i--){
		char a=s[i],c;
		Info **pt=head+i;
		push_back(pt,a,i);
		for(Info *j=head[i+1];j;){
			if(c=to[a-'a'][j->c-'a']){
				p=j->x+1;
				if(c=='*'){
					f[i]=f[p]+1;
					*pt=head[p];
					break;
				}else{
					a=c;
					push_back(pt,a,j->x);
					j=head[p];
				}
			}else{
				j=j->bro;
			}
		}
		ans+=f[i];
	}
	printf("%lld\n",ans);
}
