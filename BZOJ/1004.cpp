#include <iostream>
#include <cstdio>
#include <cstring>
#define S 22
#define N 3*S
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int disp[N],n,p,f[S][S][S],sr,sb,sg;
bool vis[N];
int pow(int x,int n){
	if(n==0){
		return 1;
	}
	int ret=pow(x,n>>1);
	ret=ret*ret%p;
	if(n&1){
		return ret*x%p;
	}else{
		return ret;
	}
}
inline int rev(int x){
	return pow(x,p-2);
}
inline void dp(int num,int sum){
	for(int i=sr;i>=0;i--){
		for(int j=sb;j>=0;j--){
			for(int k=sg;k>=0;k--){
				int &F=f[i][j][k];
				if(F&&i+j+k==sum){
					if(i+num<=sr){
						f[i+num][j][k]+=F;
					}
					if(j+num<=sb){
						f[i][j+num][k]+=F;
					}
					if(k+num<=sg){
						f[i][j][k+num]+=F;
					}
				}
			}
		}
	}
}
inline int fixed_cnt(){
	//find loop
	memset(vis,0,sizeof(vis));
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	int sum=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			int cnt=0;
			for(int j=i;!vis[j];j=disp[j]){
				vis[j]=true;
				cnt++;
			}
			dp(cnt,sum);
			sum+=cnt;
		}
	}
	return f[sr][sb][sg];
}
int main(){
	sr=next_int(),sb=next_int(),sg=next_int();
	int m=next_int(),sum=0;
	p=next_int();
	n=sr+sb+sg;
	for(int i=1;i<=n;i++){
		disp[i]=i;
	}
	int tmp=fixed_cnt();
	sum+=tmp;
	for(int i=0;i<m;i++){
		for(int i=1;i<=n;i++){
			disp[i]=next_int();//incorrect, but ought to work
		}
		int tmp=fixed_cnt();
		(sum+=tmp)%=p;
	}
	printf("%d",sum*rev(m+1)%p);
}
