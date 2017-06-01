#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
using namespace std;
typedef long long lint;
#define invalid puts("0"),exit(0);
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
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=410;
int sum[N][N],op[N],gen[N],tag[N],tim=0,n=0;
bool f[N][N],g[N][N];
inline bool same(const int &a,const int &b){
	return a==-1||b==-1||a==b;
}
void push(int d,int g){
	if(d==0&&op[n]==0){
		assert(~g&&~gen[n]);
		if(g==gen[n]){
			invalid;
		}
		n--;
	}else if(op[n]==1&&d==-1&&f[n][n+1]){
		n--;
		if(~g&&~gen[n]){
			if(g!=gen[n]){
				push(0,g);
			}
		}else{
			gen[n]=g;
			f[n][n+1]=false;
		}
	}else{
		n++,op[n]=d,gen[n]=g,tag[n]=tim,f[n][n+1]=true;
	}
}
inline void push_sib(int g){
	push(-1,-1);
	push(1,g);
}
inline void parse(char s[]){
	tim++;
	switch(s[0]){
		case 'f':return push(-1,0);//father
		case 'm':return push(-1,1);//mother
		case 's':switch(s[1]){
			case 'o':return push(1,0);//son
			case 'i':return push_sib(1);//sister
		}
		case 'd':return push(1,1);//daughter
		case 'h':return push(0,0);//husband
		case 'w':return push(0,1);//wife
		case 'b':return push_sib(0);//brother
		case 'g':switch(s[5]){
			case 'f':{push(-1,-1);return push(-1,0);}//grandfather
			case 'm':{push(-1,-1);return push(-1,1);}//grandmother
			case 's':{push(1,-1);return push(1,0);}//grandson
			case 'd':{push(1,-1);return push(1,1);}//granddaughter
		}
		case 'u':{push(-1,-1);return push_sib(0);}//uncle
		case 'a':{push(-1,-1);return push_sib(1);}//aunt
		case 'n':switch(s[1]){
			case 'e':{push_sib(-1);return push(1,0);}//nephew
			case 'i':{push_sib(-1);return push(1,1);}//niece
		}
	}
}
int main(){
	op[0]=10,gen[0]=0,tag[0]=0;
	memset(f,false,sizeof(f));
	scanf("Q is U's");
	for(char s[20];scanf("%s",s)!=EOF;parse(s));
	memset(f,false,sizeof(f));
	for(int i=1;i<n;i++){
		f[i][i+1]=same(gen[i-1],gen[i+1])&&op[i]+op[i+1]==0&&tag[i]!=tag[i+1];
	}
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			sum[i][j]=sum[i][j-1]+op[j];
		}
	}
	for(int gap=3;gap<=n;gap++){
		for(int i=1,j=gap;j<=n;i++,j++){
			if(same(gen[i-1],gen[j])&&sum[i][j]==0){
				if(f[i+1][j-1]&&op[i]+op[j]==0){
					f[i][j]=true;
					continue;
				}
				for(int k=i+2;k<j;k++){
					if(f[i][k-1]&&f[k][j]){
						f[i][j]=true;
						break;
					}
				}
			}
		}
	}
	memset(sum,0,sizeof(sum));
	memset(g,false,sizeof(g));
	g[0][0]=true;
	for(int i=1;i<=n;i++){
		f[i][i-1]=true;
		for(int j=0;j<i;j++){
			if(f[j+1][i-1]){
				for(int k=0;k<=j;k++){
					g[i][k+(op[i]!=0)]|=g[i][k];
				}
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		if(g[n][i]){
			ans++;
		}
	}
	printf("%d\n",ans);
	for(int i=0;i<=n;i++){
		if(g[n][i]){
			printf("%d ",i);
		}
	}
	putchar('\n');
}