#include <iostream>
#include <cstdio>
#include <cstring>
#define MOD 998244353
using namespace std;
long long f[10000];
int main(){
	int n,k,num;
	scanf("%d%d",&n,&k);
	memset(f,0,sizeof(f));
	f[0]=1;
	while(n--){
		scanf("%d",&num);
		for(int i=k;i>=0;i--){
			for(int j=1;j<=num&&j<=i;j++){
				f[i]=(f[i]+f[i-j])%MOD;
			}
		}
	}
	printf("%d",f[k]);
}
#include <bits/stdc++.h>
#define ll long long
#define inf 0x7fffffff
#define mod 998244353
using namespace std;
  
ll n,k,ans;
ll a[30];
inline ll kusumi(ll a,ll b){ 
    ll ans=1;for(;a;a/=2,(b*=b)%=mod)
    if(a&1) (ans*=b)%=mod;return ans;
}
inline ll cal(ll n,ll x){
    ll an=1,tmp=1;
    for(ll i=1;i<=x;i++){
        (tmp*=i)%=mod;
        (an*=(n-i+1)%mod)%=mod;
    }
	tmp=kusumi(mod-2,tmp);
    (an*=tmp)%=mod;
}
void dfs(ll x,ll sum,ll t){
    if(sum>k) return;
    if(x==n+1){
        ll tmp=k-sum;
        if(t&1)ans-=cal(n-1+tmp,n-1);
        else ans+=cal(n-1+tmp,n-1);
        return;
    }
    dfs(x+1,sum,t);
    dfs(x+1,sum+a[x]+1,t+1);
}
int main(){
    scanf("%lld%lld",&n,&k);
    for(ll i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
	dfs(1,0,0);
    cout<<(ans%mod+mod)%mod<<endl;
    return 0;
}
