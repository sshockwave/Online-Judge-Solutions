#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define M 22
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
int m,MOD,fail[M];
char s[M];
struct mat{
	int num[M][M];
	mat operator * (mat b){
		mat ret;
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				int &F=ret.num[i][j];
				F=0;
				for(int k=0;k<M;k++){
					(F+=num[i][k]*b.num[k][j])%=MOD;
				}
			}
		}
		return ret;
	}
}trans,id;
mat transpow(int x){
	if(x==0){
		return id;
	}
	mat ret=transpow(x>>1);
	ret=ret*ret;
	if(x&1){
		ret=ret*trans;
	}
	return ret;
}
int main(){
	int n=ni();
	m=ni(),MOD=ni();
	scanf("%s",s+1);
	fail[1]=0;
	for(int i=1,j=0;s[i];){//[1,j)==[i-j+1,i),j<i
		if(j==0||s[i]==s[j]){
			fail[++i]=++j;
		}else{
			j=fail[j];
		}
	}
	memset(id.num,0,sizeof(id.num));
	for(int i=0;i<M;i++){
		id.num[i][i]=1;
	}
	#define T trans.num
	memset(T,0,sizeof(T));
	for(int i=1,cnt;i<=m;i++){
		bool exist[10]={0};
		T[i][i-1]++;
		exist[s[i]-'0']=true;
		for(int j=fail[i];j;j=fail[j]){
			if(!exist[s[j]-'0']){
				exist[s[j]-'0']=true;
				T[j][i-1]++;
			}
		}
		cnt=0;
		for(int j=0;j<10;j++){
			if(!exist[j]){
				cnt++;
			}
		}
		T[0][i-1]+=cnt;
	}
	mat ans=transpow(n);
	int cnt=0;
	for(int i=0;i<m;i++){
		(cnt+=ans.num[i][0])%=MOD;
	}
	printf("%d",cnt);
}
