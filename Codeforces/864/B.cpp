#include <iostream>
#include <cstdio>
#include <cstring>
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
char s[210];
bool vis[26];
int main(){
#ifndef ONLINE_JUDGE
	freopen("letter.in","r",stdin);
	freopen("letter.out","w",stdout);
#endif
	ni;
	scanf("%s",s);
	memset(vis,0,sizeof(vis));
	int ans=0,cnt=0;
	for(int i=0;s[i];i++){
		if(s[i]>='a'){
			if(!vis[s[i]-'a']){
				cnt++,vis[s[i]-'a']=true;
				if(cnt>ans){
					ans=cnt;
				}
			}
		}else{
			memset(vis,0,sizeof(vis));
			cnt=0;
		}
	}
	printf("%d\n",ans);
	return 0;
}
