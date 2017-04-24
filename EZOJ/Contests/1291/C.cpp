#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <bitset>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=20010,SPLIT=15,INF=0x7f7f7f7f;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
bool seq[N];
bool decide[N],store[N];
int ans=INF,n;
bool tmp[N];
inline bool check(){
	for(int i=1;i<=n;i++){
		tmp[i]=seq[i]||decide[i];
	}
	for(int i=1;i<n;i++){
		if(!tmp[i]){
			if(gcd(i,n)!=i){
				return false;
			}
			for(int j=i;j<=n;j+=i){
				tmp[j]=!tmp[j];
			}
		}
	}
	return tmp[n];
}
void dfs(int x,int choose){
	if(x>n){
		if(check()&&choose<ans){
			ans=choose;
			memcpy(store+1,decide+1,n);
		}
		return;
	}
	if(choose>ans){
		return;
	}
	if(seq[x]){
		dfs(x+1,choose);
	}else{
		decide[x]=false;
		dfs(x+1,choose);
		decide[x]=true;
		dfs(x+1,choose+1);
	}
}
int main(){
	n=ni;
	int k=ni;
	for(int tot=k;tot--;){
		int cur=ni;
		seq[cur]=1;
	}
	if(n<=SPLIT){
		dfs(1,0);
		if(ans==INF||ans+k==n){
			puts("-1");
			return 0;
		}
		printf("%d\n",ans);
		for(int i=1;i<=n;i++){
			if(store[i]){
				printf("%d ",i);
			}
		}
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(seq[i]&&gcd(n,i)==i){
			for(int j=i;j<=n;j+=i){
				seq[j]^=1;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(seq[i]){
			ans++;
		}
	}
	if(ans+k==n){
		puts("-1");
		return 0;
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++){
		if(seq[i]){
			printf("%d ",i);
		}
	}
}
